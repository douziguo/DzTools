#ifndef IKAPCAMERA_H
#define IKAPCAMERA_H

#include "../Public/DzCamera.h"

#include "IKapInstance.h"
#include <shlwapi.h>

namespace DzCamera {

class IKapCamera : public Camera
{
    Q_OBJECT
private:
    static IKapInstance instance;

    QString _configFile;
    QString _serial;

    ITKDEVICE hCamera = NULL;
    HANDLE hBoard = INVALID_HANDLE_VALUE;

    ITKSTATUS res = ITKSTATUS_OK;
    int ret = IK_RTN_OK;

    // 图像宽度
    int g_nWidth = 0;

    // 图像高度
    int g_nHeight = 0;

private:
    bool configureBoard();

    QImage toQImage(unsigned char *pData);

public:
    explicit IKapCamera(QObject *parent = nullptr);

    QStringList enumerateDevicesSerial() override;
    bool attachBySerial(const QString &serial) override;
    bool detach() override;
    QImage grab() override;
    QString serialNumber() override;
    bool setIOEnable(const bool &isEnable) override;
    bool setPacketSize(const int &packetSize) override;
    bool setExposureTime(const qreal &expTime) override;

    bool startGrabbing();
    bool stopGrabbing();
    void onFrameReady();

    QString configFile() const;
    void setConfigFile(const QString &configFile);
};

} // namespace SpeedCamera

#endif // IKAPCAMERA_H
