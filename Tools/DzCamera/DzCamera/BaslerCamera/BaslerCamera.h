#ifndef BASLERCAMERA_H
#define BASLERCAMERA_H

#include "../Public/DzCamera.h"

#include "BaslerInstance.h"

namespace DzCamera {

class BaslerCamera : public Camera
{
    Q_OBJECT
private:
    // 相较于 BaslerInstance::getInstance() 的形式，这样才能真正确保
    // BaslerInstance 实例晚于 BaslerCamera 被释放
    static BaslerInstance instance;

    Pylon::CInstantCamera camera;
    GenApi::CNodeMapPtr pINodeMap;

    bool checkNodeMap();
public:
    BaslerCamera(QObject *parent = nullptr);

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
    bool isCameraConnected() override;
};

}   // namespace DzCamera

#endif // BASLERCAMERA_H
