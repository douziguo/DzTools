/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       HikCamera.cpp
 * @brief      海康相机功能封装
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2022/06/09
 *
 * @history
 * - 2022/06/09 模块创建
 *****************************************************************************/

#include "HikCamera.h"
#include "HikInstance.h"

#include <QDebug>

// 相机操作：如果遇到错误则返回
#define HIK_ERR_RETURN(CODE, MSG, RET) \
    do { \
        if (MV_OK != CODE) { \
            setError(HikInstance::formatErrorMsg(CODE, MSG)); \
            return RET; \
        } \
    } while (0)

// 海康相机开始设置：检查句柄、停止取流，加锁
#define HIK_BEGIN_SET \
    if (!checkHandle()) \
        return false; \
    bool grabbing = isGrabbing(); \
    if (grabbing) { \
        stopGrabbing(); \
    } \
    { \
        QWriteLocker locker(&_lock); \
        int nRet = -1; \
        Q_UNUSED(nRet)

// 海康结束设置：恢复取流，返回操作成功
#define HIK_END_SET \
    } \
    if (grabbing) \
        startGrabbing(); \
    return true;

// 图片接收回调
void __stdcall hikImageCallBackEx(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
    auto *camera = (SpeedCamera::HikCamera *) pUser;
    if (pFrameInfo && camera) {
        QImage image;
        SpeedCamera::HikInstance::dataToImage(camera->hikHandle(), pData, pFrameInfo, image);
        camera->setImage(image);
    }
}

// 异常回调
void __stdcall hikExceptionCallBack(unsigned int nMsgType, void *pUser)
{
    auto *camera = (SpeedCamera::HikCamera *) pUser;
    if (nMsgType == MV_EXCEPTION_DEV_DISCONNECT) {
        qWarning() << "[海康相机] MV_EXCEPTION_DEV_DISCONNECT 设备掉线";
        camera->handleDisconnect();
        emit camera->cameraDisconnected();
    } else {
        printf("[海康相机] Unknown exception 0x[%x] ", nMsgType);
    }
}

namespace SpeedCamera {

HikCamera::HikCamera(QObject *parent)
    : Camera(parent)
{
    hik = HikInstance::getInstance();
}

HikCamera::~HikCamera()
{
    /***
     * 海康相机如果未及时释放，会出现占用问题
     * 参考资料：https://blog.csdn.net/qq_39570716/article/details/114270134
     */
    detach();
}

// 枚举所有的可用设备
QStringList HikCamera::enumerateDevicesSerial()
{
    QStringList serials;

    MV_CC_DEVICE_INFO_LIST stDeviceList;
    QString errMsg;
    const bool ret = hik->enumDevices(true, stDeviceList, errMsg);
    if (!ret) {
        setError(errMsg);
        return serials;
    }

    for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++) {
        MV_CC_DEVICE_INFO *pDeviceInfo = stDeviceList.pDeviceInfo[i];
        if (NULL == pDeviceInfo)
            continue;

        QString serial;
        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
            serial = reinterpret_cast<char *>(pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
        } else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE) {
            serial = reinterpret_cast<char *>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        }

        if (!serial.isEmpty()) {
            serials.append(serial);
        }
    }

    serials.removeDuplicates();
    return serials;
}

// 根据序列号加载设备
bool HikCamera::attachBySerial(const QString &serial)
{
    detach();

    // 根据序列号找到相机
    QString errMsg;
    auto *deviceInfo = hik->findCameraBySerial(false, serial, errMsg);
    if (deviceInfo == nullptr) {
        deviceInfo = hik->findCameraBySerial(true, serial, errMsg);
    }

    if (deviceInfo == nullptr) {
        setError(errMsg);
        return false;
    }

    int nRet;

    // ch:选择设备并创建句柄 | en:Select device and create handle
    nRet = MV_CC_CreateHandle(&handle, deviceInfo);
    HIK_ERR_RETURN(nRet, tr("Create Handle fail"), false);

    // ch:打开设备 | en:Open device
    nRet = MV_CC_OpenDevice(handle);
    HIK_ERR_RETURN(nRet, tr("Open Device fail"), false);

    // 注册异常回调 Register disconnected exception callBack
    nRet = MV_CC_RegisterExceptionCallBack(handle, hikExceptionCallBack, this);
    if (MV_OK != nRet) {
        printf("[海康相机] RegisterExceptionCallBack fail! nRet [0x%x]\n", nRet);
    }

    // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    if (deviceInfo->nTLayerType == MV_GIGE_DEVICE) {
        int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
        if (nPacketSize > 0) {
            nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
            if (nRet != MV_OK) {
                printf("[海康相机] Set Packet Size fail nRet [0x%x]!", nRet);
            }
        } else {
            printf("[海康相机] Get Packet Size fail nRet [0x%x]!", nPacketSize);
        }
    }

    // 设置软触发
    bool ret = setTriggerMode(SoftwareTriggering);
    if (!ret)
        return false;

    _serial = serial;
    return true;
}

