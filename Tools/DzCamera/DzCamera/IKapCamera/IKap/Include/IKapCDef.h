/**
 *  @file    IKapCDef.h
 *  @brief   IKapC bindings - macro definitions.
 *  @author  iTek OptoElectronics Ltd
 *  @par     Copyright (c) iTek OptoElectronics Ltd.
 *           All Rights Reserved
 *  @date    2017:06:19
 *  @version <1.0.0.1>
 */

#ifndef _IKAPCDEF_H
#define _IKAPCDEF_H
#include "IKapCStat.h"

#if defined(_MSC_VER) || defined(__BORLANDC__)
#    ifdef IKAPC_EXPORTS
#        define IKAPC_API __declspec(dllexport)
#    else
#        define IKAPC_API __declspec(dllimport)
#    endif
#    define IKAPC_CC      _stdcall
#    define IKAPC_PACKING 8
#elif defined(__GNUC__) || defined(SWIG)
#    define IKAPC_API
#    define IKAPC_CC
#    define IKAPC_PACKING 8
#else
#    error Unsupported platform
#endif

#define IKAPC_DECLARE_HANDLE(name)                                                                                          \
                                                                                                                            \
    typedef struct name##_ {                                                                                                \
        int unused;                                                                                                      \
    } *name;

/** @brief A value for invalid / uninitialized handles. */
#ifdef __cplusplus
#    define GENAPIC_INVALID_HANDLE (0)
#else
#    define GENAPIC_INVALID_HANDLE ((void *)0)
#endif

/****************************************************************************
 *	Manager Parameters
 ****************************************************************************/
#define ITKMANAGER_PRM_FIRST    0
#define ITKMANAGER_PRM(n, size) ((((n) + ITKMANAGER_PRM_FIRST) << 16) | (size))

#define ITKMANAGER_COAXPRESS_12_SUPPORT                ITKMANAGER_PRM(0, 4)
#define ITKMANAGER_COAXPRESS_COMMUNICATION_TAG_SUPPORT ITKMANAGER_PRM(1, 4)
#define ITKMANAGER_COAXPRESS_CONTROL_PACKET_MAX_SIZE   ITKMANAGER_PRM(2, 4)
#define ITKMANAGER_COAXPRESS_STREAM_PACKET_MAX_SIZE    ITKMANAGER_PRM(3, 4)
#define ITKMANAGER_COAXPRESS_RW_REGISTER_MAX_TIME      ITKMANAGER_PRM(4, 4)
#define ITKMANAGER_ENABLED_MANAGER_MODULES                                                                                  \
    ITKMANAGER_PRM(                                                                                                         \
        5, 4) /**< \brief eg: setPrm(ITKMANAGER_ENABLED_MANAGER_MODULES,ITKMANAGER_SET_ENABLE(MANAGER_TYPE_GV,0)) can       \
                 disable GV manager   getPrm(ITKMANAGER_ENABLED_MANAGER_MODULES,pValue)                                     \
                 ITKMANAGER_GET_ENABLE(*pValue,MANAGER_TYPE_GV) return 0 or 1 means GV Manager enabled or not. */

#define ITKMANAGER_SET_ENABLE(n, value) ((n << 16) | (value))
#define ITKMANAGER_GET_ENABLE(value, n) ((value) & (1 << n))
enum MANAGER_TYPE_LIST
{
    MANAGER_TYPE_CL   = 0,
    MANAGER_TYPE_GV   = 1,
    MANAGER_TYPE_CXP  = 2,
    MANAGER_TYPE_U3V  = 3,
    MANAGER_TYPE_XGVB = 4,
    MANAGER_TYPE_PCIE = 5
};
typedef uint32_t MANAGER_TYPE;

/****************************************************************************
 *	Board Parameters
 ****************************************************************************/
#define ITKBOARD_PRM_FIRST    0
#define ITKBOARD_PRM(n, size) ((((n) + ITKDEV_PRM_FIRST) << 16) | (size))

#define ITKBOARD_PRM_WIDTH    ITKBOARD_PRM(0, 4) /**< \brief board width          */
#define ITKBOARD_PRM_HEIGHT   ITKBOARD_PRM(1, 4) /**< \brief board height         */
#define ITKBOARD_PRM_OFFSET_X ITKBOARD_PRM(2, 4) /**< \brief board offset x       */
#define ITKBOARD_PRM_OFFSET_Y ITKBOARD_PRM(3, 4) /**< \brief board offset y       */

/****************************************************************************
 *	Device Parameters
 ****************************************************************************/
#define ITKDEV_PRM_FIRST    0
#define ITKDEV_PRM(n, size) ((((n) + ITKDEV_PRM_FIRST) << 16) | (size))

#define ITKDEV_PRM_HEARTBEAT_TIMEOUT ITKDEV_PRM(0, 4) /**< \brief device heartbeat timeout.						*/
#define ITKDEV_PRM_INTERFACE_TYPE    ITKDEV_PRM(1, 4) /**< \brief device interface type.                          */

/* IKapC device access modes */
#define ITKDEV_VAL_ACCESS_MODE_MONITOR 0        /**< \brief access in monitor mode(read only)*/
#define ITKDEV_VAL_ACCESS_MODE_CONTROL (1 << 0) /**< \brief access in control mode(read/write feature)*/
#define ITKDEV_VAL_ACCESS_MODE_STREAM  (1 << 1) /**< \brief access in stream mode(grab image)*/
#define ITKDEV_VAL_ACCESS_MODE_EXCLUSIVE                                                                                    \
    (1 << 2) /**< \brief access in exclusive mode(only one process could control device)*/

/* Device support event type */
#define ITKDEV_VAL_EVENT_TYPE_DEV_REMOVE                                                                                    \
    0x00010000 /**< \brief Call the callback function after the device closed.                */
#define ITKDEV_VAL_EVENT_TYPE_FEATURE_VALUE_CHANGED                                                                         \
    0x00020000 /**< \brief Call the callback function after the device feature value changed. */
