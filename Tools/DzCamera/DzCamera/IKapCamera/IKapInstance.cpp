/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       IKapInstance.cpp
 * @brief      埃科光电相机
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "IKapInstance.h"

#include <QMap>
#include <QDebug>

namespace DzCamera {

IKapInstance::IKapInstance()
{
    auto res = ItkManInitialize();
    if (ITKSTATUS_OK != res) {
        qWarning().noquote() << IKapInstance::formatErrorMsg(res, "埃科光电相机 SDK 初始化失败");
    }
}

IKapInstance::~IKapInstance()
{
    auto res = ItkManTerminate();
    if (ITKSTATUS_OK != res) {
        qWarning().noquote() << IKapInstance::formatErrorMsg(res, "埃科光电相机 SDK 释放资源失败");
    }
}

// 解析错误信息
QString IKapInstance::formatErrorMsg(uint32_t res, const QString &msg)
{
    QString errorMsg = msg;

    if (res != ITKSTATUS_OK) {
        if (!msg.isEmpty()) {
            errorMsg += QObject::tr(", ");
        }
        errorMsg += QObject::tr("Error = 0x%1: ").arg(QString::number(res, 16).right(4));
    }

    QMap<uint32_t, QString> errorDescs = {
        {ITKSTATUS_INVALID_HANDLE, QObject::tr("Invalid Handle")},
        {ITKSTATUS_INSUFFICIENT_RESOURCES, QObject::tr("Insufficient Resources")},
        {ITKSTATUS_BUFFER_TOO_SMALL, QObject::tr("Buffer Too Small")},
        {ITKSTATUS_MISSING_RESOURCE, QObject::tr("Missing Resource")},
        {ITKSTATUS_UNINITIALIZE, QObject::tr("Uninitialize")},
        {ITKSTATUS_DEVICE_ID_OUTOF_RANGE, QObject::tr("Device Id Outof Range")},
        {ITKSTATUS_SERAIL_PORT_NOT_AVAILABLE, QObject::tr("Serail Port Not Available")},
        {ITKSTATUS_XML_NOT_FOUND, QObject::tr("Xml Not Found")},
        {ITKSTATUS_DEVICE_NOT_ACCESSABLE, QObject::tr("Device Not Accessable")},
        {ITKSTATUS_DEVICE_PERMISSION_DENY, QObject::tr("Device Permission Deny")},
        {ITKSTATUS_REGISTRY_NOT_FOUND, QObject::tr("Registry Not Found")},
        {ITKSTATUS_XML_PARSE_ERROR, QObject::tr("Xml Parse Error")},
        {ITKSTATUS_INVALID_ARG, QObject::tr("Invalid Arg")},
        {ITKSTATUS_INVALID_NAME, QObject::tr("Invalid Name")},
        {ITKSTATUS_INCOMPATIBLE_FEATURE_TYPE, QObject::tr("Incompatible Feature Type")},
        {ITKSTATUS_TIME_OUT, QObject::tr("Time Out")},
        {ITKSTATUS_COMMAND_CRASH, QObject::tr("Command Crash")},
        {ITKSTATUS_COMMAND_PARAM_OUT_OF_RANGE, QObject::tr("Command Param Out Of Range")},
        {ITKSTATUS_COMMAND_NOT_ALLOW, QObject::tr("Command Not Allow")},
        {ITKSTATUS_COMMAND_NOT_PRASE, QObject::tr("Command Not Prase")},
        {ITKSTATUS_COMMAND_PENDING, QObject::tr("Command Pending")},
        {ITKSTATUS_ARG_OUT_OF_RANGE, QObject::tr("Arg Out Of Range")},
        {ITKSTATUS_NOT_IMPLEMENT, QObject::tr("Not Implement")},
        {ITKSTATUS_NO_MEMORY, QObject::tr("No Memory")},
        {ITKSTATUS_INCOMPATIBLE_ARG_TYPE, QObject::tr("Incompatible Arg Type")},
        {ITKSTATUS_STREAM_IN_PROCESS, QObject::tr("Stream In Process")},
        {ITKSTATUS_PRM_READ_ONLY, QObject::tr("Prm Read Only")},
        {ITKSTATUS_STREAM_IS_OPENED, QObject::tr("Stream Is Opened")},
        {ITKSTATUS_SYSTEM_ERROR, QObject::tr("System Error")},
        {ITKSTATUS_INVALID_ADDRESS, QObject::tr("Invalid Address")},
        {ITKSTATUS_BAD_ALIGNMENT, QObject::tr("Bad Alignment")},
        {ITKSTATUS_DEVICE_BUSY, QObject::tr("Device Busy")},
        {ITKSTATUS_DEVICE_IS_REMOVED, QObject::tr("Device Is Removed")},
        {ITKSTATUS_DEVICE_NOT_FOUND, QObject::tr("Device Not Found")},
        {ITKSATTUS_BOARD_IS_OPENED, QObject::tr("Itksattus Board Is Opened")},
        {ITKSTATUS_BOARD_NO_OPENED, QObject::tr("Board No Opened")},
        {ITKSTATUS_PRM_WRITE_ONLY, QObject::tr("Prm Write Only")},
        {ITKSTATUS_BOARD_CONNECTION_FAIL, QObject::tr("Board Connection Fail")},
        {ITKSTATUS_RUNTIME_ERROR, QObject::tr("Runtime Error")},
        {ITKSTATUS_IO_ERROR, QObject::tr("Io Error")},
        {ITKSTATUS_BUFFER_OVERFLOW, QObject::tr("Buffer Overflow")},
        {ITKSTATUS_COMMUNICATION_ERROR, QObject::tr("Communication Error")},
        {ITKSTATUS_CXP_CONTROL_CRC_ERROR, QObject::tr("Cxp Control Crc Error")},
        {ITKSTATUS_ACK_ID_NOT_COMPATIABLE, QObject::tr("Ack Id Not Compatiable")},
        {ITKSTATUS_DEV_INVALID_HEADER, QObject::tr("Dev Invalid Header")},
        {ITKSTATUS_DEV_DSI_ENDPOINT_HALTED, QObject::tr("Dev Dsi Endpoint Halted")},
        {ITKSTATUS_DEV_DEI_ENDPOINT_HALTED, QObject::tr("Dev Dei Endpoint Halted")},
        {ITKSTATUS_DEV_DATA_DISCARDED, QObject::tr("Dev Data Discarded")},
        {ITKSTATUS_DEV_DATA_OVERRUN, QObject::tr("Dev Data Overrun")},
        {ITKSTATUS_STREAM_ABORTED, QObject::tr("Stream Aborted")},
        {ITKSTATUS_DRIVER_NOT_MATCH, QObject::tr("Driver Not Match")},
        {ITKSTATUS_DEVICE_WRONG_USB_PORT, QObject::tr("Device Wrong Usb Port")},
        {ITKSTATUS_DEVICE_IS_FAULTY, QObject::tr("Device Is Faulty")},
        {ITKSTATUS_CXP_TOPOLOGY_ERROR, QObject::tr("Cxp Topology Error")},
    };

    errorMsg += errorDescs.value(res, QObject::tr("Unknow(%1)").arg(res));

    return errorMsg;
}

// 解析错误信息
QString IKapInstance::formatBoardErrorMsg(int res, const QString &msg)
{
    QString errorMsg = msg;

    if (res != IK_RTN_OK) {
        if (!msg.isEmpty()) {
            errorMsg += QObject::tr(", ");
        }
        errorMsg += QObject::tr("Error = 0x%1: ").arg(QString::number(res, 16).right(8));
    }

    QMap<uint32_t, QString> errorDescs = {
        {IKStatus_BoardNotFound, QObject::tr("Cannot find board")},
        {IKStatus_AllocMemoryFail, QObject::tr("Fail to allocate memory")},
        {IKStatus_InvalidParameter, QObject::tr("Invalid parameter")},
        {IKStatus_OpenBoardFail, QObject::tr("Fail to open board")},
        {IKStatus_TimeOut, QObject::tr("Operation timeout")},
        {IKStatus_WinError, QObject::tr("System error")},
        {IKStatus_BoardNotOpen, QObject::tr("Board is not open")},
        {IKStatus_ConfigFilePathInvalid, QObject::tr("Invalid configuration file path")},
        {IKStatus_ConfigParameterInvalid, QObject::tr("Invalid configuration parameter")},
        {IKStatus_ZLP, QObject::tr("USB3.0 zero length packet")},
        {IKStatus_ThreadUnsetup, QObject::tr("Fail to create the thread")},
        {IKStatus_ThreadExist, QObject::tr("The current thread already exists")},
        {IKStatus_CameraUnsupport, QObject::tr("The camera type is not supported")},
        {IKStatus_XMLFileLoadFail, QObject::tr("Fail to load XML file")},
        {IKStatus_NodeNotExist, QObject::tr("XML file node does not exist")},
        {IKStatus_WriteSerialFail, QObject::tr("Fail for serial writing")},
        {IKStatus_CommandNotExist, QObject::tr("The serial command does not exist")},
        {IKStatus_CommandCollision, QObject::tr("Serial command conflict")},
        {IKStatus_CommandMissRequirement,
         QObject::tr("The serial port command does not meet the requirements")},
        {IKStatus_CommandNotAllow, QObject::tr("The serial port command is not allowed")},
        {IKStatus_CommandSyntaxError, QObject::tr("Serial port command format error")},
        {IKStatus_NodeTypeDismatch, QObject::tr("XML node does not match")},
        {IKStatus_FeatureUnSupport, QObject::tr("The camera feature is not supported")},
        {IKStatus_CommandResultNoExit, QObject::tr("Camera execution result is meaningless")},
        {IKStatus_CLRegPathNotFound, QObject::tr("Cannot find CamaraLinkPath")},
        {IKStatus_CLDLLNotFound, QObject::tr("Cannot find CLallserial.dll")},
        {IKStatus_CameraNotFound, QObject::tr("Cannot find camera")},
        {IKStatus_BufferTooSmall, QObject::tr("Input buffer is too small")},
        {IKStatus_BaudrateNotSupport, QObject::tr("The baud rate is not supported")},
        {IKStatus_CameraInUse, QObject::tr("Camera is in use")},
        {IKStatus_FPGA_EraseFlashFail, QObject::tr("Fail to erase FPGA")},
        {IKStatus_FPGA_CheckFail, QObject::tr("Fail to check FPGA firmware")},
        {IKStatus_BoardNotBindingCOM, QObject::tr("Board is not bound to COM")},
        {IKStatus_ReadRegFail, QObject::tr("Fail to read camera status register")},
        {IKStatus_Invalid_Mutex, QObject::tr("Invalid board lock handle")},
        {IKStatus_Mutex_Locked, QObject::tr("Board is occupied")},
        {IKStatus_Invalid_Handle, QObject::tr("Invalid device handle")},
        {IKStatus_Set_Info_Error, QObject::tr("Invalid or wrong setting parameter value")},
        {IKStatus_Grab_Pending, QObject::tr("Image acquisition process is in progress")},
        {IKStatus_Insufficient_Resource, QObject::tr("System does not have enough resources")},
        {IKStatus_Grab_Abort, QObject::tr("Abandon the current acquisition")},
        {IKStatus_Need_Reboot,
         QObject::tr("A fatal error occurred in the system, and the computer must be restarted to "
                     "return to normal")},
        {IKStatus_Need_Restart,
         QObject::tr("An error occurred in the frame grabber, and the frame grabber needs to be "
                     "reopened to recover to normal")},
        {IKStatus_Not_Implement, QObject::tr("Function not implemented")},
        {IKStatus_Not_In_Callback,
         QObject::tr("This function should be run in callback function, but actually not")},
        {IKStatus_Not_Match_Driver_Version, QObject::tr("Driver version mismatch")},
        {IKStatus_Prm_Not_Available,
         QObject::tr("The parameter is currently unreadable and not writable")},
        {IKStatus_Prm_Locked,
         QObject::tr("The parameters of frame grabber are locked and cannot be modified")},
        {IKStatus_Logic_Error, QObject::tr("Logic error")},
    };

    errorMsg += errorDescs.value(res, QObject::tr("Unknow(%1)").arg(res));

    return errorMsg;
}

} // namespace SpeedCamera
