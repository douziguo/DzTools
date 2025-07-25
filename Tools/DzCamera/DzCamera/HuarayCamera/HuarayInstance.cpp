/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       HuarayInstance.cpp
 * @brief      华睿全局生命周期管理
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2024/05/16
 *
 * @history
 * - 2024/05/16 模块创建
 *****************************************************************************/

#include "HuarayInstance.h"

#include <QDebug>
#include <QImage>

HuarayInstance::HuarayInstance()
{

}

HuarayInstance::~HuarayInstance()
{

}

void HuarayInstance::frameToImage(void* handle, const IMV_Frame& frame, QImage& image)
{
    image = QImage();
    const auto frameInfo = frame.frameInfo;

    // mono8格式可不做转码，直接显示，其他格式需要经过转码才能显示
    // mono8 format can be displayed directly without transcoding. Other formats can be displayed only after transcoding
    if (gvspPixelMono8 == frameInfo.pixelFormat)
    {
        image = QImage(frame.pData, frameInfo.width, frameInfo.height, QImage::Format_Grayscale8).copy();
    }
    else
    {
        // 创建彩色图内存
        unsigned char* pRGBbuffer = NULL;
        int nRgbBufferSize = frameInfo.width * frameInfo.height * 3;
        pRGBbuffer = (unsigned char*) malloc(nRgbBufferSize);
        if (pRGBbuffer == NULL)
        {
            qWarning() << "[Huaray] RGBbuffer malloc failed.";
            return;
        }

        // 转码
        IMV_PixelConvertParam stPixelConvertParam;
        stPixelConvertParam.nWidth = frameInfo.width;
        stPixelConvertParam.nHeight = frameInfo.height;
        stPixelConvertParam.ePixelFormat = frameInfo.pixelFormat;
        stPixelConvertParam.pSrcData = frame.pData;
        stPixelConvertParam.nSrcDataLen = frameInfo.size;
        stPixelConvertParam.nPaddingX = frameInfo.paddingX;
        stPixelConvertParam.nPaddingY = frameInfo.paddingY;
        stPixelConvertParam.eBayerDemosaic = demosaicNearestNeighbor;
        stPixelConvertParam.eDstPixelFormat = gvspPixelRGB8;
        stPixelConvertParam.pDstBuf = pRGBbuffer;
        stPixelConvertParam.nDstBufSize = nRgbBufferSize;

        int ret = IMV_PixelConvert(handle, &stPixelConvertParam);
        if (IMV_OK != ret)
        {
            qWarning() << QString("[Huaray] image convert to RGB failed! ErrorCode 0x%1: ")
                          .arg(QString::number(ret, 16).right(8));
            free(pRGBbuffer);
            return;
        }

        image = QImage(pRGBbuffer, stPixelConvertParam.nWidth, stPixelConvertParam.nHeight, QImage::Format_RGB888).copy();
        free(pRGBbuffer);
    }
}

// 解析错误信息
QString HuarayInstance::formatErrorMsg(int nErrorNum, const QString &msg)
{
    QString errorMsg = msg;

    if (nErrorNum != IMV_OK) {
        if (!msg.isEmpty()) {
            errorMsg += QObject::tr(", ");
        }
        errorMsg += QObject::tr("Error = 0x%1: ")
                .arg(QString::number(nErrorNum, 16).right(8));
    }

    switch (nErrorNum)
    {
    case IMV_ERROR:                 errorMsg += QObject::tr("Generic error"); break;
    case IMV_INVALID_HANDLE:        errorMsg += QObject::tr("Error or invalid handle"); break;
    case IMV_INVALID_PARAM:         errorMsg += QObject::tr("Incorrect parameter"); break;
    case IMV_INVALID_FRAME_HANDLE:  errorMsg += QObject::tr("Error or invalid frame handle"); break;
    case IMV_INVALID_FRAME:         errorMsg += QObject::tr("Invalid frame"); break;
    case IMV_INVALID_RESOURCE:      errorMsg += QObject::tr("Camera/Event/Stream and so on resource invalid"); break;
    case IMV_INVALID_IP:            errorMsg += QObject::tr("Device's and PC's subnet is mismatch"); break;
    case IMV_NO_MEMORY:             errorMsg += QObject::tr("Malloc memery failed"); break;
    case IMV_INSUFFICIENT_MEMORY:   errorMsg += QObject::tr("Insufficient memory"); break;
    case IMV_ERROR_PROPERTY_TYPE:   errorMsg += QObject::tr("Property type error"); break;
    case IMV_INVALID_ACCESS:        errorMsg += QObject::tr("Property not accessible, or not be read/written, or read/written failed"); break;
    case IMV_INVALID_RANGE:         errorMsg += QObject::tr("The property's value is out of range, or is not integer multiple of the step"); break;
    case IMV_NOT_SUPPORT:           errorMsg += QObject::tr("Device not supported function"); break;
    case IMV_RESTORE_STREAM:        errorMsg += QObject::tr("Device restore stream"); break;
    case IMV_RECONNECT_DEVICE:      errorMsg += QObject::tr("Device reconnect"); break;
    case IMV_TIMEOUT:               errorMsg += QObject::tr("Timeout"); break;
    default:                        errorMsg += QObject::tr("Unknow(%1)").arg(nErrorNum); break;
    }

    return errorMsg;
}
