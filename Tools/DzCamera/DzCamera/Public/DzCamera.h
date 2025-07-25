#ifndef DZCAMERA_H
#define DZCAMERA_H

#pragma execution_character_set("utf-8")

#include <QObject>
#include <QImage>
#include <QReadWriteLock>

namespace DzCamera {

class Camera : public QObject
{
    Q_OBJECT
public:
    // 触发模式
    enum TriggerMode {
        SoftwareTriggering, // 软触发
        HardwareTriggering  // 硬触发
    };

private:
    QStringList errMsgs;

    QReadWriteLock _imageLock;
    QImage _image;

protected:
    mutable QReadWriteLock _lock;

protected:
    void setError(const QString &errMsg);

public:
    explicit Camera(QObject *parent = nullptr);
    virtual ~Camera();

    // 错误消息处理
    QStringList errors() const;
    QString lastError() const;
    void clearError();

    // 设置拍摄的照片（主要用于照片回调，因此设置为 public）
    void setImage(const QImage &image);

    // 枚举所有连接的设备
    virtual QStringList enumerateDevicesSerial() = 0;

    // 根据序列号连接设备
    virtual bool attachBySerial(const QString &serial) = 0;
    // 断开与设备的连接
    virtual bool detach() = 0;

    // 采图
    virtual QImage grab() = 0;

    // 获取当前连接设备的序列号
    virtual QString serialNumber();

    // 获取相机采集的图像
    virtual QImage getImage();

    // 控制 I/O 量
    virtual bool setIOEnable(const bool &isEnable);

    // 修改包大小
    virtual bool setPacketSize(const int &packetSize);

    // 设置曝光时间
    virtual bool setExposureTime(const qreal &expTime);

    // 设置数字移位
    virtual bool setDigitalShift(const qreal digitalShift);

    // 设置增益
    virtual bool setGain(const qreal gain);

    // 设置触发模式
    virtual bool setTriggerMode(TriggerMode triggerMode);

    // 相机是否已连接
    virtual bool isCameraConnected();

Q_SIGNALS:
    // 相机断开连接
    void cameraDisconnected();

    // 图片采集回调
    void imageGrabbed(QImage image, QPrivateSignal);
};

} // namespace DzCamera

#endif // DZCAMERA_H
