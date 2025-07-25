/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       IKapCamera.cpp
 * @brief      埃科光电相机
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2025/02/19
 *
 * @history
 * - 2025/02/19 模块创建
 *****************************************************************************/

#include "IKapCamera.h"

#include <QDebug>

// 相机操作：如果遇到错误则记录错误日志
#define IKAP_ERR_CHECK(CODE, MSG) \
    do { \
        if (ITKSTATUS_OK != CODE) { \
            setError(IKapInstance::formatErrorMsg(CODE, MSG)); \
        } \
    } while (0)

// 相机操作：如果遇到错误则返回
#define IKAP_ERR_RETURN(CODE, MSG, RET) \
    do { \
        if (ITKSTATUS_OK != CODE) { \
            setError(IKapInstance::formatErrorMsg(CODE, MSG)); \
            return RET; \
        } \
    } while (0)

// 采集卡操作：如果遇到错误则返回
#define BOARD_ERR_RETURN(CODE, MSG, RET) \
    do { \
        if (IK_RTN_OK != CODE) { \
            setError(IKapInstance::formatBoardErrorMsg(CODE, MSG)); \
            return RET; \
        } \
    } while (0)

// 相机掉线回调
void _stdcall removalCallbackFunction(void *context, ITKEVENTINFO eventInfo)
{
    uint32_t type = 0;
    ITKSTATUS res = ItkEventInfoGetPrm(eventInfo, ITKEVENTINFO_PRM_TYPE, &type);
    Q_UNUSED(res);

    qWarning() << "[埃科光电相机] 设备掉线";

    auto *camera = (SpeedCamera::IKapCamera *) context;
    if (camera != nullptr) {
        emit camera->cameraDisconnected();
    }
}

// 本函数被注册为一个回调函数。当图像采集开始时，函数被调用
void CALLBACK OnGrabStart(void *pContext)
{
    Q_UNUSED(pContext);
    //printf("Start grabbing image.\n");
}

// 本函数被注册为一个回调函数。当一帧图像采集完成时，函数被调用
void CALLBACK OnFrameReady(void *pContext)
{
    auto *camera = (SpeedCamera::IKapCamera *) pContext;
    if (camera != nullptr) {
        camera->onFrameReady();
    }
}

// 本函数被注册为一个回调函数。当图像采集超时时，函数被调用
void CALLBACK OnTimeout(void *pContext)
{
    Q_UNUSED(pContext);
    //printf("Grab image timeout.\n");
}

// 本函数被注册为一个回调函数。当采集丢帧时，函数被调用
void CALLBACK OnFrameLost(void *pContext)
{
    Q_UNUSED(pContext);
    //printf("Grab frame lost.\n");
}

// 本函数被注册为一个回调函数。当图像采集停止时，函数被调用
void CALLBACK OnGrabStop(void *pContext)
{
    Q_UNUSED(pContext);
    //printf("Stop grabbing image.\n");
}

/******************************************************************************/

