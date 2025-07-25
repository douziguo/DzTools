/**
 *  @file    IKapCStat.h
 *  @brief   IKapC Status returned when function executed.
 *  @author  iTek OptoElectronics Ltd
 *  @par     Copyright (c) iTek OptoElectronics Ltd.
 *           All Rights Reserved
 *  @date    2017:06:19
 *  @version <1.0.0.1>
 */

#ifndef _IKAPCSTAT_H
#define _IKAPCSTAT_H

#include "IKapCType.h"

/*
 status format

 status ID:	16 bits - a ITKSTATUS_... constant
 level:		4 bits - a ITKSTATUS_LEVEL_... constant
 module:	4 bits - a ITKSTATUS_MODULE_... constant
 |------------------|-------------------|-------------|------------------|
 |31   reserved   24|23   module ID   20|19  level  16|15   status ID   0|
 |------------------|-------------------|-------------|------------------|
 */

#define ITKSTATUS uint32_t

// Status format location definitions
#define ITKSTATUS_MODULE_BIT_OFFSET 20
#define ITKSTATUS_LEVEL_BIT_OFFSET  16
#define ITKSTATUS_STATUS_BIT_OFFSET 0

// Status format size definitions
#define ITKSTATUS_MODULE_BIT_MASK 0x0f
#define ITKSTATUS_LEVEL_BIT_MASK  0x0f
#define ITKSTATUS_STATUS_BIT_MASK 0xffff

// module
#define ITKSTATUS_MODULE(status) (((status) >> ITKSTATUS_MODULE_BIT_OFFSET) & ITKSTATUS_MODULE_BIT_MASK)

#define ITKSTATUS_MODULE_DEVICE    0x01  //	1: Device module
#define ITKSTATUS_MODULE_BUFFER    0x02  //	2: Buffer module
#define ITKSTATUS_MODULE_LOG       0x03  //	3: Log module
#define ITKSTATUS_MODULE_MANAGER   0x04  //  4: API control module
#define ITKSTATUS_MODULE_STREAM    0x05  //	5: Stream module
#define ITKSTATUS_MODULE_PARAM     0x06  //	6: Parameter module
#define ITKSTATUS_MODULE_SERIAL    0x07  //	7: Serial module
#define ITKSTATUS_MODULE_EVENTINFO 0x08  //  8: Event information module
#define ITKSTATUS_MODULE_FEATURE   0x09  //  9: Feature module
#define ITKSTATUS_MODULE_VIEW      0x0A  //  10: View module
#define ITKSTATUS_MODULE_BOARD     0x0B  //  11: Board module
#define ITKSTATUS_MODULE_FILE      0x0C  //  12: File module

// level
#define ITKSTATUS_LEVEL(status) (((status) >> ITKSTATUS_LEVEL_BIT_OFFSET) & ITKSTATUS_LEVEL_BIT_MASK)

#define ITKSTATUS_LEVEL_FAT 0  //  fatal errors
#define ITKSTATUS_LEVEL_ERR 1  //	general errors
#define ITKSTATUS_LEVEL_WRN 2  //	warnings
#define ITKSTATUS_LEVEL_INF 3  //	informations

// id
#define ITKSTATUS_ID(status) ((status)&ITKSTATUS_STATUS_BIT_MASK)

