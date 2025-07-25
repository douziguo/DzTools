#ifndef HUARAYCAMERA_H
#define HUARAYCAMERA_H

#include "../Public/SpeedCamera.h"

class HuarayInstance;

namespace SpeedCamera {

class HuarayCamera : public Camera
{
    Q_OBJECT
private:
    void* _handle = nullptr;
public:
    HuarayCamera();
    ~HuarayCamera();

    QStringList enumerateDevicesSerial() override;

    bool attachBySerial(const QString &serial) override;
    bool detach() override;

    QImage grab() override;

    QString serialNumber() override;

    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &packetSize) override;
    bool setExposureTime(const qreal &expTime) override;
    bool setInterPacketDelay(const int &delay);
    bool setGainRaw(int64_t gainRaw);
    bool setAcquizMode(bool acquizMode = true);
private:
    bool checkHandle();
};

}   // namespace SpeedCamera

#endif // HUARAYCAMERA_H
