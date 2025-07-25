#ifndef MINDVISIONCAMERAINSTANCE_H
#define MINDVISIONCAMERAINSTANCE_H

#include <QObject>
#include <windows.h>
#include "include/CameraApi.h"

// 指定相机枚举的最大个数
#ifndef MV_CAMERA_NUMS
#define MV_CAMERA_NUMS 50
#endif

namespace DzCamera {

class MindVisionCameraInstance : public QObject
{
    Q_OBJECT
private:
    QList<tSdkCameraDevInfo> _cachedDeviceList;   // 缓存的设备列表
public:
    explicit MindVisionCameraInstance(QObject *parent = nullptr);

    static QString formatErrorMsg(int status, const QString &msg = QString());

    bool enumDevices(bool refreshCache, QList<tSdkCameraDevInfo> &deviceList, QString &errMsg);
    tSdkCameraDevInfo findCameraBySerial(bool refreshCache, const QString &serial, QString &errMsg);
};

}   // namespace SpeedCamera

#endif // MINDVISIONCAMERAINSTANCE_H