#define ITKDEV_VAL_EVENT_TYPE_FRAME_TRIGGER_IGNORE                                                                          \
    0x00040000 /**< \brief Call when frame trigger ignore happen.                             */
#define ITKDEV_VAL_EVENT_TYPE_LINE_TRIGGER_IGNORE                                                                           \
    0x00080000 /**< \brief Call when line trigger ignore happen.							   */
#define ITKDEV_VAL_EVENT_TYPE_FRAME_TRIGGER                                                                                 \
    0x00100000 /**< \brief Call when frame trigger happen.					                   */

#define ITKDEV_VAL_EVENT_TYPE_MASK 0xffff0000

/****************************************************************************
 *	Feature Parameters
 ****************************************************************************/

/* IKapC feature data types */
#define ITKFEATURE_VAL_TYPE_UNDEFINED 0  /**< \brief feature type invalid. */
#define ITKFEATURE_VAL_TYPE_INT32     1  /**< \brief feature represents an 32bit integer-valued parameter. */
#define ITKFEATURE_VAL_TYPE_INT64     2  /**< \brief feature represents an 64bit integer-valued parameter. */
#define ITKFEATURE_VAL_TYPE_FLOAT     3  /**< \brief feature represents a 32bit floating point-valued parameter. */
#define ITKFEATURE_VAL_TYPE_DOUBLE    4  /**< \brief feature represents a 64bit floating point-valued parameter. */
#define ITKFEATURE_VAL_TYPE_BOOL      5  /**< \brief Node represents a boolean (true/false) parameter. */
#define ITKFEATURE_VAL_TYPE_ENUM      6  /**< \brief Node represents an 'enumeration entry' parameter. */
#define ITKFEATURE_VAL_TYPE_STRING    7  /**< \brief Node represents a string-valued parameter. */
#define ITKFEATURE_VAL_TYPE_COMMAND   8  /**< \brief Node can trigger a command. */
#define ITKFEATURE_VAL_TYPE_CATEGORY  9  /**< \brief Category include other features. */
#define ITKFEATURE_VAL_TYPE_REGISTER  10 /**< \brief Node represents a register. */

/* IKapC feature access mode */
#define ITKFEATURE_VAL_ACCESS_MODE_UNDEFINED 0 /**< \brief Access mode invalid. */
#define ITKFEATURE_VAL_ACCESS_MODE_RW        1 /**< \brief Read and Write. */
#define ITKFEATURE_VAL_ACCESS_MODE_RO        2 /**< \brief Read Only. */
#define ITKFEATURE_VAL_ACCESS_MODE_WO        3 /**< \brief Write Only.*/
#define ITKFEATURE_VAL_ACCESS_MODE_NI        4 /**< \brief Not implemented. */
#define ITKFEATURE_VAL_ACCESS_MODE_NA        5 /**< \brief Not available. */

/* IKapC feature name space */
#define ITKFEATURE_VAL_NAME_SPACE_UNDEFINED 0 /**< \brief Name space invalid. */
#define ITKFEATURE_VAL_NAME_SPACE_CUSTOM    1 /**< \brief Name resides in custom name space. */
#define ITKFEATURE_VAL_NAME_SPACE_STANDARD  2 /**< \brief Name resides in one of the standard name spaces. */

/* IKapC feature representation */
#define ITKFEATURE_VAL_REPRESENTATION_UNDEFINED   0 /**< \brief Undefined representation.					*/
#define ITKFEATURE_VAL_REPRESENTATION_LINEAR      1 /**< \brief The feature follows a linear scale.			*/
#define ITKFEATURE_VAL_REPRESENTATION_LOGARITHMIC 2 /**< \brief The feature follows a logarithmic scale.	*/
#define ITKFEATURE_VAL_REPRESENTATION_BOOLEAN                                                                               \
    3 /**< \brief The feature is a boolean (can have two values: zero or non-zero).	*/
#define ITKFEATURE_VAL_REPRESENTATION_PURENUMBER  4 /**< \brief The feature using an edit box only with decimal display.*/
#define ITKFEATURE_VAL_REPRESENTATION_HEXNUMBER   5 /**< \brief The feature using an edit box with hexadecimal display.*/
#define ITKFEATURE_VAL_REPRESENTATION_IPV4ADDRESS 6 /**< \brief The feature showing like an IP address.*/
#define ITKFEATURE_VAL_REPRESENTATION_MACADDRESS  7 /**< \brief The feature showing like a MAC address.*/

/* IKapC feature visibility	*/
#define ITKFEATURE_VAL_VISIBILITY_UNDEFINED 0 /**< \brief Undefined visibility level.		*/
#define ITKFEATURE_VAL_VISIBILITY_BEGINNER                                                                                  \
    1 /**< \brief Specifies that the feature should be made visible to any user.		*/
#define ITKFEATURE_VAL_VISIBILITY_EXPERT                                                                                    \
    2 /**< \brief Specifies that the feature should be made visible to users with a certain level of expertise.		*/
#define ITKFEATURE_VAL_VISIBILITY_GURU                                                                                      \
    3 /**< \brief Specifies that the feature should be made visible to users with a high level of expertise.		*/
#define ITKFEATURE_VAL_VISIBILITY_INVISIBLE                                                                                 \
    4 /**< \brief Specifies that the feature should not be made visible to any user.This level of visibility is normally    \
         used on obsolete or internal features.		*/

/* IKapC feature signed */
#define ITKFEATURE_VAL_SIGN_UNDEFINED 0 /**< \brief Sign is undefined.								*/
#define ITKFEATURE_VAL_SIGN_SIGNED    1 /**< \brief The feature is a signed integer of float.		*/
#define ITKEFATURE_VAL_SIGN_UNSIGNED  2 /**< \brief The feature is an unsigned integer of float.	*/

/****************************************************************************
 *	Event info Parameters
 ****************************************************************************/
#define ITKEVENTINFO_PRM_FIRST    0
#define ITKEVENTINFO_PRM(n, size) ((((n) + ITKDEV_PRM_FIRST) << 16) | (size))