// 断开设备的连接
bool HikCamera::detach()
{
    if (!isAttached()) {
        return true;
    }

    int nRet;

    stopGrabbing();

    // ch:关闭设备 | Close device
    nRet = MV_CC_CloseDevice(handle);
    HIK_ERR_RETURN(nRet, tr("CloseDevice fail"), false);

    // ch:销毁句柄 | Destroy handle
    nRet = MV_CC_DestroyHandle(handle);
    HIK_ERR_RETURN(nRet, tr("Destroy Handle fail"), false);

    handle = nullptr;
    _serial = QString();

    return true;
}

// 掉线处理：释放资源，解决掉线后相机出现的函数调用顺序报错
// 注：测试功能，后续可能回退处理
void HikCamera::handleDisconnect()
{
    MV_CC_CloseDevice(handle);
    MV_CC_DestroyHandle(handle);
    handle = nullptr;
}

// 截取一张图像
QImage HikCamera::grab()
{
    if (!checkHandle())
        return QImage();

    if (!startGrabbing()) {
        return QImage();
    }

    QWriteLocker locker(&_lock);
    QImage image;
    int nRet = MV_OK;
    MV_FRAME_OUT stOutFrame = {0};

    // 软触发
    nRet = MV_CC_SetCommandValue(handle, "TriggerSoftware");
    HIK_ERR_RETURN(nRet, tr("Set Software Trigger Fail"), QImage());

    // 因为刚开启抓取就在尝试取数据，只取一次可能会返回 MV_CODEREADER_E_NODATA，这里多尝试几次
    int retryCount = 0;
    do {
        nRet = MV_CC_GetImageBuffer(handle, &stOutFrame, 1000);
    } while ((++retryCount < 10) && (nRet != MV_OK));

    if (nRet == MV_OK) {
        HikInstance::dataToImage(handle, stOutFrame.pBufAddr, &stOutFrame.stFrameInfo, image);

        nRet = MV_CC_FreeImageBuffer(handle, &stOutFrame);
        if (nRet != MV_OK) {
            qWarning() << "[HikCamera] Free Image Buffer fail! nRet " << nRet;
        }
    } else {
        setError(HikInstance::formatErrorMsg(nRet, tr("Get Image fail")));
    }

    return image;
}

// 获取当前连接设备的序列号
QString HikCamera::serialNumber()
{
    if (!checkHandle())
        return QString();
    return _serial;
}

// 检查相机 handle 是否为空
bool HikCamera::checkHandle()
{
    if (handle == nullptr) {
        setError(tr("Hik Handle Is Null!"));
        return false;
    }
    return true;
}

// 判断相机是否已连接
bool HikCamera::isAttached() const
{
    return (handle != nullptr);
}

/****************************************************/

// 控制 I/O 量
// TODO: 待实现
bool HikCamera::setIOEnable(const bool &isEnable)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle())
        return false;

    // TODO
    Q_UNUSED(isEnable);

    return false;
}

// 修改包大小
bool HikCamera::setPacketSize(const int &packetSize)
{
    stopGrabbing();
    QWriteLocker locker(&_lock);

    int nRet = MV_CC_SetIntValueEx(handle, "GevSCPSPacketSize", packetSize);
    HIK_ERR_RETURN(nRet, tr("Set Packet Size fail"), false);

    return true;
}

