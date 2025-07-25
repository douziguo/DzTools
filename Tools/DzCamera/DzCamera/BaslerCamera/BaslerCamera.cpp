/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       BaslerCamera.cpp
 * @brief      巴斯勒相机功能封装
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2021/04/14
 *
 * @history
 * - 2021/04/14 模块创建
 *****************************************************************************/

#include "BaslerCamera.h"

#include <QDebug>

#include "BaslerEventer.h"

using namespace Pylon;
using namespace GenICam;
using namespace GenApi;

namespace SpeedCamera {

BaslerInstance BaslerCamera::instance;

BaslerCamera::BaslerCamera(QObject *parent)
    : Camera(parent)
{}

// 枚举所有的可用设备
QStringList BaslerCamera::enumerateDevicesSerial()
{
    QStringList serials;

    try {
        DeviceInfoList_t dList;
        CTlFactory::GetInstance().EnumerateDevices(dList, true);

        for (size_t i = 0; i < dList.size(); i++) {
            serials << QString(dList[i].GetSerialNumber());
        }
    } catch (const GenericException &e) {
        setError(tr("Error getting camera list: %1").arg(e.GetDescription()));
    }

    serials.removeDuplicates();
    return serials;
}

// 根据序列号加载设备
bool BaslerCamera::attachBySerial(const QString &serial)
{
    detach();

    try {
        CDeviceInfo device;
        auto serialString = serial.toStdString();
        device.SetSerialNumber(serialString.c_str());
        camera.Attach(CTlFactory::GetInstance().CreateDevice(device));

        /// 相机移除日志，断开超时5s
        camera.RegisterConfiguration(
            new BaslerConfigEventPrinter, RegistrationMode_Append, Cleanup_Delete);
        CIntegerParameter heartbeat(camera.GetTLNodeMap(), "HeartbeatTimeout");
        // set to 5000 ms timeout if writable
        heartbeat.TrySetValue(30000, IntegerValueCorrection_Nearest);

        camera.Open();
        // camera.MaxNumBuffer = 5;

        pINodeMap = &camera.GetNodeMap();
        return true;
    } catch (const GenericException &e) {
        setError(tr("Camera attach failure: %1").arg(e.GetDescription()));
    }
    return false;
}

// 断开设备的连接
bool BaslerCamera::detach()
{
    try {
        pINodeMap = nullptr;

        camera.Close();
        camera.DetachDevice();
        return true;
    } catch (const GenericException &e) {
        setError(tr("Camera detach failure: %1").arg(e.GetDescription()));
        return false;
    }
}

// 截取一张图像
QImage BaslerCamera::grab()
{
    QWriteLocker locker(&_lock);
    QImage image;
    try {
        camera.StopGrabbing();
        camera.StartGrabbing(1, GrabStrategy_LatestImageOnly);
        CGrabResultPtr ptrGrabResult;
        while (camera.IsGrabbing()) {
            camera.RetrieveResult(20000, ptrGrabResult, TimeoutHandling_ThrowException);
        }

        if (ptrGrabResult->GrabSucceeded()) {
            // 转换为 QImage
            BaslerInstance::resultToImage(ptrGrabResult, image);
        } else {
            setError(tr("Image grab error: #%1-%2")
                         .arg(ptrGrabResult->GetErrorCode())
                         .arg(QString(ptrGrabResult->GetErrorDescription())));
        }
    } catch (const GenericException &e) {
        setError(tr("Image grab error: %1").arg(e.GetDescription()));
    }

    camera.StopGrabbing();
    return image;
}

// 获取当前连接设备的序列号
QString BaslerCamera::serialNumber()
{
    try {
        return QString(camera.GetDeviceInfo().GetSerialNumber());
    } catch (const GenericException &e) {
        setError(tr("Unable to read camera serial number: %1").arg(e.GetDescription()));
        return QString();
    }
}

// 检查 NodeMap 是否就绪
bool BaslerCamera::checkNodeMap()
{
    if (pINodeMap.IsValid()) {
        return true;
    } else {
        setError(tr("NodeMap is invalid!"));
        return false;
    }
}

/****************************************************/

// 控制 I/O 量
bool BaslerCamera::setIOEnable(const bool &isEnable)
{
    QWriteLocker locker(&_lock);
    if (!checkNodeMap())
        return false;
    try {
        CEnumParameter(pINodeMap, "UserOutputSelector").SetValue("UserOutput1");
        CBooleanParameter(pINodeMap, "UserOutputValue").SetValue(isEnable);
        return true;
    } catch (const GenericException &e) {
        setError(tr("Failure to modify I/O status: %1").arg(e.GetDescription()));
        return false;
    }
}

// 修改包大小
bool BaslerCamera::setPacketSize(const int &packetSize)
{
    QWriteLocker locker(&_lock);
    if (!checkNodeMap())
        return false;
    try {
        CIntegerPtr gigePacketSize(pINodeMap->GetNode("GevSCPSPacketSize"));
        if (IsWritable(gigePacketSize)) {
            gigePacketSize->SetValue(packetSize);
        }
        return true;
    } catch (const GenericException &e) {
        setError(tr("Failure to modify packet size: %1").arg(e.GetDescription()));
        return false;
    }
}

// 设置曝光时间
bool BaslerCamera::setExposureTime(const qreal &expTime)
{
    QWriteLocker locker(&_lock);
    if (!checkNodeMap())
        return false;
    try {
        // 如果值为 0 则开启自动曝光
        CEnumerationPtr ExpAuto(pINodeMap->GetNode("ExposureAuto"));
        if (IsWritable(ExpAuto)) {
            if (qFuzzyIsNull(expTime)) {
                ExpAuto->FromString("Continuous"); // Once-调整一次，Continuous-次次调整，Off-关闭
                return true;
            } else {
                ExpAuto->FromString("Off");
            }
        }

        // 设置曝光时间
        CFloatPtr SetExpTime(pINodeMap->GetNode("ExposureTimeAbs"));
        if (!SetExpTime.IsValid()) {
            SetExpTime = CFloatPtr(pINodeMap->GetNode("ExposureTime"));
            if (!SetExpTime.IsValid()) {
                setError(tr("Failure to get exposure time property"));
                return false;
            }
        }
        const qreal min = SetExpTime->GetMin();
        const qreal max = SetExpTime->GetMax();
        if (expTime < min) {
            SetExpTime->SetValue(min);
        } else if (expTime > max) {
            SetExpTime->SetValue(max);
        } else {
            SetExpTime->SetValue(expTime);
        }
        return true;
    } catch (const GenericException &e) {
        setError(tr("Failure to modify exposure time: %1").arg(e.GetDescription()));
        return false;
    }
}

// 设置数字移位  https://zh.docs.baslerweb.com/digital-shift
bool BaslerCamera::setDigitalShift(const qreal digitalShift)
{
    QWriteLocker locker(&_lock);
    if (!checkNodeMap())
        return false;
    try {
        CIntegerParameter(pINodeMap, "DigitalShift").SetValue((int) digitalShift);
        return true;
    } catch (const GenericException &e) {
        setError(tr("Failure to modify digital shift: %1").arg(e.GetDescription()));
        return false;
    }
}

// 设置增益
bool BaslerCamera::setGain(const qreal gain)
{
    if (!checkNodeMap())
        return false;
    try {
        // 关闭自动增益
        auto gainAuto = CEnumerationPtr(pINodeMap->GetNode("GainAuto"));
        if (gainAuto->ToString() != "Off") {
            CEnumerationPtr(pINodeMap->GetNode("GainAuto"))->FromString("Off");
        }

        auto param = CIntegerPtr(pINodeMap->GetNode("GainRaw")); //->SetValue(400);

        const auto min = param->GetMin();
        const auto max = param->GetMax();
        auto val = qMin(max, qMax(min, (qint64) gain));

        param->SetValue(val);
    } catch (const GenericException &e) {
        setError(QString(tr("Failure to modify gain(raw): %1")).arg(e.GetDescription()));
        return false;
    }

    return true;
}

class BaslerCameraImageEventHandler : public CImageEventHandler
{
private:
    BaslerCamera *_parent = nullptr;

public:
    ~BaslerCameraImageEventHandler()
    {
        //qDebug() << "~BaslerCameraImageEventHandler()";
    }

    // 图像抓取回调
    virtual void OnImageGrabbed(CInstantCamera &camera, const CGrabResultPtr &ptrGrabResult)
    {
        Q_UNUSED(camera);

        if (_parent != nullptr) {
            QImage image;
            BaslerInstance::resultToImage(ptrGrabResult, image);
            _parent->setImage(image);
        }
    }

    void setParent(BaslerCamera *parent) { _parent = parent; }
};

// 设置触发模式
bool BaslerCamera::setTriggerMode(TriggerMode triggerMode)
{
    switch (triggerMode) {
    case SoftwareTriggering:
        // TODO
        break;
    case HardwareTriggering:
        // 注：设置了 Cleanup_Delete，会自动释放 EventHandler
        auto *eventHandler = new BaslerCameraImageEventHandler;
        eventHandler->setParent(this);
        camera.RegisterImageEventHandler(eventHandler, RegistrationMode_ReplaceAll, Cleanup_Delete);
        return true;
    }

    return Camera::setTriggerMode(triggerMode);
}

// 相机是否已连接
bool BaslerCamera::isCameraConnected()
{
    return camera.IsCameraDeviceRemoved() && camera.IsOpen();
}

} // namespace SpeedCamera
