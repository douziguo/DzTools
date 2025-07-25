#ifndef VirtualCamera_H
#define VirtualCamera_H

#include "../Public/DzCamera.h"

namespace DzCamera {

class VirtualCamera : public Camera
{
    Q_OBJECT
private:
    QString _deviceSerial;

    bool _IOEnable = false;
    int _packetSize = 500;
    qreal _expTime = 0;
    qreal _digitalShift = 0;
    qreal _gain = 0;
    TriggerMode _triggerMode = SoftwareTriggering;
public:
    VirtualCamera(QObject *parent = nullptr);

    QStringList enumerateDevicesSerial() override;

    bool attachBySerial(const QString &serial) override;
    bool detach() override;

    QImage grab() override;

    QString serialNumber() override;

    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &_packetSize) override;
    bool setExposureTime(const qreal &_expTime) override;
    bool setDigitalShift(const qreal digitalShift) override;
    bool setGain(const qreal gain) override;
    bool setTriggerMode(TriggerMode triggerMode) override;
private:
    bool checkNodeMap();
    QColor getRandColor();
    void delay(int msec);
};

}   // namespace DzCamera

#endif // VirtualCamera_H