// 设置曝光时间
bool HikCamera::setExposureTime(const qreal &expTime)
{
    HIK_BEGIN_SET;

    if (qFuzzyIsNull(expTime)) {
        nRet = MV_CC_SetEnumValue(handle, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_CONTINUOUS);
        HIK_ERR_RETURN(nRet, tr("Set ExposureAuto fail"), false);
    } else {
        // ch:调节这两个曝光模式，才能让曝光时间生效
        // en:Adjust these two exposure mode to allow exposure time effective
        nRet = MV_CC_SetEnumValue(handle, "ExposureMode", MV_EXPOSURE_MODE_TIMED);
        HIK_ERR_RETURN(nRet, tr("Set ExposureMode fail"), false);

        MV_CC_SetEnumValue(handle, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

        nRet = MV_CC_SetFloatValue(handle, "ExposureTime", expTime);
        HIK_ERR_RETURN(nRet, tr("Set ExposureTime fail"), false);
    }

    HIK_END_SET;
}

// 设置数字移位
bool HikCamera::setDigitalShift(const qreal digitalShift)
{
    HIK_BEGIN_SET;

    nRet = MV_CC_SetBoolValue(handle, "DigitalShiftEnable", true);
    HIK_ERR_RETURN(nRet, tr("Set DigitalShiftEnable fail"), false);

    nRet = MV_CC_SetFloatValue(handle, "DigitalShift", digitalShift);
    HIK_ERR_RETURN(nRet, tr("Set DigitalShift fail"), false);

    HIK_END_SET;
}

// 设置增益
bool HikCamera::setGain(const qreal gain)
{
    HIK_BEGIN_SET;

    // ch:设置增益前先把自动增益关闭，失败无需返回
    //en:Set Gain after Auto Gain is turned off, this failure does not need to return
    MV_CC_SetEnumValue(handle, "GainAuto", MV_GAIN_MODE_OFF);

    nRet = MV_CC_SetFloatValue(handle, "Gain", gain);
    HIK_ERR_RETURN(nRet, tr("Set Gain fail"), false);

    HIK_END_SET;
}

// 设置触发模式
bool HikCamera::setTriggerMode(TriggerMode triggerMode)
{
    stopGrabbing();
    QWriteLocker locker(&_lock);

    int nRet;

    switch (triggerMode) {
    case SoftwareTriggering: {
        // ch:设置触发模式为 ON | en:Set trigger mode as ON
        nRet = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_ON);
        HIK_ERR_RETURN(nRet, tr("Set Trigger Mode fail"), false);

        // 设置软触发
        nRet = MV_CC_SetEnumValue(handle, "TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
        HIK_ERR_RETURN(nRet, tr("Set Software Trigger Fail"), false);

        return true;
    }
    case HardwareTriggering: {
        // ch:设置触发模式为 ON | en:Set trigger mode as ON
        nRet = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_ON);
        HIK_ERR_RETURN(nRet, tr("Set TriggerMode fail"), false);

        // 设置触发 IO
        nRet = MV_CC_SetEnumValue(handle, "TriggerSource", MV_TRIGGER_SOURCE_LINE0);
        HIK_ERR_RETURN(nRet, tr("Set TriggerSource fail"), false);

        // 注册回调函数
        nRet = MV_CC_RegisterImageCallBackEx(handle, hikImageCallBackEx, this);
        HIK_ERR_RETURN(nRet, tr("Register image callback fail"), false);

        _lock.unlock();

        // ch:开始取流 | en:Start grab image
        startGrabbing();

        return true;
    }
    }

    return Camera::setTriggerMode(triggerMode);
}

// 是否在取流中
bool HikCamera::isGrabbing() const
{
    QReadLocker locker(&_lock);
    return _isGrabbing;
}

// ch:开始取流 | en:Start grab image
bool HikCamera::startGrabbing()
{
    if (isGrabbing())
        return true;
    QWriteLocker locker(&_lock);

    auto nRet = MV_CC_StartGrabbing(handle);
    HIK_ERR_RETURN(nRet, tr("Start Grabbing Fail"), false);

    _isGrabbing = true;
    return true;
}

// ch:停止取流 | en:Stop grab image
bool HikCamera::stopGrabbing()
{
    if (!isGrabbing())
        return true;
    QWriteLocker locker(&_lock);

    auto nRet = MV_CC_StopGrabbing(handle);
    HIK_ERR_RETURN(nRet, tr("Stop Grabbing Fail"), false);

    _isGrabbing = false;
    return true;
}

// 重置计数器
bool HikCamera::counterReset()
{
    QWriteLocker locker(&_lock);

    auto nRet = MV_CC_SetCommandValue(handle, "CounterReset");
    HIK_ERR_RETURN(nRet, "计数器重置失败", false);
    return true;
}

// 获取计数器值
int HikCamera::getCounterCurrentValue()
{
    QWriteLocker locker(&_lock);

    MVCC_INTVALUE_EX pstIntValue = {};
    auto nRet = MV_CC_GetIntValueEx(handle, "CounterCurrentValue", &pstIntValue);
    HIK_ERR_RETURN(nRet, "获取计数器值失败", -1);

    return pstIntValue.nCurValue;
}

} // namespace SpeedCamera
