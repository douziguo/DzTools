#ifndef DALSACAMERA_H
#define DALSACAMERA_H

#pragma execution_character_set("utf-8")

#include "../Public/DzCamera.h"
#include "SapClassBasic.h"

static void XferCallback(SapXferCallbackInfo *pInfo);

namespace SpeedCamera {

class DalsaCameraInstance;

class DalsaCamera : public Camera
{
    Q_OBJECT
private:
    static DalsaCameraInstance *instance;
    QString _serial;

public:
    SapAcqDevice *AcqDevice = nullptr;
    SapBufferWithTrash *Buffers = nullptr;
    SapAcqDeviceToBuf *Xfer = nullptr;

    int Img_Width = 0;
    int Img_Height = 0;
public:
    explicit DalsaCamera(QObject *parent = nullptr);

    QStringList enumerateDevicesSerial() override;
    bool attachBySerial(const QString &serial) override;
    bool detach() override;
    QImage grab() override;

    virtual QString serialNumber() override;
    virtual bool setIOEnable(const bool &isEnable) override;
    virtual bool setPacketSize(const int &packetSize) override;
    virtual bool setExposureTime(const qreal &expTime) override;

    bool checkXfer();
    bool startGrabbing();
    bool stopGrabbing();
};

}   // namespace SpeedCamera

#endif // DALSACAMERA_H