namespace SpeedCamera {

IKapInstance IKapCamera::instance;

IKapCamera::IKapCamera(QObject *parent)
    : Camera(parent)
{
    //
}

// 查询所有连接的设备
QStringList IKapCamera::enumerateDevicesSerial()
{
    uint32_t camNum = 0;
    uint32_t camIndex = 0;

    auto res = ItkManGetDeviceCount(&camNum);
    IKAP_ERR_CHECK(res, "ItkManGetDeviceCount");

    QStringList serialList;
    for (camIndex = 0; camIndex < camNum; ++camIndex) {
        ITKDEV_INFO di;
        res = ItkManGetDeviceInfo(camIndex, &di);
        if (ITKSTATUS_OK != res) {
            setError(IKapInstance::formatErrorMsg(res, "ItkManGetDeviceInfo"));
            continue;
        }
        serialList << QString::fromUtf8(di.SerialNumber);
    }

    serialList.removeDuplicates();
    serialList.removeAll("");

    return serialList;
}

bool IKapCamera::attachBySerial(const QString &serial)
{
    uint32_t camNum = 0;
    uint32_t camIndex = 0;

    auto res = ItkManGetDeviceCount(&camNum);
    IKAP_ERR_CHECK(res, "ItkManGetDeviceCount");

    QStringList serialList;
    for (camIndex = 0; camIndex < camNum; ++camIndex) {
        ITKDEV_INFO di;
        res = ItkManGetDeviceInfo(camIndex, &di);
        if (ITKSTATUS_OK != res) {
            continue;
        }

        const auto serialNum = QString::fromUtf8(di.SerialNumber);
        if (serialNum != serial) {
            continue;
        }

        // 找到了，开始连接
        auto res = ItkDevOpen(camIndex, ITKDEV_VAL_ACCESS_MODE_EXCLUSIVE, &hCamera);
        IKAP_ERR_RETURN(res, "ItkDevOpen", false);

        // 注册相机回调事件
        res = ItkDevRegisterCallback(hCamera, "DeviceRemove", removalCallbackFunction, this);
        IKAP_ERR_CHECK(res, "ItkDevRegisterCallback");

        // GigEVision 相机处理
        if (strcmp(di.DeviceClass, "GigEVision") == 0) {
            ITKGIGEDEV_INFO gvInfo;

            // 获取GigEVision相机设备信息。
            res = ItkManGetGigEDeviceInfo(camIndex, &gvInfo);
        }

        // GigEVision 采集卡处理
        if (strcmp(di.DeviceClass, "GigEVisionBoard") == 0) {
            ITK_GVB_DEV_INFO gvb_cam_info;
            IKAP_GVB_BOARD_INFO gvb_board_info;

            // 获取GigEVision相机设备信息。
            res = ItkManGetGVBDeviceInfo(camIndex, &gvb_cam_info);

            // 打开采集卡。
            memcpy(&gvb_board_info, &gvb_cam_info, sizeof gvb_cam_info);
            hBoard = IKapOpenGVB(IKBoardPCIE, gvb_board_info.BoardIndex, gvb_board_info);
            if (hBoard == INVALID_HANDLE_VALUE) {
                setError(tr("Fail to open board"));
                return false;
            }

            configureBoard();
        }

        // CoaXPress 采集卡处理
        if (strcmp(di.DeviceClass, "CoaXPress") == 0) {
            ITK_CXP_DEV_INFO cxp_cam_info;
            IKAP_CXP_BOARD_INFO cxp_board_info;

            // 获取CoaXPress相机设备信息。
            res = ItkManGetCXPDeviceInfo(camIndex, &cxp_cam_info);

            // 打开采集卡。
            memcpy(&cxp_board_info, &cxp_cam_info, sizeof cxp_cam_info);
            hBoard = IKapOpenCXP(IKBoardPCIE, cxp_board_info.BoardIndex, cxp_board_info);
            if (hBoard == INVALID_HANDLE_VALUE) {
                setError(tr("Fail to open board"));
                return false;
            }

            configureBoard();
        }

        _serial = serial;
        return true;
    }

    setError(tr("Camera %1 not found!").arg(serial));
    return false;
}

// 设置采集卡配置问界
QString IKapCamera::configFile() const
{
    return _configFile;
}

void IKapCamera::setConfigFile(const QString &configFile)
{
    _configFile = configFile;
}

// 配置采集卡设备
bool IKapCamera::configureBoard()
{
    int ret = IK_RTN_OK;
    auto configFilename = _configFile.toLocal8Bit();

    // 导入配置文件  *.vlcf
    ret = IKapLoadConfigurationFromFile(hBoard, configFilename.data());
    BOARD_ERR_RETURN(ret, "IKapLoadConfigurationFromFile", false);

    // 获取图像宽度
    ret = IKapGetInfo(hBoard, IKP_IMAGE_WIDTH, &g_nWidth);
    BOARD_ERR_RETURN(ret, "IKapGetInfo IKP_IMAGE_WIDTH", false);

    // 获取图像高度
    ret = IKapGetInfo(hBoard, IKP_IMAGE_HEIGHT, &g_nHeight);
    BOARD_ERR_RETURN(ret, "IKapGetInfo IKP_IMAGE_HEIGHT", false);

    // 设置图像缓冲区帧数
    int BOARD_FRMAE_COUNT = 1;
    ret = IKapSetInfo(hBoard, IKP_FRAME_COUNT, BOARD_FRMAE_COUNT);
    BOARD_ERR_RETURN(ret, "IKapSetInfo IKP_FRAME_COUNT", false);

    // 设置超时时间
    int timeout = -1;
    ret = IKapSetInfo(hBoard, IKP_TIME_OUT, timeout);
    BOARD_ERR_RETURN(ret, "IKapSetInfo IKP_TIME_OUT", false);

    // 设置采集模式
    int grab_mode = IKP_GRAB_NON_BLOCK;
    ret = IKapSetInfo(hBoard, IKP_GRAB_MODE, grab_mode);
    BOARD_ERR_RETURN(ret, "IKapSetInfo IKP_GRAB_MODE", false);

    // 设置传输模式
    int transfer_mode = IKP_FRAME_TRANSFER_SYNCHRONOUS_NEXT_EMPTY_WITH_PROTECT;
    ret = IKapSetInfo(hBoard, IKP_FRAME_TRANSFER_MODE, transfer_mode);
    BOARD_ERR_RETURN(ret, "IKapSetInfo IKP_FRAME_TRANSFER_MODE", false);

    // 注册回调函数
    ret = IKapRegisterCallback(hBoard, IKEvent_GrabStart, OnGrabStart, this);
    BOARD_ERR_RETURN(ret, "IKapRegisterCallback IKEvent_GrabStart", false);
    ret = IKapRegisterCallback(hBoard, IKEvent_FrameReady, OnFrameReady, this);
    BOARD_ERR_RETURN(ret, "IKapRegisterCallback IKEvent_FrameReady", false);
    ret = IKapRegisterCallback(hBoard, IKEvent_FrameLost, OnFrameLost, this);
    BOARD_ERR_RETURN(ret, "IKapRegisterCallback IKEvent_FrameLost", false);
    ret = IKapRegisterCallback(hBoard, IKEvent_TimeOut, OnTimeout, this);
    BOARD_ERR_RETURN(ret, "IKapRegisterCallback IKEvent_TimeOut", false);
    ret = IKapRegisterCallback(hBoard, IKEvent_GrabStop, OnGrabStop, this);
    BOARD_ERR_RETURN(ret, "IKapRegisterCallback IKEvent_GrabStop", false);

    return true;
}

bool IKapCamera::detach()
{
    // 取消采集卡回调函数
    ret = IKapUnRegisterCallback(hBoard, IKEvent_GrabStart);
    ret = IKapUnRegisterCallback(hBoard, IKEvent_FrameReady);
    ret = IKapUnRegisterCallback(hBoard, IKEvent_FrameLost);
    ret = IKapUnRegisterCallback(hBoard, IKEvent_TimeOut);
    ret = IKapUnRegisterCallback(hBoard, IKEvent_GrabStop);

    // 关闭采集卡
    ret = IKapClose(hBoard);

    res = ItkDevUnregisterCallback(hCamera, "DeviceRemove");
    IKAP_ERR_CHECK(res, "ItkDevUnregisterCallback");

    res = ItkDevClose(hCamera);
    IKAP_ERR_RETURN(res, "ItkDevClose", false);

    _serial = QString();
    return true;
}

QImage IKapCamera::grab()
{
    // TODO
    return QImage();
}

QString IKapCamera::serialNumber()
{
    return _serial;
}

bool IKapCamera::setIOEnable(const bool &isEnable)
{
    return Camera::setIOEnable(isEnable);
}

bool IKapCamera::setPacketSize(const int &packetSize)
{
    return Camera::setPacketSize(packetSize);
}

bool IKapCamera::setExposureTime(const qreal &expTime)
{
    return Camera::setExposureTime(expTime);
}

// 开始图像采集
bool IKapCamera::startGrabbing()
{
    ITKSTATUS res = ITKSTATUS_OK;
    int ret = IK_RTN_OK;

    res = ItkDevExecuteCommand(hCamera, "AcquisitionStop");
    IKAP_ERR_RETURN(res, "ItkDevExecuteCommand AcquisitionStop", false);

    ret = IKapStartGrab(hBoard, 0);
    BOARD_ERR_RETURN(ret, "IKapStartGrab", false);

    res = ItkDevExecuteCommand(hCamera, "AcquisitionStart");
    IKAP_ERR_RETURN(res, "ItkDevExecuteCommand AcquisitionStart", false);

    return true;
}

// 停止图像采集
bool IKapCamera::stopGrabbing()
{
    ret = IKapStopGrab(hBoard);
    BOARD_ERR_RETURN(ret, "IKapStopGrab", false);

    return true;
}

// 收到了一帧
void IKapCamera::onFrameReady()
{
    HANDLE hDev = hBoard;
    unsigned char *pUserBuffer = NULL;
    int nFrameSize = 0;
    int nFrameCount = 0;
    int nFrameIndex = 0;
    IKAPBUFFERSTATUS status;

    IKapGetInfo(hDev, IKP_FRAME_COUNT, &nFrameCount);
    IKapGetInfo(hDev, IKP_CURRENT_BUFFER_INDEX, &nFrameIndex);
    IKapGetBufferStatus(hDev, nFrameIndex, &status);

    // 当图像缓冲区满时
    if (status.uFull == 1) {
        // 获取一帧图像的大小
        IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);

        // 获取缓冲区地址
        IKapGetBufferAddress(hDev, nFrameIndex, (void **) &pUserBuffer);

        // 保存图像
        //IKapSaveBuffer(hDev, nFrameIndex, "1.tiff", IKP_DEFAULT_COMPRESSION);

        auto image = toQImage(pUserBuffer);
        setImage(image);
    }
}

