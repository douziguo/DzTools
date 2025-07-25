/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       DahengCamera.cpp
 * @brief      大恒相机功能封装
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2023/02/08
 *
 * @history
 * - 2023/02/08 模块创建
 *****************************************************************************/

#include "DahengCamera.h"

#include "DahengInstance.h"
#include "GalaxyIncludes.h"

namespace SpeedCamera {

using namespace std;

DahengCamera::DahengCamera(QObject *parent) : Camera(parent)
{
    DahengInstance::getInstance();
}

// 枚举设备序列号
QStringList DahengCamera::enumerateDevicesSerial()
{
    QStringList serials;

    GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;
    IGXFactory::GetInstance().UpdateAllDeviceList(1000, vectorDeviceInfo);
    for (size_t i = 0; i < vectorDeviceInfo.size(); i++)
    {
        serials.append(QString(vectorDeviceInfo[i].GetSN()));
    }

    return serials;
}

// 根据序列号加载设备
bool DahengCamera::attachBySerial(const QString &serial)
{
    detach();

    static bool isEmum = false;
    if (!isEmum) {
        isEmum = true;  // 大恒的坑：必须枚举一次设备才能通过序列号连上
        enumerateDevicesSerial();
    }

    bool bIsDeviceOpen = false;      ///< 判断设备是否已打开标志
    try
    {
        // 打开设备
        m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(serial.toStdString().c_str(), GX_ACCESS_EXCLUSIVE);
        bIsDeviceOpen = true;

        // 获取属性控制器
        m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

        // 设置采集模式为连续采集
        m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("SingleFrame");

        // 设置触发模式为关
        m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");

        return true;
    }
    catch (CGalaxyException& e)
    {
        // 判断设备是否已打开
        if (bIsDeviceOpen)
        {
            m_objDevicePtr->Close();
        }
        setError(tr("Camera attach failure: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }

    return false;
}

bool DahengCamera::detach()
{
    try
    {
        if (!m_objDevicePtr.IsNull()) {
            m_objDevicePtr->Close();
        }
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Camera detach failure: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }
    return true;
}

QImage DahengCamera::grab()
{
    QImage image;
    try
    {
        // 打开流
        m_objStreamPtr = m_objDevicePtr->OpenStream(0);
        // 开启流通道采集
        m_objStreamPtr->StartGrab();
        // 给设备发送开采命令
        CGXFeatureControlPointer objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();
        objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
        // 采单帧
        CImageDataPointer objImageDataPtr;
        objImageDataPtr = m_objStreamPtr->GetImage(20000);// 超时时间
        if (objImageDataPtr->GetStatus() == GX_FRAME_STATUS_SUCCESS)
        {
            // 图像获取为完整帧，可以读取图像宽、高、数据格式等
            uint64_t nWidth = objImageDataPtr->GetWidth();
            uint64_t nHeight = objImageDataPtr->GetHeight();
            GX_PIXEL_FORMAT_ENTRY emPixelFormat = objImageDataPtr->GetPixelFormat();

            if (emPixelFormat == GX_PIXEL_FORMAT_MONO8) {
                image = QImage((uchar*) objImageDataPtr->GetBuffer(), nWidth, nHeight, QImage::Format_Grayscale8);
                image = image.copy();
            } else if (emPixelFormat == GX_PIXEL_FORMAT_BAYER_RG8) {
                GX_VALID_BIT_LIST emValidBits = GX_BIT_0_7;
                BYTE* pBuffer = NULL;
                pBuffer = (BYTE*)objImageDataPtr->ConvertToRGB24(emValidBits, GX_RAW2RGB_NEIGHBOUR, true);
                image = QImage((uchar*) pBuffer, nWidth, nHeight, QImage::Format_BGR888);
                image = image.copy();
            } else {
                setError(tr("Unsupported image format: %1").arg(emPixelFormat));
            }
        }
        // 停采
        objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
        m_objStreamPtr->StopGrab();
        // 关闭流通道
        m_objStreamPtr->Close();
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Image grab error: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }

    return image;
}

QString DahengCamera::serialNumber()
{
    try
    {
        return QString(m_objDevicePtr->GetDeviceInfo().GetSN());
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Unable to read camera serial number: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }
    return QString();
}

bool DahengCamera::setIOEnable(const bool &isEnable)
{
    try
    {
        m_objFeatureControlPtr->GetEnumFeature("LineSelector")->SetValue("Line1");
        m_objFeatureControlPtr->GetEnumFeature("LineSource")->SetValue("UserOutput0");
        m_objFeatureControlPtr->GetEnumFeature("UserOutputSelector")->SetValue("UserOutput0");
        m_objFeatureControlPtr->GetBoolFeature("UserOutputValue")->SetValue(isEnable);
        return true;
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Failure to modify I/O status: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }
    return false;
}

bool DahengCamera::setPacketSize(const int &packetSize)
{
    try
    {
        m_objFeatureControlPtr->GetIntFeature("GevSCPSPacketSize")->SetValue(packetSize);
        return true;
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Failure to modify packet size: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }
    return false;
}

// 设置曝光时间
bool DahengCamera::setExposureTime(const qreal &expTime)
{
    try
    {
        if (qFuzzyIsNull(expTime)) {
            // 自动曝光
            m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->SetValue("Continuous");
            return true;
        }
        m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->SetValue("Off");
        m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue(expTime);
        return true;
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Failure to modify exposure time: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }
    return false;
}

bool DahengCamera::setDigitalShift(const qreal digitalShift)
{
    try
    {
        m_objFeatureControlPtr->GetIntFeature("DigitalShift")->SetValue((int) digitalShift);
        return true;
    }
    catch (CGalaxyException& e)
    {
        setError(tr("Failure to modify digital shift: %1, %2")
                 .arg(e.GetErrorCode()).arg(formatErrMsg(e.what())));
    }
    return false;
}

// 格式化错误内容，消除两边的大括号
QString DahengCamera::formatErrMsg(QString msg) const
{
    if (msg.startsWith("{")) {
        msg.remove(0, 1);
    }
    if (msg.endsWith("}")) {
        msg.remove(msg.length() - 1, 1);
    }
    return msg;
}

}   // namespace SpeedCamera
