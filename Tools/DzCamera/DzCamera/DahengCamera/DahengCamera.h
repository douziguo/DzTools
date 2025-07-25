#ifndef DAHENGCAMERA_H
#define DAHENGCAMERA_H

#include "../Public/DzCamera.h"

#include "inc/IGXDevice.h"

namespace DzCamera {

class DahengCamera : public Camera
{
    Q_OBJECT
private:
    CGXDevicePointer m_objDevicePtr;                  ///< 设备句柄
    CGXStreamPointer m_objStreamPtr;                  ///< 设备流对象
    CGXFeatureControlPointer m_objFeatureControlPtr;  ///< 属性控制器
public:
    explicit DahengCamera(QObject *parent = nullptr);

    QStringList enumerateDevicesSerial() override;

    bool attachBySerial(const QString &serial) override;
    bool detach() override;

    QImage grab() override;

    QString serialNumber() override;

    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &packetSize) override;
    bool setExposureTime(const qreal &expTime) override;
    bool setDigitalShift(const qreal digitalShift) override;
private:
    QString formatErrMsg(QString msg) const;
};

}   // namespace DzCamera

#endif // DAHENGCAMERA_H
