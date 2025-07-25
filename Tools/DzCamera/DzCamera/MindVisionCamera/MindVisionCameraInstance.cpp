/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       MindVisionCameraInstance.cpp
 * @brief      MindVision 相机单例，管理全局的生命周期
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "MindVisionCameraInstance.h"

namespace DzCamera {

MindVisionCameraInstance::MindVisionCameraInstance(QObject *parent) : QObject(parent)
{
    // sdk初始化  0-English, 1-中文
    CameraSdkInit(1);
}


// 枚举设备
bool MindVisionCameraInstance::enumDevices(bool refreshCache, QList<tSdkCameraDevInfo> &deviceList, QString &errMsg)
{
    errMsg = QString();

    // 如果无需刷新，且存在缓存，则返回缓存的设备信息
    if (!refreshCache && (_cachedDeviceList.count() > 0)) {
        deviceList = _cachedDeviceList;
        return true;
    }

    CameraSdkStatus status;

    // 调用CameraEnumerateDevice前，先设置CameraNums = 16，表示最多只读取16个设备。
    // 如果需要枚举更多的设备，请更改CameraList数组的大小和CameraNums的值
    // Before calling CameraEnumerateDevice, set CameraNums = 16 to read only 16 devices at most.
    // If you need to enumerate more devices, change the size of the CameraList array and CameraNums
    tSdkCameraDevInfo CameraList[MV_CAMERA_NUMS];
    int CameraNums = MV_CAMERA_NUMS;

    // 枚举设备，获得设备列表
    // Enumerate devices to get a list of devices
    status = CameraEnumerateDevice(CameraList, &CameraNums);
    if (CAMERA_STATUS_SUCCESS != status) {
        errMsg = formatErrorMsg(status);
        return false;
    }

    deviceList.clear();
    for (int i = 0; i < CameraNums; i++) {
        deviceList.append(CameraList[i]);
    }
    _cachedDeviceList = deviceList;
    return true;
}

// 根据序列号找到对应的相机
tSdkCameraDevInfo MindVisionCameraInstance::findCameraBySerial(bool refreshCache, const QString &serial, QString &errMsg)
{
    errMsg = QString();

    QList<tSdkCameraDevInfo> stDeviceList;
    bool ret = enumDevices(refreshCache, stDeviceList, errMsg);
    if (!ret) {
        return tSdkCameraDevInfo();
    }

    for (const auto &info : qAsConst(stDeviceList))
    {
        if (info.acSn == serial) {
            return info;
        }
    }

    errMsg = QObject::tr("Device not found");
    return tSdkCameraDevInfo();
}




// 解析错误信息
QString MindVisionCameraInstance::formatErrorMsg(int status, const QString &msg)
{
    QString errorMsg = msg;

    if (status != CAMERA_STATUS_SUCCESS) {
        if (!msg.isEmpty()) {
            errorMsg += QObject::tr(", ");
        }
        errorMsg += QObject::tr("Error = 0x%1: ")
                .arg(QString::number(status, 16).right(8));
    }

    switch (status)
    {
    case CAMERA_STATUS_SUCCESS: errorMsg += tr("Successful"); break;
    case CAMERA_STATUS_FAILED: errorMsg += tr("operation failed"); break;
    case CAMERA_STATUS_INTERNAL_ERROR: errorMsg += tr("internal error"); break;
    case CAMERA_STATUS_UNKNOW: errorMsg += tr("unknown error"); break;
    case CAMERA_STATUS_NOT_SUPPORTED: errorMsg += tr("Does not support this feature"); break;
    case CAMERA_STATUS_NOT_INITIALIZED: errorMsg += tr("Incomplete initialization"); break;
    case CAMERA_STATUS_PARAMETER_INVALID: errorMsg += tr("Invalid argument"); break;
    case CAMERA_STATUS_PARAMETER_OUT_OF_BOUND: errorMsg += tr("Out of bounds of parameters"); break;
    case CAMERA_STATUS_UNENABLED: errorMsg += tr("Not enabled"); break;
    case CAMERA_STATUS_USER_CANCEL: errorMsg += tr("The user manually canceled, such as roi panel click cancel, return"); break;
    case CAMERA_STATUS_PATH_NOT_FOUND: errorMsg += tr("The corresponding path was not found in the registry"); break;
    case CAMERA_STATUS_SIZE_DISMATCH: errorMsg += tr("The length of the obtained image data does not match the defined size"); break;
    case CAMERA_STATUS_TIME_OUT: errorMsg += tr("Timeout error"); break;
    case CAMERA_STATUS_IO_ERROR: errorMsg += tr("Hardware IO error"); break;
    case CAMERA_STATUS_COMM_ERROR: errorMsg += tr("Communication error"); break;
    case CAMERA_STATUS_BUS_ERROR: errorMsg += tr("Bus error"); break;
    case CAMERA_STATUS_NO_DEVICE_FOUND: errorMsg += tr("No device found"); break;
    case CAMERA_STATUS_NO_LOGIC_DEVICE_FOUND: errorMsg += tr("Logical device not found"); break;
    case CAMERA_STATUS_DEVICE_IS_OPENED: errorMsg += tr("The device is already open"); break;
    case CAMERA_STATUS_DEVICE_IS_CLOSED: errorMsg += tr("Device is off"); break;
    case CAMERA_STATUS_DEVICE_VEDIO_CLOSED: errorMsg += tr("Without opening the device video, when the video-related function is called, if the camera video is not open, the error is returned back."); break;
    case CAMERA_STATUS_NO_MEMORY: errorMsg += tr("Not enough system memory"); break;
    case CAMERA_STATUS_FILE_CREATE_FAILED: errorMsg += tr("Failed to create file"); break;
    case CAMERA_STATUS_FILE_INVALID: errorMsg += tr("Invalid file format"); break;
    case CAMERA_STATUS_WRITE_PROTECTED: errorMsg += tr("Write protection, not write"); break;
    case CAMERA_STATUS_GRAB_FAILED: errorMsg += tr("Data collection failed"); break;
    case CAMERA_STATUS_LOST_DATA: errorMsg += tr("Loss of data, incomplete"); break;
    case CAMERA_STATUS_EOF_ERROR: errorMsg += tr("No frame terminator received"); break;
    case CAMERA_STATUS_BUSY: errorMsg += tr("Busy (last operation is still in progress), this operation cannot be performed"); break;
    case CAMERA_STATUS_WAIT: errorMsg += tr("Need to wait (condition of operation is not established), can try again"); break;
    case CAMERA_STATUS_IN_PROCESS: errorMsg += tr("Ongoing, has been operated"); break;
    case CAMERA_STATUS_IIC_ERROR: errorMsg += tr("IIC transmission error"); break;
    case CAMERA_STATUS_SPI_ERROR: errorMsg += tr("SPI transmission error"); break;
    case CAMERA_STATUS_USB_CONTROL_ERROR: errorMsg += tr("USB control transmission error"); break;
    case CAMERA_STATUS_USB_BULK_ERROR: errorMsg += tr("USB BULK transmission error"); break;
    case CAMERA_STATUS_SOCKET_INIT_ERROR: errorMsg += tr("Network Transport Suite Initialization Failed"); break;
    case CAMERA_STATUS_GIGE_FILTER_INIT_ERROR: errorMsg += tr("The webcam kernel filter driver failed to initialize. Please check if the driver is installed correctly or reinstall it."); break;
    case CAMERA_STATUS_NET_SEND_ERROR: errorMsg += tr("Network data sending error"); break;
    case CAMERA_STATUS_DEVICE_LOST: errorMsg += tr("Lost connection with webcam, heartbeat timeout"); break;
    case CAMERA_STATUS_DATA_RECV_LESS: errorMsg += tr("Received fewer bytes than requested"); break;
    case CAMERA_STATUS_FUNCTION_LOAD_FAILED: errorMsg += tr("Failed to load program from file"); break;
    case CAMERA_STATUS_CRITICAL_FILE_LOST: errorMsg += tr("The file necessary to run the program is missing."); break;
    case CAMERA_STATUS_SENSOR_ID_DISMATCH: errorMsg += tr("The firmware and program do not match because the wrong firmware was downloaded."); break;
    case CAMERA_STATUS_OUT_OF_RANGE: errorMsg += tr("The parameter is out of valid range."); break;
    case CAMERA_STATUS_REGISTRY_ERROR: errorMsg += tr("Setup registration error. Please reinstall the program, or run the installation directory Setup/Installer.exe"); break;
    case CAMERA_STATUS_ACCESS_DENY: errorMsg += tr("No Access. When the specified camera has been occupied by another program, it will return to this state if you request to access the camera. (A camera cannot be accessed simultaneously by multiple programs)"); break;
    case CAMERA_STATUS_CAMERA_NEED_RESET: errorMsg += tr("It means that the camera needs to be reset before it can be used normally. At this time, please make the camera power off and restart, or restart the operating system, then it can be used normally."); break;
    case CAMERA_STATUS_ISP_MOUDLE_NOT_INITIALIZED: errorMsg += tr("ISP module is not initialized"); break;
    case CAMERA_STATUS_ISP_DATA_CRC_ERROR: errorMsg += tr("Data check error"); break;
    case CAMERA_STATUS_MV_TEST_FAILED: errorMsg += tr("Data test failed"); break;
    case CAMERA_STATUS_INTERNAL_ERR1: errorMsg += tr("Internal error 1"); break;
    case CAMERA_STATUS_U3V_NO_CONTROL_EP	: errorMsg += tr("U3V control endpoint not found"); break;
    case CAMERA_STATUS_U3V_CONTROL_ERROR	: errorMsg += tr("U3V control communication error"); break;
    case CAMERA_STATUS_INVALID_FRIENDLY_NAME: errorMsg += tr("Invalid device name, the name cannot contain the following characters (\\/:*?\"<>|\")"); break;
    case CAMERA_STATUS_FORMAT_ERROR: errorMsg += tr("Format error"); break;
    case CAMERA_STATUS_PCIE_OPEN_ERROR: errorMsg += tr("PCIE device open failed"); break;
    case CAMERA_STATUS_PCIE_COMM_ERROR: errorMsg += tr("PCIE device communication failed"); break;
    case CAMERA_STATUS_PCIE_DDR_ERROR: errorMsg += tr("PCIE DDR error"); break;
    case CAMERA_STATUS_IP_ERROR: errorMsg += tr("IP error"); break;

        // CameraLink Acquisition Device
    case CAMERA_STATUS_CL_GRABBER_NOT_FOUND: errorMsg += tr("The specified frame grabber not found"); break;
    case CAMERA_STATUS_CL_GRABBER_NOT_ACCESSIBLE: errorMsg += tr("The specified frame grabber is busy"); break;
    case CAMERA_STATUS_CL_GRABBER_RES_NOT_FOUND: errorMsg += tr("The resource on the firmware of the frame grabber not found"); break;
    case CAMERA_STATUS_CL_GRABBER_RES_NOT_AVAILABLE: errorMsg += tr("Device resource is not available for the frame grabber"); break;
    case CAMERA_STATUS_CL_GRABBER_NOT_VALID: errorMsg += tr("Specified parameter is invalid for current device resource"); break;
    case CAMERA_STATUS_CL_GRABBER_PRM_ILLEGAL: errorMsg += tr("The setting value for parameter is an illegal value or this frame grabber not supported"); break;
    case CAMERA_STATUS_CL_GRABBER_SERIAL_OPEN_FAILED: errorMsg += tr("The serial port open failed"); break;
    case CAMERA_STATUS_CL_GRABBER_NOT_START_ACQ: errorMsg += tr("The specified frame grabber doesn't received a start acquisition signal."); break;
    case CAMERA_STATUS_CL_GRABBER_NOT_SUPPORTED_FEATURE: errorMsg += tr("The frame grabber not supported this feature."); break;
    case CAMERA_STATUS_CL_GRABBER_UNKNOWN_ERROR: errorMsg += tr("Unknown error occurred in frame grabber"); break;


        //和AIA制定的标准相同
        /*#define CAMERA_AIA_SUCCESS                        0x0000 */
    case CAMERA_AIA_PACKET_RESEND: errorMsg += tr("The frame needs to be retransmitted"); break;
    case CAMERA_AIA_NOT_IMPLEMENTED: errorMsg += tr("Device does not support commands"); break;
    case CAMERA_AIA_INVALID_PARAMETER: errorMsg += tr("Illegal command parameters"); break;
    case CAMERA_AIA_INVALID_ADDRESS: errorMsg += tr("Inaccessible address"); break;
    case CAMERA_AIA_WRITE_PROTECT: errorMsg += tr("The accessed object cannot be written"); break;
    case CAMERA_AIA_BAD_ALIGNMENT: errorMsg += tr("Visited address is not aligned as required"); break;
    case CAMERA_AIA_ACCESS_DENIED: errorMsg += tr("No access"); break;
    case CAMERA_AIA_BUSY: errorMsg += tr("Command is processing"); break;
    case CAMERA_AIA_DEPRECATED: errorMsg += tr("0x8008-0x0800B 0x800F This instruction has been deprecated"); break;
    case CAMERA_AIA_PACKET_UNAVAILABLE: errorMsg += tr("Invalid package"); break;
    case CAMERA_AIA_DATA_OVERRUN: errorMsg += tr("Data overflow, usually more data than needed"); break;
    case CAMERA_AIA_INVALID_HEADER: errorMsg += tr("Some areas in the packet header do not match the protocol"); break;
    case CAMERA_AIA_PACKET_NOT_YET_AVAILABLE: errorMsg += tr("Image packet data is not ready yet. It is mostly used in trigger mode. Application access timeout"); break;
    case CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY: errorMsg += tr("Subcontracts that require access no longer exist. Mostly used for data retransmission is not in the buffer"); break;
    case CAMERA_AIA_PACKET_REMOVED_FROM_MEMORY: errorMsg += tr("CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY"); break;
    case CAMERA_AIA_NO_REF_TIME: errorMsg += tr("There is no reference clock source. When used for time synchronization commands"); break;
    case CAMERA_AIA_PACKET_TEMPORARILY_UNAVAILABLE: errorMsg += tr("Due to channel bandwidth issues, the current subcontracting is temporarily unavailable and needs to be accessed later"); break;
    case CAMERA_AIA_OVERFLOW: errorMsg += tr("Data overflow on the device, usually the queue is full"); break;
    case CAMERA_AIA_ACTION_LATE: errorMsg += tr("Command execution has exceeded valid specified time"); break;
    case CAMERA_AIA_ERROR: errorMsg += tr("error"); break;

        // 自定义
    case CAMERA_MV_SSR_COMM_ERROR: errorMsg += tr("SSR communication error"); break;
    case CAMERA_MV_SSR_TRAIN_ERROR: errorMsg += tr("SSR training error"); break;

    default: errorMsg += tr("Unknow(%1)").arg(status); break;
    }

    return errorMsg;
}

}   // namespace SpeedCamera
