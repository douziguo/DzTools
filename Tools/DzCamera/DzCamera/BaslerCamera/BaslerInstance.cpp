/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       BaslerInstance.cpp
 * @brief      单例，用于维护全局的 Basler 相关实例
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2021/04/14
 *
 * @history
 * - 2021/04/14 模块创建
 *****************************************************************************/

#include "BaslerInstance.h"
#include <QImage>
#include <QDebug>

namespace SpeedCamera {

using namespace Pylon;
using namespace GenICam;
using namespace GenApi;

BaslerInstance::BaslerInstance()
{
    // SetGenICamLogConfig("GenICamLog/");
    Pylon::PylonInitialize();
}

BaslerInstance::~BaslerInstance()
{
    Pylon::PylonTerminate();
}

// 转换输出结果到图片
void BaslerInstance::resultToImage(CGrabResultPtr pInBuffer, QImage &OutImage)
{
    const uchar *buff = (uchar *) pInBuffer->GetBuffer();
    const int nHeight = pInBuffer->GetHeight();
    const int nWidth = pInBuffer->GetWidth();

    // 黑白图像
    if (pInBuffer->GetPixelType() == PixelType_Mono8) {
        OutImage = QImage(buff, nWidth, nHeight, QImage::Format_Grayscale8);
        uchar *pCursor = OutImage.bits();
        if (OutImage.bytesPerLine() != nWidth) {
            for (int y = 0; y < nHeight; ++y) {
                pCursor = OutImage.scanLine(y);
                for (int x = 0; x < nWidth; ++x) {
                    *pCursor = *buff;
                    ++pCursor;
                    ++buff;
                }
            }
        } else {
            memcpy(OutImage.bits(), buff, nWidth * nHeight);
        }
    }

    // 彩色图像
    else if (
        pInBuffer->GetPixelType() == PixelType_BayerGR8
        || pInBuffer->GetPixelType() == PixelType_BayerRG8
        || pInBuffer->GetPixelType() == PixelType_BayerGB8
        || pInBuffer->GetPixelType() == PixelType_BayerBG8
        || pInBuffer->GetPixelType() == PixelType_YUV422packed) {
        CImageFormatConverter fc;
        fc.OutputPixelFormat = PixelType_BGR8packed;

        CPylonImage image;
        fc.Convert(image, pInBuffer);

        OutImage
            = QImage((uint8_t *) image.GetBuffer(), nWidth, nHeight, nWidth * 3, QImage::Format_BGR888)
                  .copy();
    } else {
        qWarning() << "[BaslerCamera] 不支持的图像格式：" << pInBuffer->GetPixelType();
        OutImage = QImage();
    }
}

} // namespace SpeedCamera
