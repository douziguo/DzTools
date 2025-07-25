/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       HuarayCamera.cpp
 * @brief      Huaray 相机功能封装
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2024/05/16
 *
 * @history
 * - 2024/05/16 模块创建
 *****************************************************************************/

#include "HuarayCamera.h"

#include <QDebug>

#include <IMVApi.h>
#include <IMVDefines.h>

#include "HuarayInstance.h"

// 相机操作：如果遇到错误则返回
#define HR_ERR_RETURN(CODE, MSG, RET) \
    do { \
    if (IMV_OK != CODE) { \
    setError(HuarayInstance::formatErrorMsg(CODE, MSG)); \
    return RET; \
    } \
    } while(0)


namespace SpeedCamera {

HuarayCamera::HuarayCamera() : Camera()
{

}

HuarayCamera::~HuarayCamera()
{
    detach();
}

// 检查相机 handle 是否为空
// 注：这个函数请在加锁后使用
bool HuarayCamera::checkHandle()
{
    if (_handle == nullptr) {
        setError(tr("Huaray Handle Is Null!"));
        return false;
    }
    return true;
}

// 枚举出所有相机
QStringList HuarayCamera::enumerateDevicesSerial()
{
    QStringList serials;
    int ret = IMV_OK;
    IMV_DeviceList dList;
    ret = IMV_EnumDevices(&dList, interfaceTypeAll);
    HR_ERR_RETURN(ret, tr("EnumDevices fail"), QStringList());

    for (unsigned int camIdx = 0; camIdx < dList.nDevNum; camIdx++) {
        IMV_DeviceInfo* pDevice = &dList.pDevInfo[camIdx];
        serials << QString(pDevice->cameraKey);
    }

    serials.removeDuplicates();
    return serials;
}

// 通过序列号加载相机
bool HuarayCamera::attachBySerial(const QString& serial)
{
    detach();

    static bool isEmum = false;
    if (!isEmum) {
        isEmum = true;  // 必须枚举一次设备才能通过序列号连上
        enumerateDevicesSerial();
    }

    QWriteLocker locker(&_lock);

    int ret = IMV_OK;

    QByteArray cameraKeyArray = serial.toLocal8Bit();
    char* cameraKey = cameraKeyArray.data();
    ret = IMV_CreateHandle(&_handle, modeByCameraKey, (void*) cameraKey);
    HR_ERR_RETURN(ret, tr("CreateHandle fail"), false);

    ret = IMV_Open(_handle);
    HR_ERR_RETURN(ret, tr("Open device fail"), false);

    // 修改相机触发模式
    ret = IMV_SetEnumFeatureSymbol(_handle, "TriggerMode", "Off");
    HR_ERR_RETURN(ret, tr("Set TriggerMode fail"), false);

    ret = IMV_SetEnumFeatureValue(_handle, "AcquisitionMode", 1);
    HR_ERR_RETURN(ret, tr("Set AcquisitionMode fail"), false);

    ret = IMV_SetEnumFeatureValue(_handle, "AcquisitionStatusSelector", 1);
    HR_ERR_RETURN(ret, tr("Set AcquisitionStatusSelector fail"), false);

    return ret == IMV_OK;
}

// 断开设备的连接
bool HuarayCamera::detach()
{
    QWriteLocker locker(&_lock);

    if (_handle == nullptr) return true;
    if (IMV_IsGrabbing(_handle)) IMV_StopGrabbing(_handle);
    if (IMV_IsOpen(_handle)) IMV_Close(_handle);

    auto ret = IMV_DestroyHandle(_handle);
    if (ret != IMV_OK) {
        qWarning() << "释放华睿相机内存失败" << ret;
    }
    _handle = nullptr;
    return ret == IMV_OK;
}

// 截取一张图像
QImage HuarayCamera::grab()
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return QImage();

    IMV_StopGrabbing(_handle);
    auto ret = IMV_StartGrabbing(_handle);
    HR_ERR_RETURN(ret, tr("StartGrabbing fail"), QImage());

