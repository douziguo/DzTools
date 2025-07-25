/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       HikInstance.cpp
 * @brief      单例，用于维护全局的海康相机相关实例
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2022/06/09
 *
 * @history
 * - 2022/06/09 模块创建
 *****************************************************************************/

#include "HikInstance.h"

#include <QImage>
#include <QMap>

namespace SpeedCamera {

HikInstance::HikInstance(QObject *parent)
    : QObject(parent)
{}

HikInstance::~HikInstance() {}

// 枚举设备
bool HikInstance::enumDevices(bool refreshCache, MV_CC_DEVICE_INFO_LIST &deviceList, QString &errMsg)
{
    errMsg = QString();

    // 如果无需刷新，且存在缓存，则返回缓存的设备信息
    if (!refreshCache && (_cachedDeviceList.nDeviceNum > 0)) {
        deviceList = _cachedDeviceList;
        return true;
    }

    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet) {
        errMsg
            = QString(tr("Enum Devices fail! nRet [0x%1]")).arg(QString::number(nRet, 16).right(8));
        return false;
    }

    deviceList = stDeviceList;
    _cachedDeviceList = stDeviceList;
    return true;
}

// 根据序列号找到对应的相机
MV_CC_DEVICE_INFO *HikInstance::findCameraBySerial(
    bool refreshCache, const QString &serial, QString &errMsg)
{
    errMsg = QString();

    MV_CC_DEVICE_INFO_LIST stDeviceList;
    bool ret = enumDevices(refreshCache, stDeviceList, errMsg);
    if (!ret) {
        return nullptr;
    }

    for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++) {
        MV_CC_DEVICE_INFO *pDeviceInfo = stDeviceList.pDeviceInfo[i];
        if (NULL == pDeviceInfo)
            continue;

        QString _serial;
        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
            _serial = reinterpret_cast<char *>(pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
        } else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE) {
            _serial = reinterpret_cast<char *>(pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        }

        if (serial == _serial) {
            return pDeviceInfo;
        }
    }

    errMsg = tr("Device not found");
    return nullptr;
}

// 转换为图片
void HikInstance::dataToImage(
    void *handle, unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, QImage &image)
{
    if (pFrameInfo->enPixelType == PixelType_Gvsp_Mono8) {
        // 灰度图转化
        image = QImage(pData, pFrameInfo->nWidth, pFrameInfo->nHeight, QImage::Format_Grayscale8)
                    .copy();
    } else {
        // 彩色图转化
        const unsigned int nDataSizeForRGB = pFrameInfo->nWidth * pFrameInfo->nHeight * 3;

        unsigned char *pDataForRGB = NULL;
        pDataForRGB = (unsigned char *) malloc(nDataSizeForRGB);
        if (NULL != pDataForRGB) {
            // ch:像素格式转换 | en:Convert pixel format
            MV_CC_PIXEL_CONVERT_PARAM stConvertParam = {0};
            memset(&stConvertParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));

            stConvertParam.nWidth = pFrameInfo->nWidth;   //ch:图像宽 | en:image width
            stConvertParam.nHeight = pFrameInfo->nHeight; //ch:图像高 | en:image height
            stConvertParam.pSrcData = pData; //ch:输入数据缓存 | en:input data buffer
            stConvertParam.nSrcDataLen = pFrameInfo->nFrameLen; //ch:输入数据大小 | en:input data size
            stConvertParam.enSrcPixelType
                = pFrameInfo->enPixelType; //ch:输入像素格式 | en:input pixel format
            stConvertParam.enDstPixelType
                = PixelType_Gvsp_RGB8_Packed; //ch:输出像素格式 | en:output pixel format
            stConvertParam.pDstBuffer = pDataForRGB; //ch:输出数据缓存 | en:output data buffer
            stConvertParam.nDstBufferSize = nDataSizeForRGB; //ch:输出缓存大小 | en:output buffer size

            MV_CC_ConvertPixelType(handle, &stConvertParam);

            image = QImage(
                        stConvertParam.pDstBuffer,
                        pFrameInfo->nWidth,
                        pFrameInfo->nHeight,
                        QImage::Format_RGB888)
                        .copy();

            free(pDataForRGB);
        }
    }
}