#define ITKEVENTINFO_PRM_TYPE            ITKEVENTINFO_PRM(0, 4)   /**< \brief Event info type.                   */
#define ITKEVENTINFO_PRM_FEATURE_NAME    ITKEVENTINFO_PRM(1, 128) /**< \brief Event info of feature name.        */
#define ITKEVENTINFO_PRM_HOST_TIME_STAMP ITKEVENTINFO_PRM(2, 8)   /**< \brief Host time stamp.                   */
#define ITKEVENTINFO_PRM_BLOCK_ID        ITKEVENTINFO_PRM(3, 8)   /**< \brief Block id.                          */
#define ITKEVENTINFO_PRM_EVENT_ID        ITKEVENTINFO_PRM(4, 2)   /**< \brief Event info of EventID.             */
#define ITKEVENTINFO_PRM_TIMESTAMP       ITKEVENTINFO_PRM(5, 8)   /**< \brief Event info of timestamp.           */
#define ITKEVENTINFO_PRM_DATA            ITKEVENTINFO_PRM(6, 256) /**< \brief Event info of data.                */

/****************************************************************************
 *	Buffer Parameters
 ****************************************************************************/
#define ITKBUFFFER_PRM_FIRST   0
#define ITKBUFFER_PRM(n, size) ((((n) + ITKBUFFFER_PRM_FIRST) << 16) | (size))

#define ITKBUFFER_PRM_FORMAT             ITKBUFFER_PRM(0, 4)              /**< \brief Buffer pixel format.				*/
#define ITKBUFFER_PRM_DATA_BIT           ITKBUFFER_PRM(1, 4)              /**< \brief Buffer pixel data size in byte.		*/
#define ITKBUFFER_PRM_PIXEL_DEPTH        ITKBUFFER_PRM(2, 4)              /**< \brief Buffer pixel depth.					*/
#define ITKBUFFER_PRM_WIDTH              ITKBUFFER_PRM(3, 8)              /**< \brief Buffer width.						*/
#define ITKBUFFER_PRM_HEIGHT             ITKBUFFER_PRM(4, 8)              /**< \brief Buffer height.						*/
#define ITKBUFFER_PRM_ADDRESS            ITKBUFFER_PRM(5, sizeof(void *)) /**< \brief Buffer address.						*/
#define ITKBUFFER_PRM_HOST_COUNTER_STAMP ITKBUFFER_PRM(6, 8)              /**< \brief Buffer host counter stamp.			*/
#define ITKBUFFER_PRM_STATE              ITKBUFFER_PRM(7, 4)              /**< \brief Buffer state.						*/
#define ITKBUFFER_PRM_SIGNED             ITKBUFFER_PRM(8, 4)              /**< \brief Sign of buffer state.				*/
#define ITKBUFFER_PRM_SIZE                                                                                                  \
    ITKBUFFER_PRM(9, 8) /**< \brief Buffer size,which is equals to image size in IMAGE PAYLOAD TYPE MODE*/
#define ITKBUFFER_PRM_BLOCK_ID                                                                                              \
    ITKBUFFER_PRM(                                                                                                          \
        10, 8) /**< \brief Buffer bloc id. For GigEVision Camera, the sequence number starts with 1 and wraps at 65535. The \
                  value 0 has a special meaning and indicates that this feature is not supported by the camera.*/
#define ITKBUFFER_PRM_READY_LINES ITKBUFFER_PRM(11, 8) /**< \brief Current ready lines in buffer.      */
#define ITKBUFFER_PRM_ERROR_REASON                                                                                          \
    ITKBUFFER_PRM(                                                                                                          \
        12, 4) /**< \brief error reason of buffer, 0 means complete buffer other value means incomplete buffer.      */
#define ITKBUFFER_PRM_RSND_PKT_COUNT                 ITKBUFFER_PRM(13, 8) /**< \brief Current resend packet count in buffer.*/
#define ITKBUFFER_PRM_LOST_PKT_COUNT                 ITKBUFFER_PRM(14, 8) /**< \brief Current lost packet count in buffer.*/
#define ITKBUFFER_PRM_FIND_LINE_RESULT               ITKBUFFER_PRM(15, 33 * 2 * 8) /**< \brief Current result of fine line in buffer.*/
#define ITKBUFFER_PRM_EXCHANGE_WIDTH_HEIGHT          ITKBUFFER_PRM(16, 4) /**< \brief Exchange Buffer's width and height.*/
#define ITKBUFFER_PRM_BATCH_STATUS_ADDRESS           ITKBUFFER_PRM(17, sizeof(void *)) /**< \brief batch status address. */
#define ITKBUFFER_PRM_BURR_DECTION_RESULT            ITKBUFFER_PRM(18, 1)              /**< \brief Burr Dection Result. */
#define ITKBUFFER_PRM_BURR_DECTION_RESULT_COORDINATE ITKBUFFER_PRM(19, 12) /**< \brief Burr Dection Result Coordinate. */
#define ITKBUFFER_PRM_BURR_DECTION_DEBUG             ITKBUFFER_PRM(20, 8)  /**< \brief Burr Dection Result debug. */
#define ITKBUFFER_PRM_PAYLOAD_TYPE                    ITKBUFFER_PRM(21, 4)  /**< \brief Stream Payload Type. */
#define ITKBUFFER_PRM_IMAGE_SIZE                                                                                            \
    ITKBUFFER_PRM(22, 4) /**< \brief image size, which is calculated with formult: size = width*height*data_bits/8. */

/* Buffer data format definitions */
// (32-bit format descriptor)
//-------------------------------------------------------------------------------
// Bits     Description
//-------------------------------------------------------------------------------
// 0-7:     Index(used by internal implementation as an index to function table)
// 8-15:    Number of bits per pixel
// 16-23:   Pixel depth
// 24:		Color (true if it's a color format)
// 25:		Sign (used by monochrome formats)
//-------------------------------------------------------------------------------
#define ITKBUFFER_FORMAT(nDepth, nBits, index) (((nDepth) << 16) | ((nBits) << 8) | index)