    ret = IMV_ExecuteCommandFeature(_handle, "AcquisitionStart");
    if (ret != IMV_OK) {
        IMV_StopGrabbing(_handle);
        HR_ERR_RETURN(ret, tr("AcquisitionStart fail"), QImage());
    }

    IMV_Frame frame;
    ret = IMV_GetFrame(_handle, &frame, 10000);
    if (ret != IMV_OK) {
        IMV_StopGrabbing(_handle);
        HR_ERR_RETURN(ret, tr("GetFrame fail"), QImage());
    }

    QImage image;
    HuarayInstance::frameToImage(_handle, frame, image);

    ret = IMV_ReleaseFrame(_handle, &frame);
    if (ret != IMV_OK) {
        qWarning() << "华睿相机释放图像数据失败" << ret;
    }

    IMV_StopGrabbing(_handle);
    return image;
}

// 获取当前连接设备的序列号
QString HuarayCamera::serialNumber()
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return QString();

    IMV_DeviceInfo info;
    auto ret = IMV_GetDeviceInfo(_handle, &info);
    HR_ERR_RETURN(ret, tr("GetDeviceInfo fail"), QString());

    return QString(info.cameraKey);
}

/****************************************************/

// 控制 I/O 量
bool HuarayCamera::setIOEnable(const bool& isEnable)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return false;

    int ret = IMV_SetBoolFeatureValue(_handle, "AcquisitionFrameRateEnabled", isEnable);
    HR_ERR_RETURN(ret, tr("Set AcquisitionFrameRateEnabled fail"), false);
    return true;
}

// 修改包大小
bool HuarayCamera::setPacketSize(const int& packetSize)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return false;

    int ret = IMV_SetIntFeatureValue(_handle, "GevSCPSPacketSize", packetSize);
    HR_ERR_RETURN(ret, tr("Set GevSCPSPacketSize fail"), false);
    return true;
}

// 设置曝光时间
bool HuarayCamera::setExposureTime(const qreal& expTime)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return false;

    int ret = IMV_SetDoubleFeatureValue(_handle, "ExposureTime", expTime);
    HR_ERR_RETURN(ret, tr("Set ExposureTime fail"), false);
    return true;
}

// 设置包间延迟
bool HuarayCamera::setInterPacketDelay(const int& delay)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return false;

    int ret = IMV_OK;

    quint64 sw = 0;
    ret = IMV_GetEnumFeatureValue(_handle, "GevSCPDSwitch", &sw);
    HR_ERR_RETURN(ret, tr("Get GevSCPDSwitch fail"), false);

    if (sw != 0) {
        // 使用SCPD，需要将该开关关闭
        ret = IMV_SetEnumFeatureValue(_handle, "GevSCPDSwitch", 0);
        HR_ERR_RETURN(ret, tr("Set GevSCPDSwitch fail"), false);
    }

    // 设置包间隔时间,单位8ns
    ret = IMV_SetIntFeatureValue(_handle, "GevSCPD", delay);
    HR_ERR_RETURN(ret, tr("Set GevSCPD fail"), false);

    return true;
}

// 设置增益
bool HuarayCamera::setGainRaw(int64_t gainRaw)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return false;

    int ret = IMV_SetIntFeatureValue(_handle, "GainRaw", gainRaw);
    HR_ERR_RETURN(ret, tr("Set GainRaw fail"), false);
    return true;
}

// 设置采集模式
bool HuarayCamera::setAcquizMode(bool acquizMode)
{
    QWriteLocker locker(&_lock);
    if (!checkHandle()) return false;

    if (IMV_IsGrabbing(_handle)) {
        IMV_StopGrabbing(_handle);
    }
    int ret = IMV_SetEnumFeatureValue(_handle, "AcquisitionMode", acquizMode ? 1 : 0);
    HR_ERR_RETURN(ret, tr("Set AcquisitionMode fail"), false);
    return true;
}

}    // namespace SpeedCamera
