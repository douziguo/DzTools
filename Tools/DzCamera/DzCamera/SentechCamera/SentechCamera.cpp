/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       SentechCamera.cpp
 * @brief      欧姆龙相机
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2021/04/13
 *
 * @history
 * - 2021/04/13 模块创建
 *****************************************************************************/

#include "SentechCamera.h"
#include "SentechInstance.h"

#include <QDebug>

namespace SpeedCamera {

using namespace StApi;
using namespace GenICam;
using namespace GenApi;

SentechCamera::SentechCamera(QObject *parent) : Camera(parent)
{

}

// 枚举所有的可用设备
QStringList SentechCamera::enumerateDevicesSerial()
{
    QStringList serials;

    try {
        StApi::IStSystemReleasable *pIStSystem = SENTECH->getIStSystemPtr();
        if (pIStSystem != nullptr) {
            for (size_t i = 0; i < pIStSystem->GetInterfaceCount(); i++) {
                IStInterface *pIStInterface(pIStSystem->GetIStInterface(i));
                pIStInterface->UpdateDeviceList();
                for (size_t j = 0; j < pIStInterface->GetDeviceCount(); j++) {
                    const QString deviceSerial(pIStInterface->GetIStDeviceInfo(j)->GetSerialNumber());
                    serials.append(deviceSerial);
                }
            }
        }
    } catch (const GenericException &e) {
        setError(tr("Error getting camera list: %1").arg(e.GetDescription()));
    }

    serials.removeDuplicates();
    return serials;
}

// 根据序列号连接设备
bool SentechCamera::attachBySerial(const QString &serial)
{
    detach();

    try {
        StApi::IStSystemReleasable *pIStSystem = SENTECH->getIStSystemPtr();
        if (pIStSystem == nullptr) {
            setError(tr("Error initializing IStSystem"));
            return false;
        }

        // 查找扫描到的所有设备，对比序列号
        for (size_t i = 0; i < pIStSystem->GetInterfaceCount(); i++) {
            IStInterface *pIStInterface(pIStSystem->GetIStInterface(i));
            pIStInterface->UpdateDeviceList();
            for (size_t j = 0; j < pIStInterface->GetDeviceCount(); j++) {
                const QString deviceSerial(pIStInterface->GetIStDeviceInfo(j)->GetSerialNumber());
                if (deviceSerial == serial) {
                    pIStDevice = pIStInterface->CreateIStDevice(j);
                    if (pIStDevice.IsValid()) {
                        pINodeMap = pIStDevice->GetRemoteIStPort()->GetINodeMap();

                        // 创建一个DataStream对象来处理图像流数据
                        pIStDataStream.Reset(pIStDevice->CreateIStDataStream(0));
                        return true;
                    }
                }
            }
        }

        setError(tr("Camera [%1] not found").arg(serial));
    } catch (const GenericException &e) {
        setError(tr("Camera attach failure: %1").arg(e.GetDescription()));
    }
    return false;
}

// 断开设备的连接
bool SentechCamera::detach()
{
    try {
        pINodeMap = nullptr;
        pIStDataStream.Reset();
        pIStDevice.Reset();
        return true;
    } catch (const GenericException &e) {
        setError(tr("Camera detach failure: %1").arg(e.GetDescription()));
        return false;
    }
}

// 截取一张图像
QImage SentechCamera::grab()
{
    QImage image;
    try
    {
        if (!pIStDevice.IsValid()) {
            setError(tr("Camera not attached"));
            return image;
        }

        pIStDataStream->StartAcquisition(1);    // 开始主机侧的图像采集
        pIStDevice->AcquisitionStart();         // 开始相机侧的图像采集

        // 循环至采集结束
        while (pIStDataStream->IsGrabbing())
        {
            // 设置 5000ms 接收图像内容
            CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(5000));

            // 检查收到的数据是否包含图像
            if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
            {
                // 获取图像内容
                IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

                // 转换为 QImage
                image = QImage((const unsigned char*)(pIStImage->GetImageBuffer()),
                               pIStImage->GetImageWidth(), pIStImage->GetImageHeight(), QImage::Format_Indexed8).copy();
            }
            else
            {
                setError(tr("Image data does not exist"));
            }
        }
        pIStDevice->AcquisitionStop();          // 停止相机侧的图像采集
        pIStDataStream->StopAcquisition();      // 停止主机侧的图像采集
    }
    catch (const GenericException &e)
    {
        setError(tr("Image grab error: %1").arg(e.GetDescription()));
    }
    return image;
}

