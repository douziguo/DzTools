/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       VirtualCamera.cpp
 * @brief      虚拟相机
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "VirtualCamera.h"
#include <QUuid>
#include <QPainter>
#include <QRandomGenerator>
#include <QDateTime>

namespace DzCamera {

VirtualCamera::VirtualCamera(QObject *parent) : Camera(parent)
{

}

// 枚举所有的可用设备
QStringList VirtualCamera::enumerateDevicesSerial()
{
    QStringList serials;

    for (int i = 0; i < 10; i++) {
        serials.append(QUuid::createUuid().toString(QUuid::Id128).left(10).toUpper());
    }

    serials.removeDuplicates();
    return serials;
}

// 根据序列号加载设备
bool VirtualCamera::attachBySerial(const QString &serial)
{
    detach();
    delay(200);
    _deviceSerial = serial;
    return true;
}

// 断开设备的连接
bool VirtualCamera::detach()
{
    _deviceSerial = QString();
    return true;
}

// 截取一张图像
QImage VirtualCamera::grab()
{
    if (_deviceSerial.isEmpty()) {
        setError(tr("Camera not attached"));
        return QImage();
    }

    delay(600);

    // 获取要显示的文字
    QStringList strs;
    strs << tr("SpeedBot Virtual Camera");
    strs << tr("---------");
    strs << tr("Time: %1").arg(QDateTime::currentDateTime().toString(tr("yyyy/MM/dd hh:mm:ss.zzz")));
    strs << tr("Serial: %1").arg(_deviceSerial);
    strs << tr("I/O: %1").arg(_IOEnable? tr("On"): tr("Off"));
    strs << tr("Packet Size: %1").arg(_packetSize);
    strs << tr("Exposure Time: %1").arg(qFuzzyIsNull(_expTime)? tr("Auto"): QString::number(_expTime));
    strs << tr("Digital Shift: %1").arg(_digitalShift);
    strs << tr("Gain: %1").arg(_gain);
    strs << tr("Trigger Mode: %1").arg((_triggerMode == HardwareTriggering)? tr("Hardware"): tr("Software"));

    // 获取颜色
    const QColor fillColor = getRandColor();
    double gray = (0.299 * fillColor.red() + 0.587 * fillColor.green() + 0.114 * fillColor.blue()) / 255;
    const QColor textColor = gray > 0.5 ? Qt::black : Qt::white;
    Q_UNUSED(textColor);

    QSize size(500, 400);
    QImage image(size, QImage::Format_ARGB32);
    image.fill(fillColor);

    QPainter painter(&image);

    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    painter.setPen(pen);

    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);

    int x = 20, y = 40;
    for (const auto &str : strs) {
        painter.drawText(x, y, str);
        y += 30;
    }

    return image;
}

// 获取当前连接设备的序列号
QString VirtualCamera::serialNumber()
{
    return _deviceSerial;
}

// 检查 NodeMap 是否就绪
bool VirtualCamera::checkNodeMap()
{
    if (!_deviceSerial.isEmpty()) {
        return true;
    } else {
        setError(tr("NodeMap is invalid!"));
        return false;
    }
}

// 获取随机颜色
QColor VirtualCamera::getRandColor()
{
    QColor color(
                QRandomGenerator::global()->bounded(0, 256),
                QRandomGenerator::global()->bounded(0, 256),
                QRandomGenerator::global()->bounded(0, 256));
    return color;
}

// 阻塞延迟，模拟耗时操作
void VirtualCamera::delay(int msec)
{
    QTime _Timer = QTime::currentTime();
    QTime _NowTimer;
    do {
        _NowTimer = QTime::currentTime();
    } while(_Timer.msecsTo(_NowTimer) <= msec);
}

/****************************************************/

// 控制 I/O 量
bool VirtualCamera::setIOEnable(const bool &isEnable)
{
    if (!checkNodeMap()) return false;
    _IOEnable = isEnable;
    return true;
}

// 修改包大小
bool VirtualCamera::setPacketSize(const int &packetSize)
{
    if (!checkNodeMap()) return false;
    _packetSize = packetSize;
    return true;
}

// 设置曝光时间
bool VirtualCamera::setExposureTime(const qreal &expTime)
{
    if (!checkNodeMap()) return false;
    _expTime = expTime;
    return true;
}

bool VirtualCamera::setDigitalShift(const qreal digitalShift)
{
    if (!checkNodeMap()) return false;
    _digitalShift = digitalShift;
    return true;
}

bool VirtualCamera::setGain(const qreal gain)
{
    if (!checkNodeMap()) return false;
    _gain = gain;
    return true;
}

bool VirtualCamera::setTriggerMode(TriggerMode triggerMode)
{
    if (!checkNodeMap()) return false;
    _triggerMode = triggerMode;
    return true;
}

}   // namespace DzCamera