#define ITKSTATUS_OK                         0x0000
#define ITKSTATUS_INVALID_HANDLE             0x0001
#define ITKSTATUS_INSUFFICIENT_RESOURCES     0x0002
#define ITKSTATUS_BUFFER_TOO_SMALL           0x0003
#define ITKSTATUS_MISSING_RESOURCE           0x0004
#define ITKSTATUS_UNINITIALIZE               0x0005
#define ITKSTATUS_DEVICE_ID_OUTOF_RANGE      0x0006
#define ITKSTATUS_SERAIL_PORT_NOT_AVAILABLE  0x0007
#define ITKSTATUS_XML_NOT_FOUND              0x0008
#define ITKSTATUS_DEVICE_NOT_ACCESSABLE      0x0009
#define ITKSTATUS_DEVICE_PERMISSION_DENY     0x000A
#define ITKSTATUS_REGISTRY_NOT_FOUND         0x000B
#define ITKSTATUS_XML_PARSE_ERROR            0x000C
#define ITKSTATUS_INVALID_ARG                0x000D
#define ITKSTATUS_INVALID_NAME               0x000E
#define ITKSTATUS_INCOMPATIBLE_FEATURE_TYPE  0x000F
#define ITKSTATUS_TIME_OUT                   0x0010
#define ITKSTATUS_COMMAND_CRASH              0x0011
#define ITKSTATUS_COMMAND_PARAM_OUT_OF_RANGE 0x0012
#define ITKSTATUS_COMMAND_NOT_ALLOW          0x0013
#define ITKSTATUS_COMMAND_NOT_PRASE          0x0014
#define ITKSTATUS_COMMAND_PENDING            0x0015
#define ITKSTATUS_ARG_OUT_OF_RANGE           0x0016
#define ITKSTATUS_NOT_IMPLEMENT              0x0017
#define ITKSTATUS_NO_MEMORY                  0x0018
#define ITKSTATUS_INCOMPATIBLE_ARG_TYPE      0x0019
#define ITKSTATUS_STREAM_IN_PROCESS          0x001A
#define ITKSTATUS_PRM_READ_ONLY              0x001B
#define ITKSTATUS_STREAM_IS_OPENED           0x001C
#define ITKSTATUS_SYSTEM_ERROR               0x001D
#define ITKSTATUS_INVALID_ADDRESS            0x001E
#define ITKSTATUS_BAD_ALIGNMENT              0x001F
#define ITKSTATUS_DEVICE_BUSY                0x0020
#define ITKSTATUS_DEVICE_IS_REMOVED          0x0021
#define ITKSTATUS_DEVICE_NOT_FOUND           0x0022
#define ITKSATTUS_BOARD_IS_OPENED            0x0023
#define ITKSTATUS_BOARD_NO_OPENED            0x0024
#define ITKSTATUS_PRM_WRITE_ONLY             0x0025
#define ITKSTATUS_BOARD_CONNECTION_FAIL      0x0026
#define ITKSTATUS_RUNTIME_ERROR              0x0027
#define ITKSTATUS_IO_ERROR                   0x0028
#define ITKSTATUS_BUFFER_OVERFLOW            0x0029
#define ITKSTATUS_COMMUNICATION_ERROR        0x0030
#define ITKSTATUS_CXP_CONTROL_CRC_ERROR      0x0031
#define ITKSTATUS_ACK_ID_NOT_COMPATIABLE     0x0032
#define ITKSTATUS_DEV_INVALID_HEADER         0x0033
#define ITKSTATUS_DEV_DSI_ENDPOINT_HALTED    0x0034
#define ITKSTATUS_DEV_DEI_ENDPOINT_HALTED    0x0035
#define ITKSTATUS_DEV_DATA_DISCARDED         0x0036
#define ITKSTATUS_DEV_DATA_OVERRUN           0x0037
#define ITKSTATUS_STREAM_ABORTED             0x0038
#define ITKSTATUS_DRIVER_NOT_MATCH           0x0039
#define ITKSTATUS_DEVICE_WRONG_USB_PORT      0x0040
#define ITKSTATUS_DEVICE_IS_FAULTY           0x0041
#define ITKSTATUS_CXP_TOPOLOGY_ERROR         0x0042

// level first so that it be visible instantly
#define ITKSTATUS_BUILD(level, id, module)                                                                                  \
    ((id) | (((level)&ITKSTATUS_LEVEL_BIT_MASK) << ITKSTATUS_LEVEL_BIT_OFFSET) |                                            \
     (((module)&ITKSTATUS_MODULE_BIT_MASK) << ITKSTATUS_MODULE_BIT_OFFSET))

/* Macros for adding single fields to status */
#define ITKSTATUS_ADD_ID(status, id)       ((status) | ((id)&ITKSTATUS_STATUS_BIT_MASK))
#define ITKSTATUS_ADD_LEVEL(status, level) ((status) | (((level)&ITKSTATUS_LEVEL_BIT_MASK) << ITKSTATUS_LEVEL_BIT_OFFSET))
#define ITKSTATUS_ADD_MODULE(status, module)                                                                                \
    ((status) | (((module)&ITKSTATUS_MODULE_BIT_MASK) << ITKSTATUS_MODULE_BIT_OFFSET))

/* Macros for adding module to status */
#define ITKSTATUS_DEVICE(status)    ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_DEVICE)
#define ITKSTATUS_BUFFER(status)    ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_BUFFER)
#define ITKSTATUS_LOG(status)       ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_LOG)
#define ITKSTATUS_MANAGER(status)   ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_MANAGER)
#define ITKSTATUS_STREAM(status)    ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_STREAM)
#define ITKSTATUS_PARAM(status)     ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_PARAM)
#define ITKSTATUS_SERIAL(status)    ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_SERIAL)
#define ITKSTATUS_EVENTINFO(status) ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_EVENTINFO)
#define ITKSTATUS_FEATURE(status)   ITKSTATUS_ADD_MODULE(status, ITKSTATUS_MODULE_FEATURE)

#endif
