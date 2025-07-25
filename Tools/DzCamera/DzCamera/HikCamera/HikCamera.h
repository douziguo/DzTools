#ifndef HIKCAMERA_H
#define HIKCAMERA_H

#include "../Public/DzCamera.h"

namespace DzCamera {

class HikInstance;

class HikCamera : public Camera
{
    Q_OBJECT
private:
    HikInstance *hik = nullptr;
    void *handle = nullptr;

    QString _serial;
    bool _isGrabbing = false;

private:
    bool checkHandle();
    bool isAttached() const;

    bool isGrabbing() const;
    bool startGrabbing();
    bool stopGrabbing();

public:
    HikCamera(QObject *parent = nullptr);
    ~HikCamera();

    QStringList enumerateDevicesSerial() override;

    bool attachBySerial(const QString &serial) override;
    bool detach() override;

    QImage grab() override;

    QString serialNumber() override;

    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &packetSize) override;
    bool setExposureTime(const qreal &expTime) override;
    bool setDigitalShift(const qreal digitalShift) override;
    bool setGain(const qreal gain) override;
    bool setTriggerMode(TriggerMode triggerMode) override;

    void *hikHandle() { return handle; };

    int getCounterCurrentValue();
    bool counterReset();
    void handleDisconnect();
};

} // namespace DzCamera

#endif // HIKCAMERA_H