// Bit fields

// Color: bit 24
#define ITKBUFFER_FORMAT_MONO  0x00000000 /**< \brief Buffer format is monochrome.			*/
#define ITKBUFFER_FORMAT_COLOR 0x01000000 /**< \brief Buffer format is color.					*/

// Sign: bit 25
#define ITKBUFFER_FORMAT_UNSIGNED 0x00000000 /**< \brief Buffer format is unsigned.				*/
#define ITKBUFFER_FORMAT_SIGNED   0x02000000 /**< \brief Buffer format is signed.				*/

// Monochrome data formats
#define ITKBUFFER_VAL_FORMAT_MONO8                                                                                          \
    (ITKBUFFER_FORMAT(8, 8, 0x01) | ITKBUFFER_FORMAT_MONO |                                                                 \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 8 format.		            */
#define ITKBUFFER_VAL_FORMAT_MONO10                                                                                         \
    (ITKBUFFER_FORMAT(10, 16, 0x02) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 10 format.				    */
#define ITKBUFFER_VAL_FORMAT_MONO10PACKED                                                                                   \
    (ITKBUFFER_FORMAT(10, 12, 0x03) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 10 packed format.		    */
#define ITKBUFFER_VAL_FORMAT_MONO12                                                                                         \
    (ITKBUFFER_FORMAT(12, 16, 0x04) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 12 format.			        */
#define ITKBUFFER_VAL_FORMAT_MONO12PACKED                                                                                   \
    (ITKBUFFER_FORMAT(12, 12, 0x05) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 12 packed format.		    */
#define ITKBUFFER_VAL_FORMAT_MONO14                                                                                         \
    (ITKBUFFER_FORMAT(14, 16, 0x06) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochroms 14 format.				    */
#define ITKBUFFER_VAL_FORMAT_MONO16                                                                                         \
    (ITKBUFFER_FORMAT(16, 16, 0x07) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 16 format.				    */

#define ITKBUFFER_VAL_FORMAT_RGB888                                                                                         \
    (ITKBUFFER_FORMAT(8, 24, 0x08) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color RGB 8-8-8 format.				*/
#define ITKBUFFER_VAL_FORMAT_RGB101010                                                                                      \
    (ITKBUFFER_FORMAT(10, 48, 0x09) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color RGB 10-10-10 format.				*/
#define ITKBUFFER_VAL_FORMAT_RGB121212                                                                                      \
    (ITKBUFFER_FORMAT(12, 48, 0x0A) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color RGB 12-12-12 format.				*/
#define ITKBUFFER_VAL_FORMAT_RGB141414                                                                                      \
    (ITKBUFFER_FORMAT(14, 48, 0x0B) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color RGB 14-14-14 format.				*/
#define ITKBUFFER_VAL_FORMAT_RGB161616                                                                                      \
    (ITKBUFFER_FORMAT(16, 48, 0x0C) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color RGB 16-16-16 format.				*/

#define ITKBUFFER_VAL_FORMAT_BGR888                                                                                         \
    (ITKBUFFER_FORMAT(8, 24, 0x0D) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color BGR 8-8-8 format.				*/
#define ITKBUFFER_VAL_FORMAT_BGR101010                                                                                      \
    (ITKBUFFER_FORMAT(10, 48, 0x0E) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color BGR 10-10-10 format.				*/
#define ITKBUFFER_VAL_FORMAT_BGR121212                                                                                      \
    (ITKBUFFER_FORMAT(12, 48, 0x0F) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color BGR 12-12-12 format.				*/
#define ITKBUFFER_VAL_FORMAT_BGR141414                                                                                      \
    (ITKBUFFER_FORMAT(14, 48, 0x10) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color BGR 14-14-14 format.				*/
#define ITKBUFFER_VAL_FORMAT_BGR161616                                                                                      \
    (ITKBUFFER_FORMAT(16, 48, 0x11) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color BGR 16-16-16 format.				*/

#define ITKBUFFER_VAL_FORMAT_BAYER_GR8                                                                                      \
    (ITKBUFFER_FORMAT(8, 8, 0x12) | ITKBUFFER_FORMAT_COLOR |                                                                \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 8 format.				*/
#define ITKBUFFER_VAL_FORMAT_BAYER_RG8                                                                                      \
    (ITKBUFFER_FORMAT(8, 8, 0x13) | ITKBUFFER_FORMAT_COLOR |                                                                \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 8 format.				*/
#define ITKBUFFER_VAL_FORMAT_BAYER_GB8                                                                                      \
    (ITKBUFFER_FORMAT(8, 8, 0x14) | ITKBUFFER_FORMAT_COLOR |                                                                \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 8 format.				*/
#define ITKBUFFER_VAL_FORMAT_BAYER_BG8                                                                                      \
    (ITKBUFFER_FORMAT(8, 8, 0x15) | ITKBUFFER_FORMAT_COLOR |                                                                \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 8 format.				*/

#define ITKBUFFER_VAL_FORMAT_BAYER_GR10                                                                                     \
    (ITKBUFFER_FORMAT(10, 16, 0x16) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 10 format.				*/
#define ITKBUFFER_VAL_FORMAT_BAYER_RG10                                                                                     \
    (ITKBUFFER_FORMAT(10, 16, 0x17) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 10 format.				*/
#define ITKBUFFER_VAL_FORMAT_BAYER_GB10                                                                                     \
    (ITKBUFFER_FORMAT(10, 16, 0x18) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 10 format.				*/
#define ITKBUFFER_VAL_FORMAT_BAYER_BG10                                                                                     \
    (ITKBUFFER_FORMAT(10, 16, 0x19) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 10 format.				*/

#define ITKBUFFER_VAL_FORMAT_BAYER_GR10PACKED                                                                               \
    (ITKBUFFER_FORMAT(10, 12, 0x1A) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 10 pakced format.       */
#define ITKBUFFER_VAL_FORMAT_BAYER_RG10PACKED                                                                               \
    (ITKBUFFER_FORMAT(10, 12, 0x1B) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 10 packed format.       */
#define ITKBUFFER_VAL_FORMAT_BAYER_GB10PACKED                                                                               \
    (ITKBUFFER_FORMAT(10, 12, 0x1C) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 10 packed format.       */
#define ITKBUFFER_VAL_FORMAT_BAYER_BG10PACKED                                                                               \
    (ITKBUFFER_FORMAT(10, 12, 0x1D) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 10 pakced format.       */

#define ITKBUFFER_VAL_FORMAT_BAYER_GR12                                                                                     \
    (ITKBUFFER_FORMAT(12, 16, 0x1E) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 12 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_RG12                                                                                     \
    (ITKBUFFER_FORMAT(12, 16, 0x1F) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 12 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_GB12                                                                                     \
    (ITKBUFFER_FORMAT(12, 16, 0x20) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 12 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_BG12                                                                                     \
    (ITKBUFFER_FORMAT(12, 16, 0x21) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 12 format.*/

#define ITKBUFFER_VAL_FORMAT_YUV422_8_YUYV                                                                                  \
    (ITKBUFFER_FORMAT(8, 16, 0x22) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's YUV 4:2:2 format(YUYV).*/
#define ITKBUFFER_VAL_FORMAT_YUV422_8_UYUV                                                                                  \
    (ITKBUFFER_FORMAT(8, 16, 0x23) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a YUV 4:2:2 format(UYUV). Not use*/
#define ITKBUFFER_VAL_FORMAT_COORD3D_C16                                                                                    \
    (ITKBUFFER_FORMAT(16, 16, 0x24) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a coord3D_C16 format.*/
#define ITKBUFFER_VAL_FORMAT_COORD3D_AC16                                                                                   \
    (ITKBUFFER_FORMAT(16, 32, 0x25) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a coord3D_AC16 format.*/
#define ITKBUFFER_VAL_FORMAT_COORD3D_ACR16                                                                                  \
    (ITKBUFFER_FORMAT(16, 48, 0x26) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a coord3D_ACR16 format.*/
#define ITKBUFFER_VAL_FORMAT_YUV422_8_UYVY                                                                                  \
    (ITKBUFFER_FORMAT(8, 16, 0x27) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's YUV 4:2:2 format(UYVY).*/

#define ITKBUFFER_VAL_FORMAT_MONO8PACKED                                                                                    \
    (ITKBUFFER_FORMAT(8, 8, 0x28) | ITKBUFFER_FORMAT_COLOR |                                                                \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color monochrome 8 packed format.		*/
#define ITKBUFFER_VAL_FORMAT_RGB888PACKED                                                                                   \
    (ITKBUFFER_FORMAT(8, 24, 0x29) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color RGB 8-8-8 packed format.		    */
#define ITKBUFFER_VAL_FORMAT_BGR888PACKED                                                                                   \
    (ITKBUFFER_FORMAT(8, 24, 0x2A) | ITKBUFFER_FORMAT_COLOR |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color BGR 8-8-8 packed format.		    */

#define ITKBUFFER_VAL_FORMAT_PCD                                                                                            \
    (ITKBUFFER_FORMAT(32, 128, 0x2B) | ITKBUFFER_FORMAT_MONO |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color point cloud data format                                  \
                                   float(x)float(y)float(z)uint32(Luminance).		    */

#define ITKBUFFER_VAL_FORMAT_BAYER_GR12PACKED                                                                               \
    (ITKBUFFER_FORMAT(12, 12, 0x2C) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 10 pakced format. */
#define ITKBUFFER_VAL_FORMAT_BAYER_RG12PACKED                                                                               \
    (ITKBUFFER_FORMAT(12, 12, 0x2D) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 10 packed format. */
#define ITKBUFFER_VAL_FORMAT_BAYER_GB12PACKED                                                                               \
    (ITKBUFFER_FORMAT(12, 12, 0x2E) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 10 packed format. */
#define ITKBUFFER_VAL_FORMAT_BAYER_BG12PACKED                                                                               \
    (ITKBUFFER_FORMAT(12, 12, 0x2F) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 10 pakced format. */

// U3V Specific Macros
#define ITKBUFFER_VAL_FORMAT_U3V_MONO10PACKED                                                                               \
    (ITKBUFFER_FORMAT(10, 10, 0x30) | ITKBUFFER_FORMAT_MONO |                                                               \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a monochrome 10 packed format.		    */
#define ITKBUFFER_VAL_FORMAT_U3V_BAYER_GR10PACKED                                                                           \
    (ITKBUFFER_FORMAT(10, 10, 0x31) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 10 pakced format.       */
#define ITKBUFFER_VAL_FORMAT_U3V_BAYER_RG10PACKED                                                                           \
    (ITKBUFFER_FORMAT(10, 10, 0x32) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 10 packed format.       */
#define ITKBUFFER_VAL_FORMAT_U3V_BAYER_GB10PACKED                                                                           \
    (ITKBUFFER_FORMAT(10, 10, 0x33) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 10 packed format.       */
#define ITKBUFFER_VAL_FORMAT_U3V_BAYER_BG10PACKED                                                                           \
    (ITKBUFFER_FORMAT(10, 10, 0x34) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 10 pakced format.       */

#define ITKBUFFER_VAL_FORMAT_BAYER_GR14                                                                                     \
    (ITKBUFFER_FORMAT(14, 16, 0x35) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 14 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_RG14                                                                                     \
    (ITKBUFFER_FORMAT(14, 16, 0x36) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 14 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_GB14                                                                                     \
    (ITKBUFFER_FORMAT(14, 16, 0x37) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 14 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_BG14                                                                                     \
    (ITKBUFFER_FORMAT(14, 16, 0x38) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 14 format.*/

#define ITKBUFFER_VAL_FORMAT_BAYER_GR16                                                                                     \
    (ITKBUFFER_FORMAT(16, 16, 0x39) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GR 16 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_RG16                                                                                     \
    (ITKBUFFER_FORMAT(16, 16, 0x3A) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer RG 16 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_GB16                                                                                     \
    (ITKBUFFER_FORMAT(16, 16, 0x3B) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer GB 16 format.                */
#define ITKBUFFER_VAL_FORMAT_BAYER_BG16                                                                                     \
    (ITKBUFFER_FORMAT(16, 16, 0x3C) | ITKBUFFER_FORMAT_COLOR |                                                              \
     ITKBUFFER_FORMAT_UNSIGNED) /**< \brief Indicates it's a color bayer BG 16 format.*/

// Macros to access bitfield information
#define ITKBUFFER_FORMAT_INDEX(format)       ((format)&0xFF)
#define ITKBUFFER_FORMAT_DATA_BIT(format)    (((format) >> 8) & 0xFF)
#define ITKBUFFER_FORMAT_PIXEL_DEPTH(format) (((format) >> 16) & 0xFF)
#define ITKBUFFER_FORMAT_IS_COLOR(format)    (((format)&ITKBUFFER_FORMAT_COLOR) ? 1 : 0)
#define ITKBUFFER_FORMAT_IS_SIGNED(format)   (((format)&ITKBUFFER_FORMAT_SIGNED) ? 1 : 0)

/* Buffer states */
#define ITKBUFFER_VAL_STATE_EMPTY       0x00000001
#define ITKBUFFER_VAL_STATE_FULL        0x00000002
#define ITKBUFFER_VAL_STATE_OVERFLOW    0x00000004
#define ITKBUFFER_VAL_STATE_UNCOMPLETED 0x00000008

/* Buffer bayer convert alignment options */
#define ITKBUFFER_VAL_BAYER_BGGR 0x00000001
#define ITKBUFFER_VAL_BAYER_RGGB 0x00000002
#define ITKBUFFER_VAL_BAYER_GBRG 0x00000004
#define ITKBUFFER_VAL_BAYER_GRBG 0x00000008

/* Buffer bayer convert method */
#define ITKBUFFER_VAL_BAYER_METHOD_DEFAULT  0x00000000  // Recommended method
#define ITKBUFFER_VAL_BAYER_METHOD_BILINEAR 0x00000010
#define ITKBUFFER_VAL_BAYER_METHOD_VNG      0x00000020
#define ITKBUFFER_VAL_BAYER_METHOD_ITEK_V4  0x00000030

/* Buffer convert option */
#define ITKBUFFER_VAL_CONVERT_OPTION_STRETCH     (1 << 30)
#define ITKBUFFER_VAL_CONVERT_OPTION_AUTO_FORMAT (1 << 31)  // default demosacing and depacked

/* File format in buffer load or save.*/
#define ITKBUFFER_VAL_BMP     0
#define ITKBUFFER_VAL_TIFF    1
#define ITKBUFFER_VAL_RAW     2
#define ITKBUFFER_VAL_JPEG    3  // zmLi 20221103
#define ITKBUFFER_VAL_PNG     4
#define ITKBUFFER_VAL_PCD     5          // Point Cloud Data file format
#define ITKBUFFER_VAL_STRETCH (1 << 30)  // Stretch image before save buffer.

/* The Paylaod type of data in buffer */
#define ITKBUFFER_VAL_IMAGE_PAYLOAD_TYPE                    0
#define ITKBUFFER_VAL_U3V_IMAGE_EXTENDED_CHUNK_PAYLOAD_TYPE 1
#define ITKBUFFER_VAL_U3V_CHUNK_PAYLOAD_TYPE                2
#define ITKBUFFER_VAL_GV_CHUNK_DATA_PAYLOAD_TYPE            3

/****************************************************************************
 *	Stream Parameters
 ****************************************************************************/
#define ITKSTREAM_PRM_FIRST    0
#define ITKSTREAM_PRM(n, size) ((((n) + ITKSTREAM_PRM_FIRST) << 16) | (size))

#define ITKSTREAM_PRM_STATUS             ITKSTREAM_PRM(0, 4) /**< \brief Stream status.                      */
#define ITKSTREAM_PRM_SUPPORT_EVENT_TYPE ITKSTREAM_PRM(1, 4) /**< \brief Stream event type.                  */
#define ITKSTREAM_PRM_START_MODE         ITKSTREAM_PRM(2, 4) /**< \brief Stream start mode.                  */
#define ITKSTREAM_PRM_TRANSFER_MODE      ITKSTREAM_PRM(3, 4) /**< \brief Stream transfer mode.               */
#define ITKSTREAM_PRM_AUTO_CLEAR         ITKSTREAM_PRM(4, 4) /**< \brief Stream auto clear enable.           */
#define ITKSTREAM_PRM_TIME_OUT           ITKSTREAM_PRM(5, 4) /**< \brief Stream time out.                    */
#define ITKSTREAM_PRM_FRAME_RATE         ITKSTREAM_PRM(6, 4) /**< \brief Stream frame rate.                  */
#define ITKSTREAM_PRN_GV_PACKET_MAX_RESEND_COUNT                                                                            \
    ITKSTREAM_PRM(7, 4) /**< \brief GigeVision camera packet max resend times.                  */
#define ITKSTREAM_PRM_GV_PACKET_RESEND_TIMEOUT                                                                              \
    ITKSTREAM_PRM(8, 4) /**< \brief GigeVision camera packet resend timeout.                    */
#define ITKSTREAM_PRM_GV_BLOCK_MAX_RESEND_PACKET_COUNT                                                                      \
    ITKSTREAM_PRM(9, 4) /**< \brief GigeVision camera block max resend packet count.            */
#define ITKSTREAM_PRM_GV_BLOCK_MAX_WAIT_PACKET_COUNT                                                                        \
    ITKSTREAM_PRM(10, 4) /**< \brief GigeVision camera block max wait packet count.              */
#define ITKSTREAM_PRM_GV_BLOCK_RESEND_WINODW_SIZE                                                                           \
    ITKSTREAM_PRM(11, 4) /**< \brief GigeVision camera block resend window size.                 */
#define ITKSTREAM_PRM_GV_PACKET_INTER_TIMEOUT                                                                               \
    ITKSTREAM_PRM(12, 4) /**< \breif GigeVision camera packet inter timeout.                     */
#define ITKSTREAM_PRM_GV_PACKET_POLLING_TIME                                                                                \
    ITKSTREAM_PRM(13, 4) /**< \breif GigeVision camera packet polling time.                      */
#define ITKSTREAM_PRM_GV_KERNEL_BUFFER_COUNT                                                                                \
    ITKSTREAM_PRM(14, 4) /**< \breif GigeVision kernel buffer count.                             */
#define ITKSTREAM_PRM_LINE_RATE ITKSTREAM_PRM(15, 4) /**< \brief Stream line rate.                    */
#define ITKSTREAM_PRM_CURRENT_BUFFER_HANDLE                                                                                 \
    ITKSTREAM_PRM(16, sizeof(ITKBUFFER *)) /**< \brief Stream current buffer handle in end of frame callback. */
#define ITKSTREAM_PRM_BURR_DECTION_IMAGE_SAVE_RATE                                                                          \
    ITKSTREAM_PRM(17, 4) /**< \breif burrDection Image saving rate.                      */
#define ITKSTREAM_PRM_BURR_DECTION_IMAGE_SAVE_PATH                                                                          \
    ITKSTREAM_PRM(18, _MAX_PATH) /**< \breif burrDection Image saving path.                      */
#define ITKSTREAM_PRM_BURR_DECTION_IMAGE_SAVE_BUFFER_COUNT                                                                  \
    ITKSTREAM_PRM(19, 4) /**< \breif burrDection Image saving BufferCount.                      */
#define ITKSTREAM_PRM_BATCH_SIZE ITKSTREAM_PRM(20, 4) /**< \brief Stream batch size.                    */
#define ITKSTREAM_PRM_SELF_ADAPTION                                                                                         \
    ITKSTREAM_PRM(21, 4) /**< \brief Stream prm self adaption 1:enable, 0:disable.               */
#define ITKSTREAM_PRM_FRAME_FRAME_START_CORRESPOND_FRAME_END                                                                \
    ITKSTREAM_PRM(22, 4) /**< \brief frameStart correspond to frameEnd 1:enable, 0:disable.      */

/* Stream status */
#define ITKSTREAM_VAL_STATUS_STOPPED 0x00000000 /**< \brief Stream stop.			*/
#define ITKSTREAM_VAL_STATUS_ACTIVE  0x00000001 /**< \brief Stream in progress.		*/
#define ITKSTREAM_VAL_STATUS_PENDING 0x00000002 /**< \brief Stream is pending.		*/
#define ITKSTREAM_VAL_STATUS_ABORTED 0x00000003 /**< \brief Stream is aborted.		*/
#define ITKSTREAM_VAL_STATUS_TIMEOUT 0x00000004 /**< \brief Stream is time out.		*/

/* Stream support event type */
#define ITKSTREAM_VAL_EVENT_TYPE_START_OF_STREAM                                                                            \
    0x00010000 /**< \brief Call the callback function at the start of stream.			*/
#define ITKSTREAM_VAL_EVENT_TYPE_END_OF_STREAM                                                                              \
    0x00020000 /**< \brief Call the callback function at the end of stream.			*/
#define ITKSTREAM_VAL_EVENT_TYPE_START_OF_FRAME                                                                             \
    0x00040000 /**< \brief Call the callback function at the end of frame.				*/
#define ITKSTREAM_VAL_EVENT_TYPE_END_OF_FRAME                                                                               \
    0x00080000 /**< \brief Call the callback function at the end of frame.				*/
#define ITKSTREAM_VAL_EVENT_TYPE_TIME_OUT                                                                                   \
    0x00100000 /**< \brief Call the callback function at the time out of stream.		*/
#define ITKSTREAM_VAL_EVENT_TYPE_FRAME_LOST                                                                                 \
    0x00200000 /**< \brief Call the callback function at the frame lost.				*/
#define ITKSTREAM_VAL_EVENT_TYPE_IMAGE_DATA_ERROR                                                                           \
    0x00400000 /**< \brief Call the callback function at the frame lost.				*/
#define ITKSTREAM_VAL_EVENT_TYPE_END_OF_LINE                                                                                \
    0x01000000 /**< \brief Call the callback function at the end of line.				*/
#define ITKSTREAM_VAL_EVENT_TYPE_END_OF_BATCH                                                                               \
    0x02000000 /**< \brief Call the callback function at the end of batch.				*/

#define ITKSTREAM_VAL_EVENT_TYPE_MASK 0xffff0000

/* Stream start mode */
#define ITKSTREAM_VAL_START_MODE_NON_BLOCK 0x00000000 /**< \brief Stream start in asynchronous mode.					*/
#define ITKSTREAM_VAL_START_MODE_BLOCK     0x00000001 /**< \brief Stream start in synchronous mode.					*/

/* Stream transfer mode */
#define ITKSTREAM_VAL_TRANSFER_MODE_ASYNCHRONOUS                                                                            \
    0x00000000                                             /**< \brief Stream transfer in asynchronous mode.				*/
#define ITKSTREAM_VAL_TRANSFER_MODE_SYNCHRONOUS 0x00000001 /**< \brief Stream transfer in synchronous mode.				*/
#define ITKSTREAM_VAL_TRANSFER_MODE_SYNCHRONOUS_WITH_PROTECT                                                                \
    0x00000002 /**< \brief Stream transfer in synchronous with protect mode.	*/

/* Stream auto clear */
#define ITKSTREAM_VAL_AUTO_CLEAR_DISABLE 0x00000000 /**< \brief  Disable stream auto clear.							*/
#define ITKSTREAM_VAL_AUTO_CLEAR_ENABLE  0x00000001 /**< \brief  Enable stream auto clear.							*/

// To start continuous stream
#define ITKSTREAM_CONTINUOUS ((uint32_t)-1) /**< \brief Stream work in continuous mode.						*/

/****************************************************************************
 *	View Parameters
 ****************************************************************************/
#define ITKVIEW_PRM_FIRST    0
#define ITKVIEW_PRM(n, size) ((((n) + ITKVIEW_PRM_FIRST) << 16) | (size))

#define ITKVIEW_PRM_FILP_X                                                                                                  \
    ITKVIEW_PRM(0, 4) /**< \brief Enable/disable X axis vertical flipping of the source image while the view is displayed.  \
                       */
#define ITKVIEW_PRM_FILP_Y                                                                                                  \
    ITKVIEW_PRM(1, 4) /**< \brief Enable/disable Y axis horizontal flipping of the source image while the view is           \
                         displayed.					*/
#define ITKVIEW_PRM_LSB ITKVIEW_PRM(2, 4) /**< \brief Source image least significant bit. 				*/
#define ITKVIEW_PRM_MSB ITKVIEW_PRM(3, 4) /**< \brief Source image most significant bit. 					*/
#define ITKVIEW_PRM_BUFFER_ROI_HEIGHT                                                                                       \
    ITKVIEW_PRM(4, 4) /**< \brief Height of the ROI of the buffer associated with the view.	 */
#define ITKVIEW_PRM_BUFFER_ROI_WIDTH                                                                                        \
    ITKVIEW_PRM(5, 4) /**< \brief Width of the ROI of the buffer associated with the view.	 */
#define ITKVIEW_PRM_BUFFER_ROI_LEFT                                                                                         \
    ITKVIEW_PRM(6, 4) /**< \brief Left of the ROI of the buffer associated with the view.	 */
#define ITKVIEW_PRM_BUFFER_ROI_TOP                                                                                          \
    ITKVIEW_PRM(7, 4)                                 /**< \brief Top of the ROI of the buffer associated with the view.	 */
#define ITKVIEW_PRM_ZOOM_METHOD    ITKVIEW_PRM(8, 4)  /**< \brief	Sets/Gets the zooming method.							*/
#define ITKVIEW_PRM_ZOOM_MAX_RATIO ITKVIEW_PRM(9, 8)  /**< \brief	Sets/Gets the zooming maximum ratio.  */
#define ITKVIEW_PRM_ZOOM_MIN_RATIO ITKVIEW_PRM(10, 8) /**< \brief	Sets/Gets the zooming minimum ratio. */
#define ITKVIEW_PRM_HWND                                                                                                    \
    ITKVIEW_PRM(11, sizeof(void *)) /**< \brief	Window handle to be used as the destination view display surface.           \
                                     */
#define ITKVIEW_PRM_HWND_TITLE                                                                                              \
    ITKVIEW_PRM(12, 128) /**< \brief	Window title to be used as the destination view display surface.			*/
#define ITKVIEW_PRM_BAYER_MODE           ITKVIEW_PRM(13, 4) /**< \brief	Show bayer image in windows.					*/
#define ITKVIEW_PRM_BUFFER_CURRENT_INDEX ITKVIEW_PRM(14, 4) /**< \brief	Show Buffer Current Index					*/

/* View flip x */
#define ITKVIEW_VAL_FLIP_X_DISABLE 0x00000000
#define ITKVIEW_VAL_FLIP_X_ENABLE  0x00000001

/* View flip y */
#define ITKVIEW_VAL_FLIP_Y_DISABLE 0x00000000
#define ITKVIEW_VAL_FLIP_Y_ENABLE  0x00000001

/* View zoom method */
#define ITKVIEW_VAL_ZOOM_NN     0x00000000 /**< \brief	Nearest neighbor zoom method.				*/
#define ITKVIEW_VAL_ZOOM_LINEAR 0x00000001 /**< \brief	Linear zoom method.							*/
#define ITKVIEW_VAL_ZOOM_CUBIC  0x00000002 /**< \brief	Linear zoom method.							*/
#define ITKVIEW_VAL_ZOOM_AREA   0x00000003 /**< \brief	Area zoom method.							*/

/* Bayer Mode */
#define ITKVIEW_VAL_BAYER_MODE_NIL  0x00000000 /**< \brief	Bayer Mode NIL.								*/
#define ITKVIEW_VAL_BAYER_MODE_BGGR 0x00000001 /**< \brief	Bayer Mode BGGR.							*/
#define ITKVIEW_VAL_BAYER_MODE_RGGB 0x00000002 /**< \brief	Bayer Mode RGGB.							*/
#define ITKVIEW_VAL_BAYER_MODE_GBRG 0x00000003 /**< \brief	Bayer Mode GBRG.							*/
#define ITKVIEW_VAL_BAYER_MODE_GRBG 0x00000004 /**< \brief	Bayer Mode GRBG.							*/

/****************************************************************************
 *    File Parameters
 ****************************************************************************/

/* File access mode and open method flags (3rd argument of ItkFileOpen) */
#define ITKFILE_VAL_FA_READ          0x01
#define ITKFILE_VAL_FA_WRITE         0x02
#define ITKFILE_VAL_FA_OPEN_EXISTING 0x00
#define ITKFILE_VAL_FA_CREATE_NEW    0x04
#define ITKFILE_VAL_FA_CREATE_ALWAYS 0x08
#define ITKFILE_VAL_FA_OPEN_ALWAYS   0x10
#define ITKFILE_VAL_FA_OPEN_APPEND   0x30

/* File attribute bits for directory entry (FILINFO.fattrib) */
#define ITKFILE_VAL_AM_RDO 0x01 /* Read only */
#define ITKFILE_VAL_AM_HID 0x02 /* Hidden */
#define ITKFILE_VAL_AM_SYS 0x04 /* System */
#define ITKFILE_VAL_AM_DIR 0x10 /* Directory */
#define ITKFILE_VAL_AM_ARC 0x20 /* Archive */

/*Deprecated*/
#define ITKBUFFER_FORMATL_DATA_BIT(format) (((format) >> 8) & 0xFF)

#endif
