#ifndef MINDVISIONCAMERA_H
#define MINDVISIONCAMERA_H

#include <windows.h>
#include "../Public/SpeedCamera.h"

namespace SpeedCamera {

class MindVisionCameraInstance;

class MindVisionCamera : public Camera
{
    Q_OBJECT
private:
    static MindVisionCameraInstance *instance;

    QString _sn;

    int hCamera = 0;
    BYTE* pFrameBuffer = nullptr;
public:
    explicit MindVisionCamera(QObject *parent = nullptr);

    QStringList enumerateDevicesSerial() override;
    bool attachBySerial(const QString &serial) override;
    bool detach() override;
    QImage grab() override;
    QString serialNumber() override;
    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &packetSize) override;
    bool setExposureTime(const qreal &expTime) override;
};

}   // namespace SpeedCamera

#endif // MINDVISIONCAMERA_H
