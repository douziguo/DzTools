/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       SpeedCamera.cpp
 * @brief      相机封装的基类
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2021/04/13
 *
 * @history
 * - 2021/04/13 模块创建
 *****************************************************************************/

#include "SpeedCamera.h"

#include <QDebug>

namespace SpeedCamera {

Camera::Camera(QObject *parent)
    : QObject(parent)
{}

Camera::~Camera() {}

// 记录一个新的错误信息
void Camera::setError(const QString &errMsg)
{
    qDebug().noquote() << "[SpeedCamera] Error: " << errMsg;
    errMsgs.append(errMsg);

    // 只缓存最近的 20 条错误消息
    while (errMsgs.size() > 20) {
        errMsgs.takeFirst();
    }
}

// 获取所有错误消息
QStringList Camera::errors() const
{
    return errMsgs;
}

// 获取最后的错误消息
QString Camera::lastError() const
{
    if (errMsgs.isEmpty())
        return QString();
    return errMsgs.last();
}

// 清空错误消息
void Camera::clearError()
{
    errMsgs.clear();
}

// 设置拍摄的照片
void Camera::setImage(const QImage &image)
{
    _imageLock.lockForWrite();
    _image = image;
    _imageLock.unlock();

    emit imageGrabbed(_image, QPrivateSignal());
}

// 获取当前连接设备的序列号
QString Camera::serialNumber()
{
    return QString();
}

// 获取相机采集的图像
QImage Camera::getImage()
{
    QReadLocker locker(&_imageLock);
    return _image;
}

// 控制 I/O 量
bool Camera::setIOEnable(const bool &isEnable)
{
    Q_UNUSED(isEnable);
    setError(tr("Unsupported methods: %1").arg(tr("setIOEnable")));
    return false;
}

// 修改包大小
bool Camera::setPacketSize(const int &packetSize)
{
    Q_UNUSED(packetSize);
    setError(tr("Unsupported methods: %1").arg(tr("setPacketSize")));
    return false;
}

// 设置曝光时间
bool Camera::setExposureTime(const qreal &expTime)
{
    Q_UNUSED(expTime);
    setError(tr("Unsupported methods: %1").arg(tr("setExposureTime")));
    return false;
}

// 设置数字移位
bool Camera::setDigitalShift(const qreal digitalShift)
{
    Q_UNUSED(digitalShift);
    setError(tr("Unsupported methods: %1").arg(tr("setDigitalShift")));
    return false;
}

// 设置增益
bool Camera::setGain(const qreal gain)
{
    Q_UNUSED(gain);
    setError(tr("Unsupported methods: %1").arg(tr("setGain")));
    return false;
}

// 设置触发模式
bool Camera::setTriggerMode(Camera::TriggerMode triggerMode)
{
    Q_UNUSED(triggerMode);
    setError(tr("Unsupported methods: %1").arg(tr("setTriggerMode")));
    return false;
}

// 相机是否已连接
bool Camera::isCameraConnected()
{
    return false;
}

} // namespace SpeedCamera