// 转换为 QImage
QImage IKapCamera::toQImage(unsigned char *pData)
{
    int nImageType = -1;
    int ret = IKapGetInfo(hBoard, IKP_IMAGE_TYPE, &nImageType);
    BOARD_ERR_RETURN(ret, "IKapGetInfo IKP_IMAGE_TYPE", QImage());

    // RGB
    if (nImageType == 1) {
        // 直接返回 QImage，pData 作为 RGB 图像的数据源
        return QImage(pData, g_nWidth, g_nHeight, g_nWidth * 3, QImage::Format_RGB888);
    }

    // Bayer
    else if (nImageType == 0) {
        int nBayerPattern = -1;

        ret = IKapGetInfo(hBoard, IKP_BAYER_PATTERN, &nBayerPattern);
        BOARD_ERR_RETURN(ret, "IKapGetInfo IKP_BAYER_PATTERN", QImage());

        unsigned char *pConvertedData = nullptr;
        int width = g_nWidth;
        int height = g_nHeight;

        if (nBayerPattern == 1) // BGGR
        {
            // 这里进行色彩转换（BGGR -> RGB）
            pConvertedData = new unsigned char[width * height * 3];
            for (int y = 0; y < height - 1; y++) {
                for (int x = 0; x < width - 1; x++) {
                    // 使用简单的 BGGR 模式转换为 RGB
                    int index = (y * width + x) * 1;
                    int r = pData[index];
                    int g = (pData[index + 1] + pData[index + width]) / 2;
                    int b = pData[index + 2];

                    // 将 RGB 值存储在 pConvertedData 中
                    pConvertedData[(y * width + x) * 3] = r;
                    pConvertedData[(y * width + x) * 3 + 1] = g;
                    pConvertedData[(y * width + x) * 3 + 2] = b;
                }
            }
        } else if (nBayerPattern == 2) // RGGB
        {
            // 进行 RGGB -> RGB 转换
            pConvertedData = new unsigned char[width * height * 3];
            for (int y = 0; y < height - 1; y++) {
                for (int x = 0; x < width - 1; x++) {
                    // 使用简单的 RGGB 模式转换为 RGB
                    int index = (y * width + x) * 1;
                    int r = pData[index];
                    int g = (pData[index + 1] + pData[index + width]) / 2;
                    int b = pData[index + 2];

                    // 将 RGB 值存储在 pConvertedData 中
                    pConvertedData[(y * width + x) * 3] = r;
                    pConvertedData[(y * width + x) * 3 + 1] = g;
                    pConvertedData[(y * width + x) * 3 + 2] = b;
                }
            }
        } else if (nBayerPattern == 3) // GBRG
        {
            // 进行 GBRG -> RGB 转换
            pConvertedData = new unsigned char[width * height * 3];
            for (int y = 0; y < height - 1; y++) {
                for (int x = 0; x < width - 1; x++) {
                    // 使用简单的 GBRG 模式转换为 RGB
                    int index = (y * width + x) * 1;
                    int r = pData[index];
                    int g = (pData[index + 1] + pData[index + width]) / 2;
                    int b = pData[index + 2];

                    // 将 RGB 值存储在 pConvertedData 中
                    pConvertedData[(y * width + x) * 3] = r;
                    pConvertedData[(y * width + x) * 3 + 1] = g;
                    pConvertedData[(y * width + x) * 3 + 2] = b;
                }
            }
        } else if (nBayerPattern == 4) // GRBG
        {
            // 进行 GRBG -> RGB 转换
            pConvertedData = new unsigned char[width * height * 3];
            for (int y = 0; y < height - 1; y++) {
                for (int x = 0; x < width - 1; x++) {
                    // 使用简单的 GRBG 模式转换为 RGB
                    int index = (y * width + x) * 1;
                    int r = pData[index];
                    int g = (pData[index + 1] + pData[index + width]) / 2;
                    int b = pData[index + 2];

                    // 将 RGB 值存储在 pConvertedData 中
                    pConvertedData[(y * width + x) * 3] = r;
                    pConvertedData[(y * width + x) * 3 + 1] = g;
                    pConvertedData[(y * width + x) * 3 + 2] = b;
                }
            }
        } else // Mono
        {
            // 灰度图像
            pConvertedData = new unsigned char[width * height];
            memcpy(pConvertedData, pData, width * height);
        }

        // 创建 QImage 对象
        QImage image(pConvertedData, width, height, width * 3, QImage::Format_RGB888);

        // 清理内存
        delete[] pConvertedData;

        return image;
    } else {
        return QImage();
    }
}

} // namespace SpeedCamera
