/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       MindVisionCamera.cpp
 * @brief      迈德威视相机
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "MindVisionCamera.h"

#include <QDebug>
#include "MindVisionCameraInstance.h"
#include "include/CameraApi.h"
#include "gst417m.h"

// 相机操作：如果遇到错误则返回
#define MV_ERR_RETURN(CODE, MSG, RET) \
    do { \
    if (CAMERA_STATUS_SUCCESS != CODE) { \
    setError(MindVisionCameraInstance::formatErrorMsg(CODE, MSG)); \
    return RET; \
    } \
    } while(0)

namespace DzCamera {

MindVisionCameraInstance *MindVisionCamera::instance = new MindVisionCameraInstance();

MindVisionCamera::MindVisionCamera(QObject *parent) : Camera(parent)
{

}

// 枚举所有设备序列号
QStringList MindVisionCamera::enumerateDevicesSerial()
{
    QList<tSdkCameraDevInfo> deviceList; QString errMsg;
    bool ret = instance->enumDevices(true, deviceList, errMsg);
    if (!ret) {
        setError(errMsg);
        return QStringList();
    }

    QStringList devices;
    for (const auto &info : qAsConst(deviceList)) {
        devices.append(info.acSn);
    }
    return devices;
}

bool MindVisionCamera::attachBySerial(const QString &serial)
{
    detach();

    QWriteLocker locker(&_lock);
    CameraSdkStatus status;

    // 根据序列号找到相机
    QString errMsg;
    auto deviceInfo = instance->findCameraBySerial(false, serial, errMsg);
    if (deviceInfo.acSn != serial) {
        deviceInfo = instance->findCameraBySerial(true, serial, errMsg);
    }
    if (deviceInfo.acSn != serial) {
        setError(errMsg);
        return false;
    }

    // (-1,-1)表示加载上次退出前保存的参数，如果是第一次使用该相机，则加载默认参数。
    // (-1,-1) means to load the parameters saved before the last exit. If it is the first time to use the camera, then load the default parameters.
    status = CameraInit(&deviceInfo, -1, -1, &hCamera);
    MV_ERR_RETURN(status, tr("Failed to init the camera"), false);

    // 从相机获取设备枚举信息
    // You can get device enumeration information from the camera because you did not get the device list before
    tSdkCameraDevInfo DevInfo;
    CameraGetEnumInfo(hCamera, &DevInfo);
    _sn = DevInfo.acSn;

    // 获得该相机的特性描述
    // Get the camera's feature description
    tSdkCameraCapbility CameraInfo;
    CameraGetCapability(hCamera, &CameraInfo);

    // 判断是黑白相机还是彩色相机
    // Judging whether it is a mono camera or a color camera
    auto bMonoCamera = CameraInfo.sIspCapacity.bMonoSensor;

    // 黑白相机让ISP直接输出MONO数据，而不是扩展成R=G=B的24位灰度
    // Mono cameras allow the ISP to directly output MONO data instead of the 24-bit grayscale expanded to R=G=B
    if (bMonoCamera) {
        CameraSetIspOutFormat(hCamera, CAMERA_MEDIA_TYPE_MONO8);
    } else {
        CameraSetIspOutFormat(hCamera, CAMERA_MEDIA_TYPE_RGB8);
    }

    // 设置相机为软触发模式，并且把一次触发的帧数固定为1
    // Set the camera to soft trigger mode and fix the number of frames triggered at one time to 1
    CameraSetTriggerMode(hCamera, SOFT_TRIGGER);
    CameraSetTriggerCount(hCamera, 1);

    // 计算RGB buffer所需的大小，这里直接按照相机的最大分辨率来分配
    UINT FrameBufferSize = CameraInfo.sResolutionRange.iWidthMax * CameraInfo.sResolutionRange.iHeightMax * (bMonoCamera ? 1 : 3);

    // 分配RGB buffer，用来存放ISP输出的图像
    // 备注：从相机传输到PC端的是RAW数据，在PC端通过软件ISP转为RGB数据（如果是黑白相机就不需要转换格式，但是ISP还有其它处理，所以也需要分配这个buffer）
    // allocate RGB buffer to store the image output by ISP
    // Note: RAW data is transferred from the camera to the PC and converted to RGB data via the software ISP on the PC (if it is a Mono camera, there is no need to convert the format, but the ISP has other processing, so we also need to allocate this buffer)
    pFrameBuffer = (BYTE *) CameraAlignMalloc(FrameBufferSize, 16);

    /***
     * 关闭自动校正正并执行一次快速温度矫正
     * 自动校正：大概10秒钟就执行一次，执行期间图像将停留在校正前的数据
     * 为避免对节拍产生影响，这里在连接相机时执行一次快速校正，
     * 然后每次拍照后再执行一次快速校正，以兼顾准确性和节拍
     */
    CameraSpecialControl(hCamera, SET_STOP_CORRECT, STOP_CORRECT_ENABLE,0);
    CameraSpecialControl(hCamera, SET_TEMP_FAST_CHECK, 0, 0);

    // 让SDK内部取图线程开始工作
    // Let the SDK internal grab thread start working
    status = CameraPlay(hCamera);
    MV_ERR_RETURN(status, tr("CameraPlay failed"), false);

    return true;
}

bool MindVisionCamera::detach()
{
    QWriteLocker locker(&_lock);
    _sn.clear();

    CameraPause(hCamera);

    // 关闭相机
    // close camera
    CameraUnInit(hCamera);

    // release RGB buffer
    if (pFrameBuffer != nullptr) {
        CameraAlignFree(pFrameBuffer);
        pFrameBuffer = nullptr;
    }

    return true;
}

// 拍照
QImage MindVisionCamera::grab()
{
    QWriteLocker locker(&_lock);
    CameraSdkStatus status;

    // 从相机取一帧图片
    // Take a frame from the camera
    tSdkFrameHead FrameHead;
    BYTE* pRawData;

    // 由于相机目前处于软触发模式，需要软件发送指令通知相机拍照（为了避免意外取到相机缓存中的旧图片，在给触发指令前先清空了缓存）
    // Since the camera is currently in soft trigger mode, software is required to send a command to inform the camera to take pictures (to avoid accidentally fetching old pictures in the camera cache, the cache is cleared before the trigger command)
    CameraClearBuffer(hCamera);
    CameraSoftTrigger(hCamera);

    QImage image;
    status = CameraGetImageBuffer(hCamera, &FrameHead, &pRawData, 3000);
    if (status == CAMERA_STATUS_SUCCESS)
    {
        // 将获得的相机原始输出图像数据进行处理，叠加饱和度、颜色增益和校正、降噪等处理效果
        CameraImageProcess(hCamera, pRawData, pFrameBuffer, &FrameHead);

        // 由于SDK输出的数据默认是从底到顶的，转换为图片需要做一下垂直镜像
        CameraFlipFrameBuffer(pFrameBuffer, &FrameHead, 1);

        if (FrameHead.uiMediaType == CAMERA_MEDIA_TYPE_MONO8) {
            image = QImage(pFrameBuffer, FrameHead.iWidth, FrameHead.iHeight, QImage::Format_Indexed8);
        } else {
            image = QImage((const uchar*) pFrameBuffer, FrameHead.iWidth, FrameHead.iHeight, QImage::Format_RGB888);
        }
        image = image.copy();

        // 在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
        // 否则再次调用CameraGetImageBuffer时，程序将被挂起，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
        CameraReleaseImageBuffer(hCamera, pRawData);
    } else {
        setError(MindVisionCameraInstance::formatErrorMsg(status, tr("Grab failed")));
    }

    /***
     * 执行一次快速温度矫正
     * 注意：这个函数非阻塞，大概需要几十个毫秒。矫正期间拍照可能存在问题
     *
     * 获取快门状态 快门已经打开说明校正完成
     * int shutter_status = 0;
     * CameraSpecialControl(g_hCamera, GET_SHUTTER_MODE,0,&shutter_status);
     */
    CameraSpecialControl(hCamera, SET_TEMP_FAST_CHECK, 0, 0);

    return image;
}

QString MindVisionCamera::serialNumber()
{
    return _sn;
}

bool MindVisionCamera::setIOEnable(const bool &isEnable)
{
    Q_UNUSED(isEnable);
    // TODO
    return false;
}

bool MindVisionCamera::setPacketSize(const int &packetSize)
{
    Q_UNUSED(packetSize);
    // TODO
    return false;
}

bool MindVisionCamera::setExposureTime(const qreal &expTime)
{
    QWriteLocker locker(&_lock);

    CameraPause(hCamera);
    if (qFuzzyIsNull(expTime)) {
        CameraSetAeState(hCamera, true);
    } else {
        CameraSetAeState(hCamera, false);
        CameraSetExposureTime(hCamera, expTime);
    }
    CameraPlay(hCamera);

    return true;
}

}   // namespace SpeedCamera
