/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       DalsaCamera.cpp
 * @brief      Dalsa 线扫相机功能封装
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "DalsaCamera.h"

#include <QDebug>
#include <QThread>
#include <QDateTime>

#include "DalsaCameraInstance.h"


// 相机数据回调
static void XferCallback(SapXferCallbackInfo *pInfo)
{
    // qDebug() << "收到相机回调！";
    if (pInfo->IsTrash()) {
        qDebug() << "[DalsaCamera] 收到废弃帧";
        return;
    }

    auto *camera = (SpeedCamera::DalsaCamera *) pInfo->GetContext();

    BYTE *pData;
    camera->Buffers->GetAddress((void**) &pData);

    const auto width = camera->Buffers->GetWidth();
    const auto height = camera->Buffers->GetHeight();

    QImage image(pData, width, height, QImage::Format_Grayscale8);
    image = image.copy();

    camera->Buffers->ReleaseAddress((void *) pData);
    camera->Buffers->Clear(camera->Buffers->GetIndex());

    camera->setImage(image);
}


namespace SpeedCamera {

DalsaCameraInstance *DalsaCamera::instance = new DalsaCameraInstance();

DalsaCamera::DalsaCamera(QObject *parent) : Camera(parent)
{

}

// 枚举相机
QStringList DalsaCamera::enumerateDevicesSerial()
{
    QStringList serials;
    auto serverCount = SapManager::GetServerCount();
    char serverName[CORSERVER_MAX_STRLEN];
    for (int serverIndex = 0; serverIndex < serverCount; serverIndex++)
    {
        if (SapManager::GetResourceCount(serverIndex, SapManager::ResourceAcqDevice) != 0)
        {
            SapManager::GetServerName(serverIndex, serverName, sizeof(serverName));
            serials.append(QString(serverName));
        }
    }
    return serials;
}

// 根据序列号加载设备
bool DalsaCamera::attachBySerial(const QString &serial)
{
    detach();

    // TODO: 加载自定义配置
    AcqDevice = new SapAcqDevice(SapLocation(serial.toStdString().c_str(), 0),
                                 "D:\\CamFiles\\User\\Default.ccf");
    BOOL Status = AcqDevice->Create();
    if (Status) {
        Buffers = new SapBufferWithTrash(8, AcqDevice);
        Xfer = new SapAcqDeviceToBuf(AcqDevice, Buffers, XferCallback, this);

        // Create buffer object
        if (!Buffers || !Buffers->Create()) {
            setError(tr("Create buffer object failed"));
            detach();
            return false;
        }

        // Create transfer object
        if (!Xfer || !Xfer->Create()) {
            setError(tr("Create transfer object failed"));
            detach();
            return false;
        }

        AcqDevice->GetFeatureValue("Width", &Img_Width);
        AcqDevice->GetFeatureValue("Height", &Img_Height);
        //AcqDevice->SetFeatureValue("ImageTimeout", 60);

        _serial = serial;
        // qDebug() << "Width:" << Img_Width << ", Height:" << Img_Height << endl;
        return true;
    }

    setError(tr("Camera %1 not found").arg(serial));
    return false;
}

bool DalsaCamera::detach()
{
    // Destroy transfer object
    if ((Xfer && *Xfer && Xfer->Destroy())) {
        Xfer = nullptr;
    }

    // Destroy buffer object
    if (Buffers && Buffers->Destroy()) {
        Buffers = nullptr;
    }

    // Destroy acquisition object
    if (AcqDevice && !AcqDevice->Destroy()) {
        AcqDevice = nullptr;
    }

    _serial = QString();
    return true;
}

QImage DalsaCamera::grab()
{
    startGrabbing();
    return QImage();

    if (!checkXfer()) {
        return QImage();
    }

    Xfer->Grab();
    return QImage();
}

QString DalsaCamera::serialNumber()
{
    return _serial;
}

bool DalsaCamera::setIOEnable(const bool &isEnable)
{
    Q_UNUSED(isEnable);
    return false;
}

bool DalsaCamera::setPacketSize(const int &packetSize)
{
    Q_UNUSED(packetSize);
    return false;
}

bool DalsaCamera::setExposureTime(const qreal &expTime)
{
    Q_UNUSED(expTime);
    return false;
}

bool DalsaCamera::checkXfer()
{
    if (Xfer == nullptr) {
        setError(tr("Xfer is null!"));
        return false;
    }
    return true;
}

// 开始触发
bool DalsaCamera::startGrabbing()
{
    if (!checkXfer()) return false;

    Xfer->Grab();
    return true;
}

// 停止触发
bool DalsaCamera::stopGrabbing()
{
    if (!checkXfer()) return false;

    // Stop grab
    Xfer->Freeze();
    //if (!Xfer->Wait(5000)) { };
    return true;
}

}   // namespace DzCamera
