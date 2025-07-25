#ifndef BASLEREVENTER_H
#define BASLEREVENTER_H

#pragma execution_character_set("utf-8")

#include <QString>
#include <QDebug>

#include <pylon/InstantCamera.h>
#include <pylon/ConfigurationEventHandler.h>

namespace Pylon {
class CInstantCamera;

// Basler相机事件处理器
class BaslerConfigEventPrinter : public CConfigurationEventHandler
{
public:
    void OnAttach(CInstantCamera & /*camera*/)
    {
        // qInfo() << "OnAttach event";
    }

    void OnAttached(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnAttached event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnOpen(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnOpen event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnOpened(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnOpened event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnGrabStart(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnGrabStart event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnGrabStarted(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnGrabStarted event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnGrabStop(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnGrabStop event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnGrabStopped(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnGrabStopped event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnClose(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnClose event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnClosed(CInstantCamera &camera)
    {
        qInfo() << "OnClosed event for device " << camera.GetDeviceInfo().GetSerialNumber()
                << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnDestroy(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnDestroy event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnDestroyed(CInstantCamera & /*camera*/)
    {
        // qInfo() << "OnDestroyed event";
    }

    void OnDetach(CInstantCamera &camera)
    {
        Q_UNUSED(camera);
        // qInfo() << "OnDetach event for device " << camera.GetDeviceInfo().GetSerialNumber() << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnDetached(CInstantCamera &camera)
    {
        qInfo() << "OnDetached event for device " << camera.GetDeviceInfo().GetSerialNumber()
                << camera.GetDeviceInfo().GetUserDefinedName();
    }

    void OnGrabError(CInstantCamera &camera, const char *errorMessage)
    {
        qDebug() << "OnGrabError event for device " << camera.GetDeviceInfo().GetSerialNumber()
                 << camera.GetDeviceInfo().GetUserDefinedName();
        qDebug() << "Error Message: " << errorMessage;
    }

    // 相机掉线
    void OnCameraDeviceRemoved(CInstantCamera &camera)
    {
        qDebug() << "巴斯勒相机掉线 " << camera.GetDeviceInfo().GetSerialNumber()
                 << camera.GetDeviceInfo().GetUserDefinedName();
    }
};

} // namespace Pylon

#endif // BASLEREVENTER_H
