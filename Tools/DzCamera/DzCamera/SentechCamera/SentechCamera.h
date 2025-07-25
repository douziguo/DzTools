#ifndef SENTECHCAMERA_H
#define SENTECHCAMERA_H

#include "../Public/DzCamera.h"

#include <StApi_TL.h>   // Transport Layer function (MUST)
//#include <StApi_IP.h>   // Image Processing function (Optional)
//#include <StApi_GUI.h>  // GUI fucntion (Optional)


namespace DzCamera {

class SentechCamera : public Camera
{
    Q_OBJECT
private:
    StApi::CIStDevicePtr pIStDevice;
    StApi::CIStDataStreamPtr pIStDataStream;

    GenApi::CNodeMapPtr pINodeMap;

public:
    SentechCamera(QObject *parent = nullptr);

    QStringList enumerateDevicesSerial() override;

    bool attachBySerial(const QString &serial) override;
    bool detach() override;

    QImage grab() override;

    bool checkNodeMap();

    QString serialNumber() override;

    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &packetSize) override;
    bool setExposureTime(const qreal &expTime) override;
};

}   // namespace SpeedCamera

#endif // SENTECHCAMERA_H