// 解析错误信息
QString HikInstance::formatErrorMsg(int nErrorNum, const QString &msg)
{
    QString errorMsg = msg;

    if (nErrorNum != MV_OK) {
        if (!msg.isEmpty()) {
            errorMsg += tr(", ");
        }
        errorMsg += tr("Error = 0x%1: ").arg(QString::number(nErrorNum, 16).right(8));
    }

    QMap<uint, QString> errorDescs = {
        // 通用错误码定义:范围0x80000000-0x800000FF
        {MV_E_HANDLE, tr("Error or invalid handle")},
        {MV_E_SUPPORT, tr("Not supported function")},
        {MV_E_BUFOVER, tr("Buffer overflow")},
        {MV_E_CALLORDER, tr("Function calling order error")},
        {MV_E_PARAMETER, tr("Incorrect parameter")},
        {MV_E_RESOURCE, tr("Applying resource failed")},
        {MV_E_NODATA, tr("No data")},
        {MV_E_PRECONDITION, tr("Precondition error, or running environment changed")},
        {MV_E_VERSION, tr("Version mismatches")},
        {MV_E_NOENOUGH_BUF, tr("Insufficient memory")},
        {MV_E_ABNORMAL_IMAGE, tr("Abnormal image, maybe incomplete image because of lost packet")},
        {MV_E_LOAD_LIBRARY, tr("Load library failed")},
        {MV_E_NOOUTBUF, tr("No Avaliable Buffer")},
        {MV_E_ENCRYPT, tr("Encryption error")},
        {MV_E_UNKNOW, tr("Unknown error")},

        // GenICam系列错误:范围0x80000100-0x800001FF
        {MV_E_GC_GENERIC, tr("General error")},
        {MV_E_GC_ARGUMENT, tr("Illegal parameters")},
        {MV_E_GC_RANGE, tr("The value is out of range")},
        {MV_E_GC_PROPERTY, tr("Property")},
        {MV_E_GC_RUNTIME, tr("Running environment error")},
        {MV_E_GC_LOGICAL, tr("Logical error")},
        {MV_E_GC_ACCESS, tr("Node accessing condition error")},
        {MV_E_GC_TIMEOUT, tr("Timeout")},
        {MV_E_GC_DYNAMICCAST, tr("Transformation exception")},
        {MV_E_GC_UNKNOW, tr("GenICam unknown error")},

        // GigE_STATUS对应的错误码:范围0x80000200-0x800002FF
        {MV_E_NOT_IMPLEMENTED, tr("The command is not supported by device")},
        {MV_E_INVALID_ADDRESS, tr("The target address being accessed does not exist")},
        {MV_E_WRITE_PROTECT, tr("The target address is not writable")},
        {MV_E_ACCESS_DENIED, tr("No permission")},
        {MV_E_BUSY, tr("Device is busy, or network disconnected")},
        {MV_E_PACKET, tr("Network data packet error")},
        {MV_E_NETER, tr("Network error")},
        {MV_E_IP_CONFLICT, tr("Device IP conflict")},

        // USB_STATUS对应的错误码:范围0x80000300-0x800003FF
        {MV_E_USB_READ, tr("Reading USB error")},
        {MV_E_USB_WRITE, tr("Writing USB error")},
        {MV_E_USB_DEVICE, tr("Device exception")},
        {MV_E_USB_GENICAM, tr("GenICam error")},
        {MV_E_USB_BANDWIDTH, tr("Insufficient bandwidth")},
        {MV_E_USB_DRIVER, tr("Driver mismatch or unmounted drive")},
        {MV_E_USB_UNKNOW, tr("USB unknown error")},

        // 升级时对应的错误码:范围0x80000400-0x800004FF
        {MV_E_UPG_FILE_MISMATCH, tr("Firmware mismatches")},
        {MV_E_UPG_LANGUSGE_MISMATCH, tr("Firmware language mismatches")},
        {MV_E_UPG_CONFLICT,
         tr("Upgrading conflicted (repeated upgrading requests during device upgrade)")},
        {MV_E_UPG_INNER_ERR, tr("Camera internal error during upgrade")},
        {MV_E_UPG_UNKNOW, tr("Unknown error during upgrade")},
    };

    errorMsg += errorDescs.value(nErrorNum, tr("Unknow(%1)").arg(nErrorNum));

    return errorMsg;
}

} // namespace SpeedCamera