// 获取相机序列号
QString SentechCamera::serialNumber()
{
    if (!pIStDevice.IsValid()) return QString();

    try {
        return QString(pIStDevice->GetIStDeviceInfo()->GetSerialNumber());
    } catch (const GenericException &e) {
        setError(tr("Unable to read camera serial number: %1").arg(e.GetDescription()));
        return QString();
    }
}

// 检查 NodeMap 是否就绪
bool SentechCamera::checkNodeMap()
{
    if (pINodeMap.IsValid()) {
        return true;
    } else {
        setError(tr("NodeMap is invalid!"));
        return false;
    }
}

/****************************************************/

// 设置相机 IO 的开关
bool SentechCamera::setIOEnable(const bool &isEnable)
{
    if (!checkNodeMap()) return false;

    try {
        // 选择要控制的 I/O
        CEnumerationPtr pUserOutputSelector(pINodeMap->GetNode("UserOutputSelector"));
        pUserOutputSelector->FromString("UserOutput1");

        // 设置值
        CNodePtr pINode(pINodeMap->GetNode("UserOutputValue"));
        CBooleanPtr pIBoolean(pINode);
        pIBoolean->SetValue(isEnable);

        //CEnumParameter(pNodeMap, "UserOutputSelector").SetValue("UserOutput1");
        //CBooleanParameter(pNodeMap, "UserOutputValue").SetValue(isEnable);
        return true;
    }
    catch (const GenericException &e)
    {
        setError(tr("Failure to modify I/O status: %1").arg(e.GetDescription()));
        return false;
    }
}

// 设置包大小
bool SentechCamera::setPacketSize(const int &packetSize)
{
    if (!checkNodeMap()) return false;

    // 暂未实现
    return true;

    try {
        //Retrieves the node from the central map by Name
        GenApi::CNodePtr pINode(pINodeMap->GetNode("AutoPacketSize"));

        bool isWritable = GenApi::IsWritable(pINode);
        bool isReadable = GenApi::IsReadable(pINode);
        bool isAvailable = GenApi::IsAvailable(pINode);
        qDebug() << isWritable << isReadable << isAvailable;

        //SmartPointer for IBoolean interface pointer
        GenApi::CBooleanPtr pIBoolean(pINode);
        pIBoolean->SetValue(false);

        // 尝试修改包大小
        CIntegerPtr gigePacketSize(pINodeMap->GetNode("GevSCPSPacketSize"));
        if (IsWritable(gigePacketSize)) {
            gigePacketSize->SetValue(packetSize);
        }
        return true;
    }
    catch (const GenericException &e)
    {
        setError(tr("Failure to modify packet size: %1").arg(e.GetDescription()));
        return false;
    }
}

// 设置曝光时间
bool SentechCamera::setExposureTime(const qreal &expTime)
{
    if (!checkNodeMap()) return false;

    try {
        // 开启或关闭自动曝光
        CEnumerationPtr ExpAuto(pINodeMap->GetNode("ExposureAuto"));
        if (IsWritable(ExpAuto))
        {
            if (qFuzzyIsNull(expTime)) {
                ExpAuto->FromString("Continuous");    // Continuous-次次调整，Off-关闭
                return true;
            } else {
                ExpAuto->FromString("Off");
            }
        }

        // 选择
        GenApi::CEnumerationPtr pExposureTimeSelector(pINodeMap->GetNode("ExposureTimeSelector"));
        GenApi::CEnumEntryPtr pCommon = pExposureTimeSelector->GetEntryByName("Common");
        int64_t iCommonValue = pCommon->GetValue();
        pExposureTimeSelector->SetIntValue(iCommonValue);

        // 赋值
        GenApi::CNodePtr pINode(pINodeMap->GetNode("ExposureTime"));
        GenApi::CFloatPtr pIFloat(pINode);
        pIFloat->SetValue(expTime);
        return true;
    }
    catch (const GenericException &e)
    {
        setError(tr("Failure to modify exposure time: %1").arg(e.GetDescription()));
        return false;
    }
}

}   // namespace SpeedCamera
