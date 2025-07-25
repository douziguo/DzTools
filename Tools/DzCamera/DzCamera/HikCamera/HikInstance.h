#ifndef HIKINSTANCE_H
#define HIKINSTANCE_H

#include "MvCameraControl.h"

#include <QString>
#include <QImage>

namespace SpeedCamera {

class HikInstance : public QObject
{
    Q_OBJECT
private:
    MV_CC_DEVICE_INFO_LIST _cachedDeviceList; // 缓存的设备列表
private:
    HikInstance(QObject *parent = nullptr);
    ~HikInstance();

public:
    static HikInstance *getInstance()
    {
        static HikInstance instance;
        return &instance;
    }

    bool enumDevices(bool refreshCache, MV_CC_DEVICE_INFO_LIST &deviceList, QString &errMsg);
    MV_CC_DEVICE_INFO *findCameraBySerial(bool refreshCache, const QString &serial, QString &errMsg);

    static void dataToImage(
        void *handle, unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, QImage &image);
    static QString formatErrorMsg(int nErrorNum, const QString &msg = QString());
};

} // namespace SpeedCamera

#endif // HIKINSTANCE_H
