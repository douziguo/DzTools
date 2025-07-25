/**
\~chinese
 * @file IKapBoardInfoType.h
 * @brief IKapBoard库相关定义
 * @author 合肥埃科光电科技股份有限公司
 * @copyright 版权所有 (c) 合肥埃科光电科技股份有限公司
 * @date 2018-12-04
 * @version 2.4.1.0
\~english
 * @file IKapBoardInfoType.h
 * @brief IKapBoard library related definition
 * @author Hefei I-TEK Optoelectronics Co., LTD.
 * @copyright Copyright (c) Hefei I-TEK Optoelectronics Co., LTD.
 * @date 2018-12-04
 * @version 2.4.1.0
 */
#pragma once
///@{
/**
\~chinese
 * @name 采集卡参数
\~english
 * @name Frame grabber parameters
 */

/**
\~chinese
 * @brief 图像宽度
 * @note 本参数表示采集卡图像宽度【RW】。
 *       <br> 1. 如果采集卡设置的图像宽度大于相机输出图像的实际有效宽度，则无法正常采集。
 *       <br> 2. 对于面扫描相机，一帧图像占据的内存大小不能超过IKP_INTERNAL_BUFFER_SIZE指定的大小。
 *       <br> 3. 图像宽度最大值由相机型号决定，用户可以通过查阅相机使用手册获得相关信息。
 *       <br> 4. 用户设置图像宽度时应遵循如下原则:
 * <table>
 * <tr><th>Tap数  <th>图像宽度
 * <tr><td>1Tap   <td>1~最大值（1的整数倍）
 * <tr><td>2Tap   <td>2~最大值（2的整数倍）
 * <tr><td>3Tap   <td>3~最大值（3的整数倍）
 * <tr><td>4Tap   <td>4~最大值（4的整数倍）
 * <tr><td>8Tap   <td>8~最大值（8的整数倍）
 * <tr><td>10Tap  <td>10~最大值（10的整数倍）
 * </table>
\~english
 * @brief Image width
 * @note This parameter represents the image width of frame grabber [RW].
 *       <br> 1. If image width set by frame grabber is greater than the actual effective width of camera output image,
normal acquisition cannot be performed.
 *       <br> 2. For area scan cameras, the memory size occupied by one frame of image cannot exceed the size specified by
IKP_INTERNAL_BUFFER_SIZE.
 *       <br> 3. The maximum image width is determined by camera model, and users can obtain relevant information by
referring to camera manual.
 *       <br> 4. Users should follow the following principles when setting image width:
 * <table>
 * <tr><th>Tap number  <th>Image width
 * <tr><td>1Tap        <td>1~Maximum（integer multiple of 1）
 * <tr><td>2Tap        <td>2~Maximum（integer multiple of 2）
 * <tr><td>3Tap        <td>3~Maximum（integer multiple of 3）
 * <tr><td>4Tap        <td>4~Maximum（integer multiple of 4）
 * <tr><td>8Tap        <td>8~Maximum（integer multiple of 8）
 * <tr><td>10Tap       <td>10~Maximum（integer multiple of 10）
 * </table>
 */
#define IKP_IMAGE_WIDTH (0x10000001)

/**
\~chinese
 * @brief 图像高度
 * @note 本参数表示采集卡图像高度【RW】。
 *       <br> 1. 图像高度最大值由相机型号决定，用户可以通过查阅相机使用手册获得相关信息。
 *       <br> 2.
对于面扫描相机，本参数表示图像高度，其最大值由相机前端传感器决定。单帧图像尺寸IKP_FRAME_SIZE不能超过IKP_INTERNAL_BUFFER_SIZE指定的大小，否则无法正常采集。
 *       <br> 3.
对于线扫描相机，本参数表示采集卡每帧采集的图像行数，最大值为2147483647。当指定行数的图像采集完成后，会触发一次IKEvent_FrameReady事件。
\~english
 * @brief Image height
 * @note This parameter represents the image height of frame grabber [RW].
 *       <br> 1. The maximum image height is determined by camera model, and users can obtain relevant information by
referring to camera manual.
 *       <br> 2. For area scan cameras, this parameter represents the image height, and its maximum value is determined by
the front-end sensor of camera. The size of a single frame image IKP_FRAME_SIZE cannot exceed the size specified by
IKP_INTERNAL_BUFFER_SIZE, otherwise normal acquisition cannot be performed.
 *       <br> 3. For line scan cameras, this parameter represents the number of image lines grabbed by frame grabber per
frame, with a maximum value of 2147483647. After the specified number of lines of image acquisition is completed, an
IKEvent_FrameReady event will be triggered.
 */
#define IKP_IMAGE_HEIGHT (0x10000002)

/**
\~chinese
 * @brief 图像数据格式
 * @note 本参数表示图像数据格式，即相机产生图像时的有效位宽【RW】。
 *       <br> 1. 采集卡图像数据格式与相机图像数据格式需保持一致，否则无法正常采集。
\~english
 * @brief Image data format
 * @note This parameter represents image data format, which is effective bit width when camera generates an image [RW].
 *       <br> 1. The image data format of frame grabber needs to be consistent with camera image data format, otherwise
normal acquisition cannot be performed.
 */
#define IKP_DATA_FORMAT (0x10000003)

/**
\~chinese
 * @brief 图像位宽
 * @note 本参数表示图像位宽，即单个像素在PC内存中占据的位宽【RO】。
 *       <br> 1. 本参数不支持手动设定，由图像数据格式和图像类型计算得到，对应关系如下:
 * <table>
 * <tr><th>图像数据格式  <th>图像类型  <th>图像位宽
 * <tr><td>8             <td>0         <td>8
 * <tr><td>10/12/14/16   <td>0         <td>16
 * <tr><td>8             <td>1         <td>24
 * <tr><td>10/12/14/16   <td>1         <td>48
 * <tr><td>8             <td>2         <td>32
 * <tr><td>10/12/14/16   <td>2         <td>64
 * <tr><td>8             <td>3         <td>24
 * <tr><td>10/12/14/16   <td>3         <td>48
 * <tr><td>8             <td>4         <td>32
 * <tr><td>10/12/14/16   <td>4         <td>64
 * </table>
\~english
 * @brief Image bit width
 * @note This parameter represents image bit width, which is the bit width occupied by a single pixel in PC memory [RO].
 *       <br> 1. This parameter does not support manual setting and is calculated based on image data format and image type.
The corresponding relationship is as follows:
 * <table>
 * <tr><th>Image data format  <th>Image type  <th>Image bit width
 * <tr><td>8                  <td>0           <td>8
 * <tr><td>10/12/14/16        <td>0           <td>16
 * <tr><td>8                  <td>1           <td>24
 * <tr><td>10/12/14/16        <td>1           <td>48
 * <tr><td>8                  <td>2           <td>32
 * <tr><td>10/12/14/16        <td>2           <td>64
 * <tr><td>8                  <td>3           <td>24
 * <tr><td>10/12/14/16        <td>3           <td>48
 * <tr><td>8                  <td>4           <td>32
 * <tr><td>10/12/14/16        <td>4           <td>64
 * </table>
 */
#define IKP_BOARD_BIT (0x10000004)

/**
\~chinese
 * @brief 超时时间（ms）
 * @note 对单帧采集，本参数表示单次采集等待的超时时间；对于连续采集，本参数表示两帧间隔的最大等待时间【RW】。
 *       <br> 1. 对于较大尺寸的图像，可能需要较长的时间完成一次图像采集，可以通过增长采集时间保证一帧完整图像的采集。
\~english
 * @brief Timeout time（ms）
 * @note For single frame acquisition, this parameter represents timeout time for waiting for a single acquisition. For
continuous acquisition, this parameter represents the maximum waiting time between two frames [RW].
 *       <br> 1. For large size images, it may take a long time to complete an image acquisition. Increasing acquisition time
can ensure the acquisition of a complete frame of image.
 */
#define IKP_TIME_OUT (0x10000005)

/**
\~chinese
 * @brief 相机扫描类型
 * @note 本参数表示相机扫描类型【RW】。
\~english
 * @brief Camera scan type
 * @note This parameter represents camera scan type [RW].
 */
#define IKP_SCAN_TYPE (0x10000006)

/**
\~chinese
 * @brief 采集卡固件版本
 * @note 本参数表示采集卡固件版本号【RO】。
\~english
 * @brief Frame grabber firmware version
 * @note This parameter represents firmware version of frame grabber [RO].
 */
#define IKP_FPGA_VERSION (0x10000007)

/**
\~chinese
 * @brief 系统预留缓冲区大小
 * @note 本参数表示系统预留的图像缓存区域大小，有效值32/64/128MB【RO】。
 *       <br> 1. 对于面扫描相机，单帧图像大小不能超过该参数，否则无法正常采集图像。
\~english
 * @brief System reserved buffer size
 * @note This parameter represents the size of image buffer reserved by system, with a valid value of 32/64/128MB [RO].
 *       <br> 1. For area scan cameras, the size of a single frame image cannot exceed this parameter, otherwise normal
acquisition cannot be performed.
 */
#define IKP_INTERNEL_BUFFER_SIZE (0x10000008)

/**
\~chinese
 * @brief 每帧图像大小
 * @note 本参数表示每帧图像在缓存区中的大小【RO】。
 *       <br> 1. 图像有效缓存区域大小计算方式: IKP_FRAME_SIZE = (IKP_IMAGE_WIDTH*IKP_IMAGE_HEIGHT*IKP_BOARD_BIT/8)（单位:
字节）
\~english
 * @brief Size of each frame image
 * @note This parameter represents the size of each frame image in buffer [RO].
 *       <br> 1. The calculation method for effective image buffer size is: IKP_FRAME_SIZE =
(IKP_IMAGE_WIDTH*IKP_IMAGE_HEIGHT*IKP_BOARD_BIT/8)（in bytes）
 */
#define IKP_FRAME_SIZE (0x10000009)

/**
\~chinese
 * @brief 图像类型
 * @note 本参数表示图像类型【RW】。
 *       <br> 1. 一帧图像占据的内存大小不能超过IKP_INTERNAL_BUFFER_SIZE指定的大小。
 *       <br> 2. 采集卡图像类型与相机图像类型需保持一致，否则无法正常采集图像。
\~english
 * @brief Image type
 * @note This parameter represents image type [RW].
 *       <br> 1. The memory size occupied by one frame of image cannot exceed the size specified by IKP_INTERNAL_BUFFER_SIZE.
 *       <br> 2. The image type of frame grabber must be consistent with that of camera, otherwise  normal acquisition cannot
be performed.
 */
#define IKP_IMAGE_TYPE (0x1000000a)

/**
\~chinese
 * @brief 图像缓冲区帧数
 * @note 本参数表示图像缓冲区帧数【RW】。
 *       <br> 1. 当用户设置该参数时，IKapBoard自动申请/管理图像缓冲区，用户无需释放该段内存缓冲区域。
 *       <br> 2. 请在设置该参数前先设置图像宽度、图像高度和图像数据格式，否则可能出现参数冲突导致采集失败。
 *       <br> 3.
用户应该校验设置缓冲区帧数的返回值，如果当前系统资源不足，就无法申请到足够的内存数据，采集卡无法开始采集工作。此时用户应该减少缓冲区帧数或减小和图像尺寸的相关参数来保证内存申请的成功。
 *       <br> 4. 请不要在连续采集的过程中设置该参数，否则可能导致采集失败。
\~english
 * @brief Number of image buffer
 * @note This parameter represents the number of image buffer [RW].
 *       <br> 1. When users set this parameter, IKapBoard automatically requests/manages image buffer, and users do not need
to release this memory buffer.
 *       <br> 2. Please set image width, image height, and image data format before setting this parameter, otherwise
parameter conflicts may occur leading to acquisition failure.
 *       <br> 3. Users should verify the return value of setting buffer number. If the current system resources are
insufficient, sufficient memory data cannot be requested and the frame grabber cannot start the acquisition work. At this
point, users should reduce the number of buffer frames or decrease the parameters related to image size to ensure the success
of memory requests.
 *       <br> 4. Please do not set this parameter during continuous acquisition, otherwise it may cause acquisition failure.
 */
#define IKP_FRAME_COUNT (0x1000000b)

/**
\~chinese
 * @brief 图像缓冲区传输模式
 * @note 本参数表示图像缓冲区传输模式【RW】。
\~english
 * @brief Image buffer transfer mode
 * @note This parameter represents image buffer transfer mode [RW].
 */
#define IKP_FRAME_TRANSFER_MODE (0x1000000c)

/**
\~chinese
 * @brief 图像缓冲区自动清空机制
 * @note 本参数表示图像缓冲区自动清空机制【RW】。
 *       <br> 1.
IKapBoard默认在IKEvent_FrameReady回调事件执行后自动清空缓冲区。当缓冲区为空时，新的图像数据可以写入该缓冲区内。因此当用户未及时取走缓冲区数据时，旧的图像数据将会被覆盖。
 *       <br> 2.
为了确保图像的正确性，用户可以禁用自动清除机制并且选择缓冲区传输模式为同步保护传输模式，此时新的图像数据将不会覆盖原有数据，直到缓冲区变为空。
 *       <br> 3. 在禁用自动清除机制时，用户需要在使用完缓冲区后调用IKapReleaseBuffer来释放缓冲区。
 *       <br> 4. 缓存自动清空机制仅适用于连续采集过程。
\~english
 * @brief Image buffer automatic clearing mechanism
 * @note This parameter represents image buffer automatic clearing mechanism [RW].
 *       <br> 1. IKapBoard defaults to automatically clear buffer after IKEvent_FrameReady callback event is executed. When
buffer is empty, new image data can be written into it. Therefore, when users fail to retrieve the buffer data in a timely
manner, old image data will be overwritten.
 *       <br> 2. To ensure the correctness of image, users can disable automatic clearing mechanism and select buffer
transfer mode as synchronous protection transfer mode. At this time, new image data will not overwrite the original data
until the buffer becomes empty.
 *       <br> 3. When automatic clearing mechanism is disabled, users need to call IKapReleaseBuffer to release buffer after
using.
 *       <br> 4. The automatic clearing mechanism is only applicable to continuous acquisition process.
 */
#define IKP_FRAME_AUTO_CLEAR (0x1000000d)

/**
\~chinese
 * @brief 图像序列采集模式
 * @note 本参数表示图像序列采集模式，可以是阻塞或者非阻塞式调用【RW】。
\~english
 * @brief Image sequence acquisition mode
 * @note This parameter represents image sequence acquisition mode, which can be a blocking or non blocking mode [RW].
 */
#define IKP_GRAB_MODE (0x1000000e)

/**
\~chinese
 * @brief 上帧图像采集完成时间戳的低字节
 * @note 本参数表示上帧图像采集完成时间戳的低字节，时间戳信息占据64bit【RO】。
\~english
 * @brief Low bytes of timestamp of last frame
 * @note This parameter represents low bytes of timestamp of last frame, and the timestamp information occupies 64 bits [RO].
 */
#define IKP_FRAME_TIME_STAMP_LOW (0x1000000f)

/**
\~chinese
 * @brief 上帧图像采集完成时间戳的高字节
 * @note 本参数表示上帧图像采集完成时间戳的高字节，时间戳信息占据64bit【RO】。
\~english
 * @brief High bytes of timestamp of last frame
 * @note This parameter represents high bytes of timestamp of last frame, and the timestamp information occupies 64 bits
[RO].
 */
#define IKP_FRAME_TIME_STAMP_HIGH (0x10000010)

/**
\~chinese
 * @brief 图像单元采集完成时间戳的低字节
 * @note 本参数表示图像单元采集完成时间戳的低字节，时间戳信息占据64bit【RO】。
\~english
 * @brief Low bytes of timestamp of image block
 * @note This parameter represents low bytes of timestamp of image block, and the timestamp information occupies 64 bits
[RO].
 */
#define IKP_BLOCK_TIME_STAMP_LOW (0x10000011)

/**
\~chinese
 * @brief 图像单元采集完成时间戳的高字节
 * @note 本参数表示图像单元采集完成时间戳的高字节，时间戳信息占据64bit【RO】。
\~english
 * @brief High bytes of timestamp of image block
 * @note This parameter represents high bytes of timestamp of image block, and the timestamp information occupies 64 bits
[RO].
 */
#define IKP_BLOCK_TIME_STAMP_HIGH (0x10000012)

/**
\~chinese
 * @brief 相机Tap个数
 * @note 本参数表示相机Tap个数，设置该参数时请参考对应相机使用手册【RW】。
\~english
 * @brief Number of camera taps
 * @note This parameter represents the number of camera taps. Please refer to the corresponding camera manual when setting
this parameter [RW].
 */
#define IKP_TAP_NUMBER (0x10000013)

/**
\~chinese
 * @brief Tap排列方式
 * @note 本参数表示相机Tap排列方式。在不同的Tap个数下，该参数表示的图像排列方式会有所不同【RW】。
\~english
 * @brief Tap arrangement method
 * @note This parameter represents tap arrangement method. The image arrangement represented by this parameter will vary
depending on the number of taps [RW].
 */
#define IKP_TAP_ARRANGEMENT (0x10000014)

/**
\~chinese
 * @brief Bayer图像解析模式
 * @note 本参数表示Bayer图像解析模式【RW】。
\~english
 * @brief Bayer image pattern
 * @note This parameter represents Bayer image pattern [RW].
 */
#define IKP_BAYER_PATTERN (0x10000015)

/**
\~chinese
 * @brief CL采集卡像素时钟【已弃用】
 * @note 本参数表示CL采集卡像素时钟【RW】。
\~english
 * @brief CL frame grabber pixel clock [abandoned]
 * @note This parameter represents CL frame grabber pixel clock [RW].
 */
#define IKP_PIXEL_CLOCK (0x10000016)

/**
\~chinese
 * @brief CL采集卡数据使能【已弃用】
 * @note 本参数表示CL采集卡数据有效使能标志位【RW】。
\~english
 * @brief CL frame grabber data enable [abandoned]
 * @note This parameter represents valid enable flag for CL frame grabber data [RW].
 */
#define IKP_DATA_VALID_ENABLE (0x10000017)

/**
\~chinese
 * @brief CL采集卡CC1信号源
 * @note 本参数表示CL采集卡CC1信号源【RW】。
\~english
 * @brief CL frame grabber CC1 signal source
 * @note This parameter represents CL frame grabber CC1 signal source [RW].
 */
#define IKP_CC1_SOURCE (0x10000018)

/**
\~chinese
 * @brief CL采集卡CC2信号源
 * @note 本参数表示CL采集卡CC2信号源【RW】。
\~english
 * @brief CL frame grabber CC2 signal source
 * @note This parameter represents CL frame grabber CC2 signal source [RW].
 */
#define IKP_CC2_SOURCE (0x10000019)

/**
\~chinese
 * @brief CL采集卡CC3信号源
 * @note 本参数表示CL采集卡CC3信号源【RW】。
\~english
 * @brief CL frame grabber CC3 signal source
 * @note This parameter represents CL frame grabber CC3 signal source [RW].
 */
#define IKP_CC3_SOURCE (0x1000001a)

/**
\~chinese
 * @brief CL采集卡CC4信号源
 * @note 本参数表示CL采集卡CC4信号源【RW】。
\~english
 * @brief CL frame grabber CC4 signal source
 * @note This parameter represents CL frame grabber CC4 signal source [RW].
 */
#define IKP_CC4_SOURCE (0x1000001b)

/**
\~chinese
 * @brief 采集卡触发模式
 * @note 本参数表示采集卡外触发采集图像的信号触发模式【RW】。
\~english
 * @brief Frame grabber trigger mode
 * @note This parameter represents signal trigger mode for frame grabber external trigger acquisition [RW].
 */
#define IKP_BOARD_TRIGGER_MODE (0x1000001c)

/**
\~chinese
 * @brief 采集卡触发信号源
 * @note 本参数表示采集卡外触发时的触发信号源，只有当采集卡触发模式设置为外触发时本参数才有效【RW】。
\~english
 * @brief Frame grabber trigger signal source
 * @note This parameter represents trigger signal source when frame grabber is triggered externally. This parameter is only
valid when frame grabber trigger mode is set to external trigger [RW].
 */
#define IKP_BOARD_TRIGGER_SOURCE (0x1000001d)

/**
\~chinese
 * @brief CL采集卡通用输入信号1采样模式【已弃用】
 * @note 本参数表示CL采集卡通用输入信号1采样模式【RW】。
\~english
 * @brief CL frame grabber general input signal1 sampling mode [abandoned]
 * @note This parameter represents general input signal1 sampling mode of CL frame grabber [RW].
 */
#define IKP_GENERAL_INPUT1_SAMPLE_MODE (0x1000001e)

/**
\~chinese
 * @brief CL采集卡通用输入信号1脉冲保护模式【已弃用】
 * @note 本参数表示CL采集卡通用输入信号1脉冲保护模式【RW】。
\~english
 * @brief CL frame grabber general input signal1 pulse protection mode [abandoned]
 * @note This parameter represents general input signal1 pulse protection mode of CL frame grabber [RW].
 */
#define IKP_GENERAL_INPUT1_PROTECT_MODE (0x1000001f)

/**
\~chinese
 * @brief CL采集卡通用输入信号1最小脉冲间隔【已弃用】
 * @note 本参数表示CL采集卡通用输入信号1最小脉冲间隔【RW】。
\~english
 * @brief CL frame grabber general input signal1 minimum pulse interval [abandoned]
 * @note This parameter represents the minimum pulse interval for general input signal1 of CL frame grabber [RW].
 */
#define IKP_GENERAL_INPUT1_MINIMUM_INTERVAL (0x10000020)

/**
\~chinese
 * @brief CL采集卡通用输入信号2采样模式【已弃用】
 * @note 本参数表示CL采集卡通用输入信号2采样模式【RW】。
\~english
 * @brief CL frame grabber general input signal2 sampling mode [abandoned]
 * @note This parameter represents general input signal2 sampling mode of CL frame grabber [RW].
 */
#define IKP_GENERAL_INPUT2_SAMPLE_MODE (0x10000021)

/**
\~chinese
 * @brief CL采集卡通用输入信号2脉冲保护模式【已弃用】
 * @note 本参数表示CL采集卡通用输入信号2脉冲保护模式【RW】。
\~english
 * @brief CL frame grabber general input signal2 pulse protection mode [abandoned]
 * @note This parameter represents general input signal2 pulse protection mode of CL frame grabber [RW].
 */
#define IKP_GENERAL_INPUT2_PROTECT_MODE (0x10000022)

/**
\~chinese
 * @brief CL采集卡通用输入信号2最小脉冲间隔【已弃用】
 * @note 本参数表示CL采集卡通用输入信号2最小脉冲间隔【RW】。
\~english
 * @brief CL frame grabber general input signal2 minimum pulse interval [abandoned]
 * @note This parameter represents the minimum pulse interval for general input signal2 of CL frame grabber [RW].
 */
#define IKP_GENERAL_INPUT2_MINIMUM_INTERVAL (0x10000023)

/**
\~chinese
 * @brief 编码器信号分频系数
 * @note 本参数表示编码器信号分频系数【RW】。
\~english
 * @brief Encoder signal division factor
 * @note This parameter represents encoder signal division factor [RW].
 */
#define IKP_SHAFT_ENCODER1_PULSE_DROP (0x10000024)

/**
\~chinese
 * @brief CL采集卡编码器脉冲保护模式【已弃用】
 * @note 本参数表示CL采集卡编码器脉冲保护模式【RW】。
\~english
 * @brief CL frame grabber encoder pulse protection mode [abandoned]
 * @note This parameter represents CL frame grabber encoder pulse protection mode [RW].
 */
#define IKP_SHAFT_ENCODER1_PROTECT_MODE (0x10000025)

/**
\~chinese
 * @brief CL采集卡编码器最小脉冲间隔【已弃用】
 * @note 本参数表示CL采集卡编码器最小脉冲间隔【RW】。
\~english
 * @brief CL frame grabber encoder minimum pulse interval [abandoned]
 * @note This parameter represents the minimum pulse interval of CL frame grabber encoder [RW].
 */
#define IKP_SHAFT_ENCODER1_MINIMUM_INTERVAL (0x10000026)

/**
\~chinese
 * @brief 积分控制方法触发信号源
 * @note 本参数表示积分控制方法触发信号源【RW】。
\~english
 * @brief Integration control method trigger signal source
 * @note This parameter represents trigger signal source for integration control method [RW].
 */
#define IKP_INTEGRATION_TRIGGER_SOURCE (0x10000027)

/**
\~chinese
 * @brief 积分控制方法触发信号频率
 * @note 本参数表示积分控制方法触发信号频率【RW】。
 *       <br> 1. 当积分控制方法触发信号源设置为采集卡内部触发时，本参数表示内部触发信号频率。
\~english
 * @brief Integration control method trigger signal frequency
 * @note This parameter represents trigger signal frequency of integration control method [RW].
 *       <br> 1. When trigger signal source of integration control method is set to internal trigger of frame grabber, this
parameter represents the frequency of internal trigger signal.
 */
#define IKP_INTEGRATION_TRIGGER_FREQUENCY (0x10000028)

/**
\~chinese
 * @brief 闪光触发信号源
 * @note 本参数表示闪光触发信号源【RW】。
\~english
 * @brief Strobe trigger signal source
 * @note This parameter represents strobe trigger signal source [RW].
 */
#define IKP_STROBE_TRIGGER_SOURCE (0x10000029)

/**
\~chinese
 * @brief CL采集卡板间同步输出1信号源
 * @note 本参数表示CL采集卡板间同步输出1信号源【RW】。
\~english
 * @brief CL frame grabber board synchronous output1 signal source
 * @note This parameter represents synchronous output1 signal source between CL frame grabber [RW].
 */
#define IKP_BOARD_SYNC_OUTPUT1_SOURCE (0x1000002a)

/**
\~chinese
 * @brief CL采集卡板间同步输出2信号源
 * @note 本参数表示CL采集卡板间同步输出2信号源【RW】。
\~english
 * @brief CL frame grabber board synchronous output2 signal source
 * @note This parameter represents synchronous output2 signal source between CL frame grabber [RW].
 */
#define IKP_BOARD_SYNC_OUTPUT2_SOURCE (0x1000002b)

/**
\~chinese
 * @brief 通用输出信号1信号源
 * @note 本参数表示通用输出信号1信号源【RW】。
\~english
 * @brief General output1 signal source
 * @note This parameter represents general output1 signal source [RW].
 */
#define IKP_GENERAL_OUTPUT1_SOURCE (0x1000002c)

/**
\~chinese
 * @brief 通用输出信号2信号源
 * @note 本参数表示通用输出信号2信号源【RW】。
\~english
 * @brief General output2 signal source
 * @note This parameter represents general output2 signal source [RW].
 */
#define IKP_GENERAL_OUTPUT2_SOURCE (0x1000002d)

/**
\~chinese
 * @brief 积分控制方法索引
 * @note 本参数表示积分控制方法索引【RW】。
\~english
 * @brief Index of integration control methods
 * @note This parameter represents the index of integration control method [RW].
 */
#define IKP_INTEGRATION_METHOD (0x1000002e)

/**
\~chinese
 * @brief 积分控制方法参数1
 * @note 本参数表示积分控制方法参数1【RW】。
\~english
 * @brief Integration control method parameter1
 * @note This parameter represents integration control method parameter1 [RW].
 */
#define IKP_INTEGRATION_PARAM1 (0x1000002f)

/**
\~chinese
 * @brief 积分控制方法参数2
 * @note 本参数表示积分控制方法参数2【RW】。
\~english
 * @brief Integration control method parameter2
 * @note This parameter represents integration control method parameter2 [RW].
 */
#define IKP_INTEGRATION_PARAM2 (0x10000030)

/**
\~chinese
 * @brief 积分控制方法参数3
 * @note 本参数表示积分控制方法参数3【RW】。
\~english
 * @brief Integration control method parameter3
 * @note This parameter represents integration control method parameter3 [RW].
 */
#define IKP_INTEGRATION_PARAM3 (0x10000031)

/**
\~chinese
 * @brief 积分控制方法参数4
 * @note 本参数表示积分控制方法参数4【RW】。
\~english
 * @brief Integration control method parameter4
 * @note This parameter represents integration control method parameter4 [RW].
 */
#define IKP_INTEGRATION_PARAM4 (0x10000032)

/**
\~chinese
 * @brief 积分信号1极性
 * @note 本参数表示积分信号1极性【RW】。
\~english
 * @brief Polarity of integration signal1
 * @note This parameter represents polarity of integration signal1 [RW].
 */
#define IKP_INTEGRATION_POLARITY1 (0x10000033)

/**
\~chinese
 * @brief 积分信号2极性
 * @note 本参数表示积分信号2极性【RW】。
\~english
 * @brief Polarity of integration signal2
 * @note This parameter represents polarity of integration signal2 [RW].
 */
#define IKP_INTEGRATION_POLARITY2 (0x10000034)

/**
\~chinese
 * @brief 闪光控制方法索引
 * @note 本参数表示闪光控制方法索引【RW】。
\~english
 * @brief Index of strobe control methods
 * @note This parameter represents the index of strobe control method [RW].
 */
#define IKP_STROBE_METHOD (0x10000035)

/**
\~chinese
 * @brief 闪光控制方法参数1
 * @note 本参数表示闪光控制方法参数1【RW】。
\~english
 * @brief Strobe control method parameter1
 * @note This parameter represents strobe control method parameter1 [RW].
 */
#define IKP_STROBE_PARAM1 (0x10000036)

/**
\~chinese
 * @brief 闪光控制方法参数2
 * @note 本参数表示闪光控制方法参数2【RW】。
\~english
 * @brief Strobe control method parameter2
 * @note This parameter represents strobe control method parameter2 [RW].
 */
#define IKP_STROBE_PARAM2 (0x10000037)

/**
\~chinese
 * @brief 闪光控制方法参数3
 * @note 本参数表示闪光控制方法参数3【RW】。
\~english
 * @brief Strobe control method parameter3
 * @note This parameter represents strobe control method parameter3 [RW].
 */
#define IKP_STROBE_PARAM3 (0x10000038)

/**
\~chinese
 * @brief 闪光控制方法参数4
 * @note 本参数表示闪光控制方法参数4【RW】。
\~english
 * @brief Strobe control method parameter4
 * @note This parameter represents strobe control method parameter4 [RW].
 */
#define IKP_STROBE_PARAM4 (0x10000039)

/**
\~chinese
 * @brief 闪光信号极性
 * @note 本参数表示闪光信号极性【RW】。
\~english
 * @brief Polarity of strobe signal
 * @note This parameter represents polarity of strobe signal [RW].
 */
#define IKP_STROBE_POLARITY (0x1000003a)

/**
\~chinese
 * @brief 通用输出信号1极性
 * @note 本参数表示通用输出信号1极性【RW】。
\~english
 * @brief Polarity of general output signal1
 * @note This parameter represents polarity of general output signal1 [RW].
 */
#define IKP_GENERAL_OUTPUT1_POLARITY (0x1000003b)

/**
\~chinese
 * @brief CL采集卡通用输出信号1输出延时【已弃用】
 * @note 本参数表示CL采集卡通用输出信号1输出延时【RW】。
\~english
 * @brief CL frame grabber general output signal1 output delay [abandoned]
 * @note This parameter represents CL frame grabber general output signal1 output delay [RW].
 */
#define IKP_GENERAL_OUTPUT1_DELAY (0x1000003c)

/**
\~chinese
 * @brief 通用输出信号2极性
 * @note 本参数表示通用输出信号2极性【RW】。
\~english
 * @brief Polarity of general output signal2
 * @note This parameter represents polarity of general output signal2 [RW].
 */
#define IKP_GENERAL_OUTPUT2_POLARITY (0x1000003d)

/**
\~chinese
 * @brief CL采集卡通用输出信号2输出延时【已弃用】
 * @note 本参数表示CL采集卡通用输出信号2输出延时【RW】。
\~english
 * @brief CL frame grabber general output signal2 output delay [abandoned]
 * @note This parameter represents CL frame grabber general output signal2 output delay [RW].
 */
#define IKP_GENERAL_OUTPUT2_DELAY (0x1000003e)

/**
\~chinese
 * @brief 通用输入信号1触发模式
 * @note 本参数表示通用输入信号1触发模式【RW】。
\~english
 * @brief General input signal1 trigger mode
 * @note This parameter represents general input signal1 trigger mode [RW].
 */
#define IKP_GENERAL_INPUT1_TRIGGER_MODE (0x1000003f)

/**
\~chinese
 * @brief 通用输入信号2触发模式
 * @note 本参数表示通用输入信号2触发模式【RW】。
\~english
 * @brief General input signal2 trigger mode
 * @note This parameter represents general input signal2 trigger mode [RW].
 */
#define IKP_GENERAL_INPUT2_TRIGGER_MODE (0x10000040)

/**
\~chinese
 * @brief CL采集卡板间同步信号1触发模式
 * @note 本参数表示CL采集卡板间同步信号1触发模式【RW】。
\~english
 * @brief CL frame grabber board synchronous signal1 trigger mode
 * @note This parameter represents CL frame grabber board synchronous signal1 trigger mode [RW].
 */
#define IKP_BOARD_SYNC1_TRIGGER_MODE (0x10000041)

/**
\~chinese
 * @brief CL采集卡板间同步信号2触发模式
 * @note 本参数表示CL采集卡板间同步信号2触发模式【RW】。
\~english
 * @brief CL frame grabber board synchronous signal2 trigger mode
 * @note This parameter represents CL frame grabber board synchronous signal2 trigger mode [RW].
 */
#define IKP_BOARD_SYNC2_TRIGGER_MODE (0x10000042)

/**
\~chinese
 * @brief 编码器A/B通道选择
 * @note 本参数表示编码器A/B通道选择【RW】。
\~english
 * @brief Encoder A/B channel selection
 * @note This parameter represents encoder A/B channel selection [RW].
 */
#define IKP_SHAFT_ENCODER1_CHANNEL (0x10000043)

/**
\~chinese
 * @brief 编码器信号倍频系数
 * @note 本参数表示编码器信号倍频系数【RW】。
\~english
 * @brief Encoder signal multiple factor
 * @note This parameter represents encoder signal multiple factor [RW].
 */
#define IKP_SHAFT_ENCODER1_MULTIPlY_FACTOR (0x10000044)

/**
\~chinese
 * @brief CL采集卡PCB版本号
 * @note 本参数表示CL采集卡PCB版本号【RO】。
\~english
 * @brief CL frame grabber PCB version number
 * @note This parameter represents CL frame grabber PCB version number [RO].
 */
#define IKP_PCB_VERSION (0x10000045)

/**
\~chinese
 * @brief CL采集卡LVAL滤波控制
 * @note 本参数表示CL采集卡LVAL滤波控制【RW】。
 *       <br> 1.
使能滤波情况下，CL采集卡会对LVAL脉冲宽度进行检测，若LVAL脉宽小于一定阈值，则认为是毛刺信号，此时不启动数据结束。
 *       <br> 2. 滤波控制适用于外部存在强电磁干扰的情况，正常采集环境不需要使用该功能。
\~english
 * @brief CL frame grabber LVAL filtering control
 * @note This parameter represents CL frame grabber LVAL filtering control [RW].
 *       <br> 1. When filtering is enabled, CL frame grabber will detect LVAL pulse width. If the LVAL pulse width is less
than a certain threshold, it is considered a burr signal and the data will not be started until it ends.
 *       <br> 2. Filter control is suitable for situations where there is strong electromagnetic interference from external
sources, and it is not necessary to use this function in normal acquisition environments.
 */
#define IKP_LVAL_FILTER (0x10000046)

/**
\~chinese
 * @brief CL采集卡面阵图像DMA传输周期数
 * @note 本参数表示CL采集卡面阵图像DMA传输周期数【RO】。
\~english
 * @brief Number of DMA transmission period for CL frame grabber area array images
 * @note This parameter represents the number of DMA transmission period for CL frame grabber area array images [RO].
 */
#define IKP_FRAME_TRANSFER_PERIOD (0x10000047)

/**
\~chinese
 * @brief CL采集卡线阵图像DMA传输周期数
 * @note 本参数表示CL采集卡线阵图像DMA传输周期数【RO】。
\~english
 * @brief Number of DMA transmission period for CL frame grabber line array images
 * @note This parameter represents the number of DMA transmission period for CL frame grabber line array images [RO].
 */
#define IKP_LINE_TRANSFER_PERIOD (0x10000048)

/**
\~chinese
 * @brief CL采集卡外触发超时系数
 * @note 本参数表示CL采集卡外触发超时系数【RW】。
 *       <br> 1. CL采集卡工作在外触发模式下，当外触发信号不良导致图像采集失败时，可以通过增加该参数值保证图像采集的正常运行。
\~english
 * @brief CL frame grabber external trigger timeout coefficient
 * @note This parameter represents the timeout coefficient of CL frame grabber external trigger [RW].
 *       <br> 1. When CL frame grabber operates in external trigger mode, and external trigger signal is poor and image
acquisition fails, increasing the parameter value can ensure the normal operation of image acquisition.
 */
#define IKP_FPGA_EXTERNAL_TRIGGER_TIMEOUT (0x10000049)

/**
\~chinese
 * @brief 相机Tap水平偏移
 * @note 本参数表示相机Tap水平偏移【RW】。
 *       <br> 1. 对于相机输出的实际数据，采集卡会根据当前Tap排列方式截取每个Tap区域最开始的若干像素。
\~english
 * @brief Camera Tap horizontal offset
 * @note This parameter represents camera Tap horizontal offset [RW].
 *       <br> 1. For actual data output by camera, the frame grabber will capture the first few pixels of each Tap area based
on the current Tap arrangement.
 */
#define IKP_IMAGE_OFFSET_X (0x10000050)

/**
\~chinese
 * @brief 通用输入信号1极性
 * @note 本参数表示通用输入信号1极性【RW】。
\~english
 * @brief Polarity of general input signal1
 * @note This parameter represents polarity of general input signal1 [RW].
 */
#define IKP_GENERAL_INPUT1_POLARITY (0x10000051)

/**
\~chinese
 * @brief 通用输入信号1最小脉冲宽度
 * @note 本参数表示通用输入信号1最小脉冲宽度【RW】。
 *       <br> 1. 当实际输入信号的脉冲宽度大于该值认为是有效触发信号，否则丢弃。
\~english
 * @brief General input signal1 minimum pulse width
 * @note This parameter represents the minimum pulse width of general input signal1 [RW].
 *       <br> 1. When the pulse width of the actual input signal is greater than this value, it is considered a valid trigger
signal, otherwise it is discarded.
 */
#define IKP_GENERAL_INPUT1_MIN_WIDTH (0x10000052)

/**
\~chinese
 * @brief 通用输入信号2极性
 * @note 本参数表示通用输入信号2极性【RW】。
\~english
 * @brief Polarity of general input signal2
 * @note This parameter represents polarity of general input signal2 [RW].
 */
#define IKP_GENERAL_INPUT2_POLARITY (0x10000053)

/**
\~chinese
 * @brief 通用输入信号2最小脉冲宽度
 * @note 本参数表示通用输入信号2最小脉冲宽度【RW】。
 *       <br> 1. 当实际输入信号的脉冲宽度大于该值认为是有效触发信号，否则丢弃。
\~english
 * @brief General input signal2 minimum pulse width
 * @note This parameter represents the minimum pulse width of general input signal2 [RW].
 *       <br> 1. When the pulse width of the actual input signal is greater than this value, it is considered a valid trigger
signal, otherwise it is discarded.
 */
#define IKP_GENERAL_INPUT2_MIN_WIDTH (0x10000054)

/**
\~chinese
 * @brief CL相机时钟频率
 * @note 本参数表示CL相机的时钟频率，单位MHz【RO】。
\~english
 * @brief CL camera clock frequency
 * @note This parameter represents CL camera clock frequency, unit is MHz [RO].
 */
#define IKP_CAMERA_PIXEL_CLOCK (0x10000055)

/**
\~chinese
 * @brief CL采集卡PCIe内部缓冲区块大小
 * @note 本参数表示CL采集卡PCIe内部缓冲区块大小，默认值为4M，提高该参数有助于减少丢帧数据的发送【RW】。
\~english
 * @brief CL frame grabber PCIe internal buffer block size
 * @note This parameter represents PCIe internal buffer block size of CL frame grabber , with a default value of 4M.
Increasing this parameter can help reduce the transmission of frame loss data [RW].
 */
#define IKP_PCIE_KERNAL_BLOCK_SIZE (0x10000056)

/**
\~chinese
 * @brief 软件触发脉冲宽度
 * @note 本参数表示软件触发脉冲宽度【RW】。
 *       <br> 1. 软件触发脉冲宽度必须小于软件触发周期且大于0。
\~english
 * @brief Software trigger pulse width
 * @note This parameter represents software trigger pulse width [RW].
 *       <br> 1. The software trigger pulse width must be less than software trigger period and greater than 0.
 */
#define IKP_SOFTWARE_TRIGGER_WIDTH (0x10000057)

/**
\~chinese
 * @brief 软件触发脉冲周期
 * @note 本参数表示软件触发脉冲周期【RW】。
 *       <br> 1. 软件触发脉冲宽度必须小于软件触发周期且大于0。
\~english
 * @brief Software trigger pulse period
 * @note This parameter represents software trigger pulse period [RW].
 *       <br> 1. The software trigger pulse width must be less than software trigger period and greater than 0.
 */
#define IKP_SOFTWARE_TRIGGER_PERIOD (0x10000058)

/**
\~chinese
 * @brief 软件触发次数
 * @note 本参数表示软件触发次数【RW】。
\~english
 * @brief Number of software trigger
 * @note This parameter represents the number of software trigger [RW].
 */
#define IKP_SOFTWARE_TRIGGER_COUNT (0x10000059)

/**
\~chinese
 * @brief 开始软件触发
 * @note 本参数表示开始软件触发【WO】。
\~english
 * @brief Start software trigger
 * @note This parameter indicates the start of software trigger [WO].
 */
#define IKP_SOFTWARE_TRIGGER_START (0x10000060)

/**
\~chinese
 * @brief 软件触发延迟时间
 * @note 本参数表示软件触发延迟时间【RW】。
\~english
 * @brief Software trigger delay time
 * @note This parameter represents software trigger delay time [RW].
 */
#define IKP_SOFTWARE_TRIGGER_DELAY (0x10000061)

/**
\~chinese
 * @brief 软件触发极性
 * @note 本参数表示软件触发极性【RW】。
\~english
 * @brief Software trigger polarity
 * @note This parameter represents software trigger polarity [RW].
 */
#define IKP_SFOTWARE_TRIGGER_POLARITY (0x10000062)

/**
\~chinese
 * @brief 采集卡采集状态
 * @note 本参数表示采集卡采集状态【RO】。
 *       <br> 1. 该参数为0表示采集卡当前未采集图像，该参数为1表示采集卡当前正在采集图像。
\~english
 * @brief Frame grabber acquisition status
 * @note This parameter represents frame grabber acquisition status [RO].
 *       <br> 1. The parameter of 0 indicates that frame grabber is not currently grabbing images, while the parameter of 1
indicates the frame grabber is currently grabbing images.
 */
#define IKP_GRAB_STATUS (0x10000063)

/**
\~chinese
 * @brief CL采集卡是否校验FVAL信号
 * @note 本参数表示CL采集卡是否校验FVAL信号【RW】。
 *       <br> 1.
本参数仅对面阵相机有效。当用户设置本参数为0时，CL采集卡将失去帧自动校准功能。CL采集卡默认校验相机帧有效信号。
\~english
 * @brief Whether CL frame grabber verify FVAL signal
 * @note This parameter represents whether CL frame grabber verifies FVAL signal [RW].
 *       <br> 1. This parameter is only valid for area scan cameras. When users set this parameter to 0, CL frame grabber
will lose frame automatic calibration function. CL frame grabber defaults to verifying valid camera frame signals.
 */
#define IKP_CHECK_FRAME_VALID_SIGNAL (0x10000064)

/**
\~chinese
 * @brief CL相机像素时钟轮询时间
 * @note 本参数表示CL相机像素时钟轮询时间【RW】。
 *       <br> 1. 用户可以通过注册IKEvent_PixelClock和IKEvent_No_PixelClock回调事件来判断相机是否接通电源。
\~english
 * @brief CL camera pixel clock polling time
 * @note This parameter represents CL camera pixel clock polling time [RW].
 *       <br> 1. Users can determine whether camera is powered on by registering IKEvent_PixelClock and IKEvent_No_PixelClock
callback events.
 */
#define IKP_PIXEL_CLOCK_POLLING_TIME (0x10000065)

/**
\~chinese
 * @brief 软件触发同步模式
 * @note 本参数表示软件触发同步模式【RW】。
\~english
 * @brief Software trigger synchronous mode
 * @note This parameter represents software trigger synchronous mode [RW].
 */
#define IKP_SOFTWARE_TRIGGER_SYNC_MODE (0x10000066)

/**
\~chinese
 * @brief 通用输入信号1延迟
 * @note 本参数表示通用输入信号1时间延迟【RW】。
\~english
 * @brief General input signal1 delay
 * @note This parameter represents general input signal1 delay [RW].
 */
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT1_DELAY (0x10000067)

/**
\~chinese
 * @brief 通用输入信号2延迟
 * @note 本参数表示通用输入信号2时间延迟【RW】。
\~english
 * @brief General input signal2 delay
 * @note This parameter represents general input signal2 delay [RW].
 */
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT2_DELAY (0x10000068)

/**
\~chinese
 * @brief 图像感兴趣区域水平偏移
 * @note 本参数表示图像感兴趣区域水平偏移，必须是16的整数倍【RW】。
\~english
 * @brief Horizontal offset of image region of interest
 * @note This parameter represents horizontal offset of image region of interest, which must be an integer multiple of 16
[RW].
 */
#define IKP_IMAGE_ROI_X (0x10000069)

/**
\~chinese
 * @brief 编码器信号最小脉冲宽度
 * @note 本参数表示编码器信号最小脉冲宽度【RW】。
 *       <br> 1. 当实际输入信号的脉冲宽度大于该值认为是有效触发信号，否则丢弃。
\~english
 * @brief Minimum pulse width of encoder signal
 * @note This parameter represents the minimum pulse width of encoder signal [RW].
 *       <br> 1. When the pulse width of actual input signal is greater than this value, it is considered a valid trigger
signal, otherwise it is discarded.
 */
#define IKP_SHAFT_ENCODER1_MIN_WIDTH (0x10000070)

/**
\~chinese
 * @brief 编码器信号有效方向控制
 * @note 本参数表示编码器信号有效方向控制【RW】。
 *       <br> 1. 当本参数为IKP_SHAFT_ENCODER1_VALID_DIR_BOTH时，编码器正向和反向输入信号均被视为有效信号。
 *       <br> 2. 当本参数为IKP_SHAFT_ENCODER1_VALID_DIR_FORWARD时，仅编码器正向信号被视为有效信号，反向信号会被采集卡丢弃。
 *       <br> 3. 当本参数为IKP_SHAFT_ENCODER1_VALID_DIR_BACKWARD时，仅编码器反向信号被视为有效信号，正向信号会被采集卡丢弃。
\~english
 * @brief Effective direction control of encoder signal
 * @note This parameter represents effective direction control of encoder signal [RW].
 *       <br> 1. When the parameter is IKP_SHAFT_ENCODER1_VALID_DIR_BOTH, both the forward and backward input signals of
encoder are considered valid signals.
 *       <br> 2. When the parameter is IKP_SHAFT_ENCODER1_VALID_DIR_FORWARD, only the forward signal of encoder is considered
a valid signal, and the backward signal will be discarded by frame grabber.
 *       <br> 3. When the parameter is IKP_SHAFT_ENCODER1_VALID_DIR_BACKWARD, only backward signal of encoder is considered a
valid signal, and the forward signal will be discarded by frame grabber.
 */
#define IKP_SHAFT_ENCODER1_VALID_DIRECTION (0x10000071)

/**
\~chinese
 * @brief 编码器信号反转补偿功能
 * @note 本参数表示编码器信号反转补偿功能【RW】。
 *       <br> 1. 当编码器信号有效方向控制参数选择正转有效或反转有效时，可以使能该参数来进行反转补偿。反转补偿效果如下:
若编码器正转100mm，然后反转10mm，接着正转50mm，则采集卡最终输出(100-10+50)mm的图像，对于反转时候回退的距离，采集卡会内部记录保证不重复出图。
\~english
 * @brief Encoder signal reverse compensation function
 * @note This parameter represents encoder signal reverse compensation function [RW].
 *       <br> 1. When effective direction control parameter of encoder signal is selected as effective for forward rotation
or effective for backward rotation, this parameter can be enabled for reverse compensation. The reverse compensation effect
is as follows: if encoder rotates forward by 100mm, then reverses by 10mm, and then rotates forward by 50mm, frame grabber
will finally output an image of (100-10+50) mm. For distance of rollback during reversal, frame grabber will internally
record it to ensure that the image is not duplicated.
 */
#define IKP_SHAFT_ENCODER1_REVERSE_COMPENSATION (0x10000072)

/**
\~chinese
 * @brief 每帧图像低32位大小
 * @note 本参数表示每帧图像低32位大小【RO】。
\~english
 * @brief Low 32bit size of each frame image
 * @note This parameter represents low 32bit size of each frame image [RO].
 */
#define IKP_FRAME_SIZE_64_LOW (0x10000073)

/**
\~chinese
 * @brief 每帧图像高32位大小
 * @note 本参数表示每帧图像高32位大小【RO】。
\~english
 * @brief High 32bit size of each frame image
 * @note This parameter represents high 32bit size of each frame image [RO].
 */
#define IKP_FRAME_SIZE_64_HIGH (0x10000074)

/**
\~chinese
 * @brief 外触发模式触发帧数
 * @note 本参数表示外触发模式触发帧数，即每接收到一个外触发信号，采集卡所采集的图像的帧数【RW】。
\~english
 * @brief Frame count in external trigger mode
 * @note This parameter represents frame count in external trigger mode, that is, the number of images grabbed by frame
grabber for each external trigger signal received [RW].
 */
#define IKP_BOARD_TRIGGER_OUTTER_MODE_FRAME_COUNT (0x10000075)

/**
\~chinese
 * @brief 编码器4倍频以上信号来源
 * @note 本参数表示编码器4倍频以上信号来源【RW】。
 *       <br> 1. 当编码器倍频为1或2时，只能通过A或B单通道传输信号。
 *       <br> 2. 当编码器倍频为4及以上时，既可以通过A或B单通道传输信号，又可以通过A、B双通道一起传输信号。
\~english
 * @brief Source of encoder signal with frequency of 4 times or higher
 * @note This parameter indicates source of encoder signal with frequency of 4 times or higher [RW].
 *       <br> 1. When encoder multiplier is 1 or 2, signal can only be transmitted through a single channel A or B.
 *       <br> 2. When encoder multiplier is 4 or more, signal can be transmitted through either single channel A or B, or
through both channels A and B.
 */
#define IKP_SHAFT_ENCODER1_QUAD_FREQUENCY_SOURCE_TYPE (0x10000076)

/**
\~chinese
 * @brief 当前缓冲区帧索引
 * @note 本参数表示当前缓冲区帧索引，必须在IKEvent_FrameReady回调事件中获取该参数【RO】。
\~english
 * @brief Current buffer index
 * @note This parameter represents the current buffer index and must be get in IKEvent_FrameReady callback event [RO].
 */
#define IKP_CURRENT_BUFFER_INDEX (0x10000077)

/**
\~chinese
 * @brief 看门狗超时时间
 * @note 本参数表示看门狗超时时间【RW】。
\~english
 * @brief Watch dog timeout time
 * @note This parameter represents watchdog timeout time [RW].
 */
#define IKP_WATCHDOG_TIMEOUT (0x10000078)

/**
\~chinese
 * @brief 开始看门狗
 * @note 本参数表示开始看门狗【WO】。
\~english
 * @brief Start watchdog
 * @note This parameter represents the start of watchdog [WO].
 */
#define IKP_WATCHDOG_START (0x10000079)

/**
\~chinese
 * @brief 停止看门狗
 * @note 本参数表示停止看门狗【WO】。
\~english
 * @brief Stop watchdog
 * @note This parameter represents the stop of watchdog [WO].
 */
#define IKP_WATCHDOG_STOP (0x1000007A)

/**
\~chinese
 * @brief 重设看门狗
 * @note 本参数表示重设看门狗【WO】。
\~english
 * @brief Reset watchdog
 * @note This parameter represents resetting watchdog [WO].
 */
#define IKP_WATCHDOG_RESET (0x1000007B)

/**
\~chinese
 * @brief 看门狗输出时间
 * @note 本参数表示看门狗输出时间【RW】。
\~english
 * @brief Watchdog output time
 * @note This parameter represents watchdog output time [RW].
 */
#define IKP_WATCHDOG_OUTPUT_TIME (0x1000007C)

/**
\~chinese
 * @brief 多灯频闪个数
 * @note 本参数表示多灯频闪个数【RW】。
\~english
 * @brief Number of multiple lights
 * @note This parameter represents the number of multiple lights [RW].
 */
#define IKP_MULTIPLE_LIGHT_COUNT (0x1000007D)

/**
\~chinese
 * @brief 缩略尺寸系数
 * @note 本参数表示缩略尺寸系数【RW】。
\~english
 * @brief Thumbnail size factor
 * @note This parameter represents thumbnail size factor [RW].
 */
#define IKP_THUMBNAIL_SIZE_FACTOR (0x1000007E)

/**
\~chinese
 * @brief 扩展模式
 * @note 本参数表示扩展模式，开启后RGB图像会被转化为RGBD图像，其中D的默认值是0【RW】。
\~english
 * @brief Expended mode
 * @note This parameter represents extended mode. RGB images will be converted to RGBD images when it is enabled, where the
default value of D is 0 [RW].
 */
#define IKP_RGBD_EXTENDED_MODE (0x1000007F)

/**
\~chinese
 * @brief 板间同步信号1最小脉冲宽度
 * @note 本参数表示板间同步信号1最小脉冲宽度【RW】。
 *       <br> 1. 当实际信号的脉冲宽度大于该值认为是有效信号，否则丢弃。
\~english
 * @brief Minimum pulse width of board synchronous signal1
 * @note This parameter represents the minimum pulse width of board synchronous signal1 [RW].
 *       <br> 1. When pulse width of actual signal is greater than this value, it is considered a valid signal, otherwise it
is discarded.
 */
#define IKP_BOARD_SYNC1_DEBOUNCE (0x10000080)

/**
\~chinese
 * @brief 板间同步信号2最小脉冲宽度
 * @note 本参数表示板间同步信号2最小脉冲宽度【RW】。
 *       <br> 1. 当实际信号的脉冲宽度大于该值认为是有效信号，否则丢弃。
\~english
 * @brief Minimum pulse width of board synchronous signal2
 * @note This parameter represents the minimum pulse width of board synchronous signal2 [RW].
 *       <br> 1. When pulse width of actual signal is greater than this value, it is considered a valid signal, otherwise it
is discarded.
 */
#define IKP_BOARD_SYNC2_DEBOUNCE (0x10000081)

/**
\~chinese
 * @brief 采集卡缓冲区chunk最小值
 * @note 本参数表示采集卡缓冲区chunk最小值【RW】。
\~english
 * @brief Minimum value of frame grabber buffer chunk
 * @note This parameter represents the minimum value of frame grabber buffer chunk [RW].
 */
#define IKP_CHUNK_COUNT_MINIMUM (0x10000082)

/**
\~chinese
 * @brief 采集卡重叠高度
 * @note 本参数表示采集卡重叠高度【RW】。
\~english
 * @brief Overlapping height of frame grabber
 * @note This parameter represents overlapping height of frame grabber [RW].
 */
#define IKP_OVERLAPPED_HEIGHT (0x10000083)

/**
\~chinese
 * @brief 采集卡不定长采图自动清空机制
 * @note 本参数表示采集卡不定长采图自动清空机制，适用于CXP/SFP/GVB采集卡【RW】。
\~english
 * @brief Automatic clearing mechanism of frame grabber for frame active image
 * @note This parameter represents automatic clearing mechanism of frame grabber for frame active image, which is applicable
to CXP/SFP/GVB frame grabbers [RW].
 */
#define IKP_FRAME_ACTIVE_AUTO_BLANK (0x10000084)

/**
\~chinese
 * @brief 编码器信号倍频系数任意值
 * @note 本参数表示编码器信号倍频系数任意值【RW】。
\~english
 * @brief Encoder signal multiple factor of any value
 * @note This parameter represents encoder signal multiple factor of any value [RW].
 */
#define IKP_SHAFT_ENCODER1_MULTIPlY_FACTOR_ANY (0x10000085)

/**
\~chinese
 * @brief CL采集卡all_levels模式下低电平图像高度
 * @note 本参数表示CL采集卡all_levels模式下低电平图像高度【RW】。
\~english
 * @brief Low level image height in all_levels mode of CL frame grabber
 * @note This parameter represents low level image height in all_levels mode of CL frame grabber [RW].
 */
#define IKP_IMAGE_HEIGHT_2ND (0x10000086)

/**
\~chinese
 * @brief PFNC 标准图像像素格式
 * @note 本参数表示采集卡的GenICam PFNC图像像素格式【RW】。
\~english
 * @brief PFNC image pixel format.
 * @note This parameter represents the frame grabber PFNC image pixel format [RW].
 */
#define IKP_IMAGE_PIXEL_FORMAT_PFNC (0x10000087)

/**
\~chinese
 * @brief 采集卡序列号
 * @note 本参数表示采集卡序列号，该参数是32位无符号整数类型【RO】。
\~english
 * @brief Frame grabber serial number
 * @note This parameter represents frame grabber serial number, which is a 32-bit unsigned integer type [RO].
 */
#define IKP_FPGA_SERIAL_NUMBER (0x20000001)

/**
\~chinese
 * @brief 采集卡PCIe链路状态
 * @note 本参数表示采集卡PCIe链路状态【RO】。
 *       <br> 1. 当采集卡PCIe链路速度无法满足图像传输速度时，会导致采集丢帧。
\~english
 * @brief PCIe link status of frame grabber
 * @note This parameter represents PCIe link status of frame grabber [RO].
 *       <br> 1. When PCIe link speed of frame grabber cannot meet image transmission speed, it will result in frame loss
during acquisition.
 */
#define IKP_PCIE_LINK_STATE (0x20000002)

/**
\~chinese
 * @brief 采集卡PCIe链路速度不足导致的丢帧次数
 * @note 本参数表示采集卡PCIe链路速度不足导致的丢帧次数【RO】。
\~english
 * @brief The number of lost frames caused by insufficient PCIe link speed of frame grabber
 * @note This parameter represents the number of lost frames caused by insufficient PCIe link speed of frame grabber [RO].
 */
#define IKP_PCIE_SPEED_MISS_REQUIREMENT (0x20000003)

/**
\~chinese
 * @brief 采集卡PCIe配置空间
 * @note 本参数表示采集卡PCIe配置空间【RO】。
\~english
 * @brief PCIe configuration space for frame grabber
 * @note This parameter represents PCIe configuration space of frame grabber [RO].
 */
#define IKP_PCI_CONFIGURATION (0x20000004)

/**
\~chinese
 * @brief CL采集卡通用输入信号延迟模式
 * @note 本参数表示CL采集卡通用输入信号延迟模式，分为行延迟模式和时间延迟模式【RW】。
\~english
 * @brief CL frame grabber general input signal delay mode
 * @note This parameter represents CL frame grabber general input signal delay mode, which is divided into line delay mode
and time delay mode [RW].
 */
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_MODE (0x20000005)

/**
\~chinese
 * @brief CL采集卡通用输入信号1行延迟
 * @note 本参数表示CL采集卡通用输入信号1行延迟【RW】。
\~english
 * @brief CL frame grabber general input signal1 line delay
 * @note This parameter represents CL frame grabber general input signal1 line delay [RW].
 */
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT1_DELAY_IN_LINES (0x20000006)

/**
\~chinese
 * @brief CL采集卡通用输入信号2行延迟
 * @note 本参数表示CL采集卡通用输入信号2行延迟【RW】。
\~english
 * @brief CL frame grabber general input signal2 line delay
 * @note This parameter represents CL frame grabber general input signal2 line delay [RW].
 */
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT2_DELAY_IN_LINES (0x20000007)

/**
\~chinese
 * @brief 内部信号计数器
 * @note 本参数表示从采集卡读取的内部信号个数【RO】。
\~english
 * @brief Internal signal counter
 * @note This parameter represents the number of internal signals read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_INTERNAL_COUNT (0x20000008)

/**
\~chinese
 * @brief 通用输入信号1计数器
 * @note 本参数表示从采集卡读取的通用输入信号1个数【RO】。
\~english
 * @brief General input signal1 counter
 * @note This parameter represents the number of general input signal1 read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_GENERAL_1_COUNT (0x20000009)

/**
\~chinese
 * @brief 通用输入信号2计数器
 * @note 本参数表示从采集卡读取的通用输入信号2个数【RO】。
\~english
 * @brief General input signal2 counter
 * @note This parameter represents the number of general input signal2 read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_GENERAL_2_COUNT (0x2000000a)

/**
\~chinese
 * @brief 编码器A通道信号计数器
 * @note 本参数表示从采集卡读取的编码器A通道信号个数【RO】。
\~english
 * @brief Encoder A channel signal counter
 * @note This parameter represents the number of encoder A channel signals read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_SHAFT_ENCODER_A_COUNT (0x2000000b)

/**
\~chinese
 * @brief 编码器B通道信号计数器
 * @note 本参数表示从采集卡读取的编码器B通道信号个数【RO】。
\~english
 * @brief Encoder B channel signal counter
 * @note This parameter represents the number of encoder B channel signals read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_SHAFT_ENCODER_B_COUNT (0x2000000c)

/**
\~chinese
 * @brief 板间同步信号1计数器
 * @note 本参数表示从采集卡读取的板间同步信号1个数【RO】。
\~english
 * @brief Board synchronous signal1 counter
 * @note This parameter represents the number of board synchronous signal1 read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_BOARD_SYNC_IN_1_COUNT (0x2000000d)

/**
\~chinese
 * @brief 积分信号1计数器
 * @note 本参数表示从采集卡读取的积分信号1个数【RO】。
\~english
 * @brief Integration signal1 counter
 * @note This parameter represents the number of integration signal1 read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_INTEGRATION_SIG_1_COUNT (0x2000000e)

/**
\~chinese
 * @brief 积分信号2计数器
 * @note 本参数表示从采集卡读取的积分信号2个数【RO】。
\~english
 * @brief Integration signal2 counter
 * @note This parameter represents the number of integration signal2 read from frame grabber [RO].
 */
#define IKP_EVENT_INPUT_INTEGRATION_SIG_2_COUNT (0x2000000f)

/**
\~chinese
 * @brief CL采集卡行间超时情况下是否丢弃已采集的未完成帧的数据
 * @note 本参数表示CL采集卡行间超时情况下是否丢弃已采集的未完成帧的数据【RW】。
\~english
 * @brief Whether to deprecate incomplete frame data when CL frame grabber occurs to line timeout
 * @note This parameter indicates whether to deprecate incomplete frame data when CL frame grabber occurs to line timeout
[RW].
 */
#define IKP_RCV_MORE_DATA_IN_TRIGGER_MODE (0x20000010)

/**
\~chinese
 * @brief 是否禁用IO事件
 * @note 本参数表示是否禁用IO事件【RW】。
\~english
 * @brief Whether to disable IO events
 * @note This parameter represents whether to disable IO events [RW].
 */
#define IKP_DISABLE_IO_EVENT (0x20000011)

/**
\~chinese
 * @brief 是否支持公版库
 * @note 本参数表示是否支持公版库【RW】。
\~english
 * @brief Whether to support public library
 * @note This parameter represents whether to support public library [RW].
 */
#define IKP_PUBLIC_VERSION_SUPPORT (0x20000012)

/**
\~chinese
 * @brief 编码器信号反转补偿最大值
 * @note 本参数表示编码器反转补偿最大值，超过该值后不再补偿编码器反转信号【RW】。
\~english
 * @brief Maximum value of encoder signal reverse compensation
 * @note This parameter represents the maximum value of encoder reverse compensation, beyond which the encoder reverse signal
will no longer be compensated [RW].
 */
#define IKP_SHAFT_ENCODER1_REVERSE_COMPENSATION_LIMIT (0x20000013)

/**
\~chinese
 * @brief 编码器信号占空比补偿功能类型
 * @note 本参数表示编码器信号占空比补偿功能类型【RW】。
 *       <br> 1.
当采集卡同时使用AB相触发且占空比不是50%时，采集卡行频会发生波动。为了消除行频波动，可以设置此选项。当占空比小于50%时选择Falling，当占空比大于50%时选择Rising。
\~english
 * @brief Clock duty compensation type of CL frame grabber
 * @note This parameter represents clock duty compensation type of CL frame grabber [RW].
 *       <br> 1. When frame grabber is triggered by both AB phase and the duty cycle is not 50%, the line rate of frame
grabber will fluctuate. To eliminate line rate fluctuations, this option can be set. When duty cycle is less than 50%, choose
Falling, and when duty cycle is greater than 50%, choose Rising.
 */
#define IKP_SHAFT_ENCODER1_CLOCK_DUTY_COMPENSATION_TYPE (0x20000014)

/**
\~chinese
 * @brief 编码器信号占空比不是50%时的补偿宽度
 * @note 本参数表示编码器信号占空比不是50%时的补偿宽度【RW】。
 *       <br> 1. 补偿宽度计算公式如下: Clock Duty Compensation Width(ns) =
|（0.5-占空比）*Period|，其中Period为触发信号周期，单位ns。
\~english
 * @brief Clock duty compensation width of CL frame grabber
 * @note This parameter represents clock duty compensation width of CL frame grabber [RW].
 *       <br> 1. The calculation formula is as follows: Clock Duty Compensation Width(ns) = |（0.5-duty cycle）*Period|,
where Period is the trigger signal period in ns.
 */
#define IKP_SHAFT_ENCODER1_CLOCK_DUTY_COMPENSATION_WIDTH (0x20000015)

/**
\~chinese
 * @brief CL采集卡有效列
 * @note 本参数表示CL采集卡有效列，抽取所有列/偶数列/奇数列进行图像输出【RW】。
 *       <br> 1. 设置奇数列/偶数列时行分辨率减半。
\~english
 * @brief CL frame grabber valid column
 * @note This parameter represents CL frame grabber valid column, extracting all columns/even columns/odd columns for image
output [RW].
 *       <br> 1. When setting odd/even columns, the line resolution is halved.
 */
#define IKP_CL_VALID_COLUMN (0x20000016)

/**
\~chinese
 * @brief CL采集卡信号增强模式
 * @note 本参数表示CL采集卡信号增强模式【RW】。
 *       <br> 1. 该参数主要用于改善Plus采集卡在远距离传输时的误码现象，在短距离传输时要关闭信号增强模式，其他情况默认开启。
\~english
 * @brief CL frame grabber signal enhance mode
 * @note This parameter represents CL frame grabber signal enhance mode [RW].
 *       <br> 1. This parameter is mainly used to improve code error phenomenon of Plus frame grabbers during long-distance
transmission. The signal enhance mode should be turned off during short distance transmission, and it should be turned on by
default in other situations.
 */
#define IKP_CL_SIGNAL_ENHANCE_MODE (0x20000017)

/**
\~chinese
 * @brief CL采集卡远距离传输功能【已弃用】
 * @note 本参数表示CL采集卡远距离传输功能【RW】。
 *       <br> 1. 该参数主要用于K6采集卡，当传输线缆小于等于7米时关闭该功能，否则开启。
\~english
 * @brief Long distance transmission function of CL frame grabber [abandoned]
 * @note This parameter represents long distance transmission function of CL frame grabber [RW].
 *       <br> 1. This parameter is mainly used for K6 frame grabbers. When transmission cable is less than or equal to 7
meters, this function is turned off, otherwise it is turned on.
 */
#define IKP_CL_LONG_DISTANCE_TRANSMISSION (0x20000018)

/**
\~chinese
 * @brief 采集卡序列号高32位
 * @note 采集卡序列号共64位，本参数表示采集卡序列号高32位数据【RO】。
\~english
 * @brief High 32 bits of frame grabber serial number
 * @note Frame grabber serial number has 64 bits, and this parameter is used to get high 32 bits [RO].
 */
#define IKP_FPGA_SERIAL_NUMBER_HIGH (0x20000019)

/**
\~chinese
 * @brief CL采集卡长线缆工作模式【已弃用】
 * @note 本参数表示CL采集卡长线缆工作模式【RW】。
 *       <br> 1.
使能该模式前，用户首先需要将相机的采集模式配置为自由运行模式，输出模式配置为测试图像，然后调用IKapPrepareGrab函数进行图像采集。
\~english
 * @brief CL frame grabber long cable working mode [abandoned]
 * @note This parameter represents CL frame grabber long cable working mode [RW].
 *       <br> 1. Before enabling this mode, users need to first configure camera's acquisition mode as free run mode, and
video mode as test image, and then call IKapPrepareGrab function to grab images.
 */
#define IKP_CL_LONG_CABLE_WORKING_MODE (0x20000020)
#define IKP_CL_GPIO_ENABLE             (0x20000021)

/**
\~chinese
 * @brief CXP采集卡测试图像
 * @note 本参数表示CXP采集卡测试图像【RW】。
\~english
 * @brief CXP frame grabber test image
 * @note This parameter represents CXP frame grabber test image [RW].
 */
#define IKP_CXP_TEST_IMAGE (0x30000001)

/**
\~chinese
 * @brief CXP采集卡触发输出选择
 * @note 本参数表示CXP采集卡触发输出选择【RW】。
\~english
 * @brief CXP frame grabber trigger output selection
 * @note This parameter represents CXP frame grabber trigger output selection [RW].
 */
#define IKP_CXP_TRIGGER_OUTPUT_SELECTOR (0x30000002)

/**
\~chinese
 * @brief 最新帧索引
 * @note 本参数表示采集卡最近一次采集完成的图像的帧索引【RO】。
\~english
 * @brief Latest frame index
 * @note This parameter represents frame index of the most recently grabbed image by frame grabber [RO].
 */
#define IKP_LAST_FRAME_INDEX (0x30000003)

/**
\~chinese
 * @brief CXP采集卡电压状态
 * @note 本参数表示CXP采集卡电压状态【RO】。
\~english
 * @brief CXP frame grabber voltage status
 * @note This parameter represents CXP frame grabber voltage status [RO].
 */
#define IKP_CXP_VOLTAGE_SUPPLY_STATUS (0x30000004)

/**
\~chinese
 * @brief CXP采集卡PoCXP功能开关
 * @note 本参数表示CXP采集卡PoCXP功能开关【RW】。
\~english
 * @brief CXP frame grabber PoCXP function switch
 * @note This parameter represents CXP frame grabber PoCXP function switch [RW].
 */
#define IKP_CXP_POWER_SWITCH (0x30000005)

/**
\~chinese
 * @brief CXP采集卡电源状态
 * @note 本参数表示CXP采集卡电源状态【RO】。
 *       <br> 1. CXP采集卡电源状态具体说明如下:
 * <table>
 * <tr><th>状态           <th>说明
 * <tr><td>Off            <td>当前选中的通道PoCXP功能关闭，或未插接外部供电线
 * <tr><td>Detecting      <td>当前选中的通道PoCXP功能打开，但未找到匹配的PoCXP受电设备
 * <tr><td>On             <td>当前选中的通道正在为设备提供PoCXP供电
 * <tr><td>Ocp            <td>当前选中的通道发生了过流保护事件，需要进行恢复
 * </table>
\~english
 * @brief CXP frame grabber power status
 * @note This parameter represents CXP frame grabber power status [RO].
 *       <br> 1. The specific description of CXP frame grabber power status is as follows:
 * <table>
 * <tr><th>Status        <th>Description
 * <tr><td>Off           <td>PoCXP function of the currently selected channel is turned off or external power supply cable is
not plugged in
 * <tr><td>Detecting     <td>The currently selected channel's PoCXP function is enabled, but no matching PoCXP powered device
is found
 * <tr><td>On            <td>The currently selected channel is providing PoCXP power to device
 * <tr><td>Ocp           <td>The currently selected channel has experienced an overcurrent protection event and needs to be
restored
 * </table>
 */
#define IKP_CXP_POWER_STATUS (0x30000006)

/**
\~chinese
 * @brief CXP采集卡当前选中通道的供电电流
 * @note 本参数表示CXP采集卡当前选中通道的供电电流【RO】。
\~english
 * @brief The power supply current of the currently selected channel on CXP frame grabber
 * @note This parameter represents the power supply current of the currently selected channel on CXP frame grabber [RO].
 */
#define IKP_CXP_SENSE_CURRENT (0x30000007)

/**
\~chinese
 * @brief CXP采集卡当前选中通道的供电电压
 * @note 本参数表示CXP采集卡当前选中通道的供电电压【RO】。
\~english
 * @brief The power supply voltage of the currently selected channel on CXP frame grabber
 * @note This parameter represents the power supply voltage of the currently selected channel on CXP frame grabber [RO].
 */
#define IKP_CXP_BUS_VOLTAGE (0x30000008)

/**
\~chinese
 * @brief CXP采集卡过流保护重置
 * @note 本参数表示CXP采集卡过流保护重置【WO】。
\~english
 * @brief CXP frame grabber overcurrent protection reset
 * @note This parameter represents CXP frame grabber overcurrent protection reset [WO].
 */
#define IKP_CXP_RESET_OCP (0x30000009)

/**
\~chinese
 * @brief CXP采集卡检测状态监测电压上限
 * @note 本参数表示CXP采集卡检测状态监测电压上限，默认值4400（5.5V）【RW】。
\~english
 * @brief CXP frame grabber detection status monitoring voltage upper limit
 * @note This parameter represents CXP frame grabber detection status monitoring voltage upper limit, with a default value of
4400 (5.5V) [RW].
 */
#define IKP_CXP_SENSE_VOLTAGE_HIGH (0x3000000a)

/**
\~chinese
 * @brief CXP采集卡检测状态监测电压下限
 * @note 本参数表示CXP采集卡检测状态监测电压下限，默认值800（1V）【RW】。
\~english
 * @brief CXP frame grabber detection status monitoring voltage lower limit
 * @note This parameter represents CXP frame grabber detection status monitoring voltage lower limit, with a default value of
800 (1V) [RW].
 */
#define IKP_CXP_SENSE_VOLTAGE_LOW (0x3000000b)

/**
\~chinese
 * @brief CXP采集卡供电状态监测电压下限
 * @note 本参数表示CXP采集卡供电状态监测电压下限，默认值800（1V）【RW】。
\~english
 * @brief CXP frame grabber power supply status monitoring voltage lower limit
 * @note This parameter represents CXP frame grabber power supply status monitoring voltage lower limit, with a default value
of 800 (1V) [RW].
 */
#define IKP_CXP_SUPPLY_VOLTAGE_LOW (0x3000000c)

/**
\~chinese
 * @brief CXP采集卡供电状态监测电流下限
 * @note 本参数表示CXP采集卡供电状态监测电流下限，默认值320（8mA）【RW】。
\~english
 * @brief CXP frame grabber power supply status monitoring current lower limit
 * @note This parameter represents CXP frame grabber power supply status monitoring current lower limit, with a default value
of 320 (8mA) [RW].
 */
#define IKP_CXP_SUPPLY_CURRENT_LOW (0x3000000d)

/**
\~chinese
 * @brief CXP采集卡超时时间【已弃用】
 * @note 本参数表示CXP采集卡超时时间【RW】。
\~english
 * @brief CXP frame grabber timeout time[abandoned]
 * @note This parameter represents CXP frame grabber timeout time [RW].
 */
#define IKP_CXP_FPGA_FRAME_TIMEOUT (0x3000000e)

/**
\~chinese
 * @brief CXP采集卡超时时间【已弃用】
 * @note 本参数表示CXP采集卡超时时间【RW】。
\~english
 * @brief CXP frame grabber timeout time[abandoned]
 * @note This parameter represents CXP frame grabber timeout time [RW].
 */
#define IKP_CXP_FPGA_FRAME_TIMEOUT_MULTIPLE (0x3000000f)

/**
\~chinese
 * @brief CXP采集卡CRC错误个数
 * @note 本参数表示CXP采集卡CRC错误个数【RO】。
\~english
 * @brief Number of CRC errors on CXP frame grabber
 * @note This parameter represents the number of CRC errors on CXP frame grabber [RO].
 */
#define IKP_CXP_CRC_ERROR_COUNT (0x30000010)

/**
\~chinese
 * @brief CXP采集卡PoCXP通道
 * @note 本参数表示CXP采集卡PoCXP通道【RW】。
\~english
 * @brief CXP frame grabber PoCXP channel
 * @note This parameter represents CXP frame grabber PoCXP channel [RW].
 */
#define IKP_CXP_PoCXP_CHANNEL (0x30000011)

/**
\~chinese
 * @brief CXP采集卡切换至高压前检测到的PoCXP电压值
 * @note 本参数表示CXP采集卡切换至高压前检测到的PoCXP电压值【RO】。
\~english
 * @brief PoCXP voltage value detected by CXP frame grabber before switching to high voltage
 * @note This parameter represents PoCXP voltage value detected by CXP frame grabber before switching to high voltage [RO].
 */
#define IKP_CXP_PoCXP_LOCKED_VOLTAGE (0x30000012)

/**
\~chinese
 * @brief CXP采集卡编码器输入信号去抖窗口长度
 * @note 本参数表示CXP采集卡编码器输入信号去抖窗口长度【RW】。
 *       <br> 1. 该参数用于减少毛刺信号对采集的影响，去抖窗口越大，滤除信号的脉冲宽度也越大。
\~english
 * @brief CXP frame grabber encoder input signal debounce window length
 * @note This parameter represents CXP frame grabber encoder input signal debounce window length [RW].
 *       <br> 1. This parameter is used to reduce the impact of burr signals on acquisition. The larger debounce window is,
the wider pulse width of filtered signal is.
 */
#define IKP_CXP_SHAFT_ENCODER_DEBOUNCE (0x30000013)

/**
\~chinese
 * @brief CXP采集卡编码器计数器模式
 * @note 本参数表示CXP采集卡编码器计数器模式【RW】。
\~english
 * @brief CXP frame grabber encoder counter mode
 * @note This parameter represents CXP frame grabber encoder counter mode [RW].
 */
#define IKP_CXP_SHAFT_ENCODER_TICK_MODE (0x30000014)

/**
\~chinese
 * @brief CXP采集卡编码器的计数器最大值
 * @note 本参数表示CXP采集卡编码器的计数器最大值【RW】。
\~english
 * @brief Maximum value of CXP frame grabber encoder counter
 * @note This parameter represents the maximum value of CXP frame grabber encoder counter [RW].
 */
#define IKP_CXP_SHAFT_ENCODER_TICK_MAX (0x30000015)

/**
\~chinese
 * @brief CXP采集卡编码器计数器重置
 * @note 本参数表示CXP采集卡编码器计数器重置【WO】。
\~english
 * @brief CXP frame grabber encoder counter reset
 * @note This parameter represents CXP frame grabber encoder counter reset [WO].
 */
#define IKP_CXP_SHAFT_ENCODER_TICK_RESET (0x30000016)

/**
\~chinese
 * @brief CXP采集卡编码器计数器当前值
 * @note 本参数表示CXP采集卡编码器计数器当前值【RO】。
\~english
 * @brief CXP frame grabber encoder counter current value
 * @note This parameter represents CXP frame grabber encoder counter current value [RO].
 */
#define IKP_CXP_SHAFT_ENCODER_TICK_COUNT (0x30000017)

/**
\~chinese
 * @brief CXP采集卡编码器工作模式
 * @note 本参数表示CXP采集卡编码器工作模式【RW】。
\~english
 * @brief CXP frame grabber encoder working mode
 * @note This parameter represents CXP frame grabber encoder working mode [RW].
 */
#define IKP_CXP_SHAFT_ENCODER_REVERSE_MODE (0x30000018)

/**
\~chinese
 * @brief CXP采集卡编码器反向计数器最大值
 * @note 本参数表示CXP采集卡编码器反向计数器最大值【RW】。
\~english
 * @brief CXP frame grabber encoder reverse counter maximum value
 * @note This parameter represents CXP frame grabber encoder reverse counter maximum value [RW].
 */
#define IKP_CXP_SHAFT_ENCODER_REVERSE_MAX (0x30000019)

/**
\~chinese
 * @brief CXP采集卡编码器反向计数器重置
 * @note 本参数表示CXP采集卡编码器反向计数器重置【WO】。
\~english
 * @brief CXP frame grabber encoder reverse counter reset
 * @note This parameter represents CXP frame grabber encoder reverse counter reset [WO].
 */
#define IKP_CXP_SHAFT_ENCODER_REVERSE_RESET (0x30000020)

/**
\~chinese
 * @brief CXP采集卡编码器反向计数器当前值
 * @note 本参数表示CXP采集卡编码器反向计数器当前值【RO】。
\~english
 * @brief CXP frame grabber encoder reverse counter current value
 * @note This parameter represents CXP frame grabber encoder reverse counter current value [RO].
 */
#define IKP_CXP_SHAFT_ENCODER_REVERSE_COUNT (0x30000021)

/**
\~chinese
 * @brief CXP采集卡通用输出信号1电压阈值
 * @note 本参数表示CXP采集卡通用输出信号1电压阈值【RW】。
\~english
 * @brief CXP frame grabber general output signal1 voltage threshold
 * @note This parameter represents CXP frame grabber general output signal1 voltage threshold [RW].
 */
#define IKP_CXP_GENERAL_OUTPUT1_THRESHOLD (0x30000022)

/**
\~chinese
 * @brief CXP采集卡通用输出信号2电压阈值
 * @note 本参数表示CXP采集卡通用输出信号2电压阈值【RW】。
\~english
 * @brief CXP frame grabber general output signal2 voltage threshold
 * @note This parameter represents CXP frame grabber general output signal2 voltage threshold [RW].
 */
#define IKP_CXP_GENERAL_OUTPUT2_THRESHOLD (0x30000023)

/**
\~chinese
 * @brief CXP采集卡固件类型
 * @note 本参数表示CXP采集卡固件类型【RO】。
\~english
 * @brief CXP frame grabber firmware type
 * @note This parameter represents CXP frame grabber firmware type [RO].
 */
#define IKP_CXP_FIRMWARE_TYPE (0x30000024)

/**
\~chinese
 * @brief GVB采集卡固件类型
 * @note 本参数表示GVB采集卡固件类型【RO】。
\~english
 * @brief GVB frame grabber firmware type
 * @note This parameter represents GVB frame grabber firmware type [RO].
 */
#define IKP_GVB_FIRMWARE_TYPE (0x30000024)

/**
\~chinese
 * @brief CXP采集卡温度
 * @note 本参数表示CXP采集卡温度【RO】。
\~english
 * @brief CXP frame grabber temperature
 * @note This parameter represents CXP frame grabber temperature [RO].
 */
#define IKP_CXP_TEMPERATURE (0x30000025)

/**
\~chinese
 * @brief GVB采集卡温度
 * @note 本参数表示GVB采集卡温度【RO】。
\~english
 * @brief GVB frame grabber temperature
 * @note This parameter represents GVB frame grabber temperature [RO].
 */
#define IKP_GVB_TEMPERATURE (0x30000025)

/**
\~chinese
 * @brief CXP采集卡通用输入信号电压阈值
 * @note 本参数表示CXP采集卡通用输入信号电压阈值【RW】。
\~english
 * @brief CXP frame grabber general input signal voltage threshold
 * @note This parameter represents CXP frame grabber general input signal voltage threshold [RW].
 */
#define IKP_CXP_GENERAL_INPUT_THRESHOLD (0x30000026)

/**
\~chinese
 * @brief CXP采集卡通用输出信号1通道
 * @note 本参数表示CXP采集卡通用输出信号1通道【RW】。
\~english
 * @brief CXP frame grabber general output signal1 channel
 * @note This parameter represents CXP frame grabber general output signal1 channel [RW].
 */
#define IKP_CXP_GENERAL_OUTPUT1_SOURCE_CHANNEL (0x30000027)

/**
\~chinese
 * @brief CXP采集卡通用输出信号2通道
 * @note 本参数表示CXP采集卡通用输出信号2通道【RW】。
\~english
 * @brief CXP frame grabber general output signal2 channel
 * @note This parameter represents CXP frame grabber general output signal2 channel [RW].
 */
#define IKP_CXP_GENERAL_OUTPUT2_SOURCE_CHANNEL (0x30000028)

/**
\~chinese
 * @brief CXP采集卡通用输入信号1类型
 * @note 本参数表示CXP采集卡通用输入信号1类型【RW】。
\~english
 * @brief CXP frame grabber general output signal1 type
 * @note This parameter represents CXP frame grabber general output signal1 type [RW].
 */
#define IKP_CXP_GENERAL_INPUT1_TYPE (0x30000029)

/**
\~chinese
 * @brief CXP采集卡通用输入信号2类型
 * @note 本参数表示CXP采集卡通用输入信号2类型【RW】。
\~english
 * @brief CXP frame grabber general output signal2 type
 * @note This parameter represents CXP frame grabber general output signal2 type [RW].
 */
#define IKP_CXP_GENERAL_INPUT2_TYPE (0x3000002a)

/**
\~chinese
 * @brief CXP采集卡传输通道选择
 * @note 本参数表示CXP采集卡传输通道选择【RW】。
\~english
 * @brief CXP frame grabber transmission channel selection
 * @note This parameter represents CXP frame grabber transmission channel selection [RW].
 */
#define IKP_CXP_TRANSFER_CHANNEL_SELECTOR (0x3000002b)

/**
\~chinese
 * @brief CXP采集卡传输包丢失数量
 * @note 本参数表示CXP采集卡传输包丢失数量【RO】。
\~english
 * @brief Number of lost transmission packets on CXP frame grabber
 * @note This parameter represents the number of lost transmission packets on CXP frame grabber [RO].
 */
#define IKP_CXP_CHANNEL_LOST_COUNT (0x3000002c)

/**
\~chinese
 * @brief CXP采集卡传输包错误数量
 * @note 本参数表示CXP采集卡传输包错误数量【RO】。
\~english
 * @brief CXP frame grabber transmission packet error count
 * @note This parameter represents CXP frame grabber transmission packet error count [RO].
 */
#define IKP_CXP_CHANNEL_ERROR_COUNT (0x3000002d)

/**
\~chinese
 * @brief 不定长采集模式
 * @note 本参数表示不定长采集模式【RW】。
\~english
 * @brief Frame active acquisition mode
 * @note This parameter represents frame active acquisition mode [RW].
 */
#define IKP_TRIGGER_FRAME_ACTIVE_MODE (0x3000002e)

/**
\~chinese
 * @brief JPEG压缩模式
 * @note 本参数表示JPEG压缩模式【RW】。
\~english
 * @brief JPEG compression mode
 * @note This parameter represents JPEG compression mode [RW].
 */
#define IKP_JPEG_COMPRESS_ENABLE (0x3000002f)

/**
\~chinese
 * @brief JPEG压缩质量
 * @note 本参数表示JPEG压缩质量，数值越大，图像压缩质量越好，传输数据量也越大【RW】。
\~english
 * @brief JPEG compression quality
 * @note This parameter represents JPEG compression quality. The higher the value, the better the image compression quality
and the larger the amount of transmitted data [RW].
 */
#define IKP_JPEG_COMPRESS_QUALITY (0x30000030)

/**
\~chinese
 * @brief CXP采集卡接受一个触发信号后产生的给相机的连续信号的个数
 * @note 本参数表示CXP采集卡接受一个触发信号后产生的给相机的连续信号的个数【RW】。
\~english
 * @brief Continuous signal count generated by CXP frame grabber
 * @note This parameter represents continuous signal count generated by CXP frame grabber [RW].
 */
#define IKP_CXP_FRAME_BURST_COUNT (0x30000031)

/**
\~chinese
 * @brief CXP采集卡产生连续信号的周期
 * @note 本参数表示CXP采集卡产生连续信号的周期【RW】。
 *       <br> 1. 该参数应该大于相机的最小帧周期，否则可能出现丢失触发信号现象。
\~english
 * @brief Period of CXP frame grabber to generate continuous signal
 * @note This parameter represents period of CXP frame grabber to generate continuous signal [RW].
 *       <br> 1. This parameter should be greater than the minimum frame period of the camera, otherwise, trigger signals may
be lost.
 */
#define IKP_CXP_FRAME_BURST_PERIOD (0x30000032)

/**
\~chinese
 * @brief CXP采集卡通道CRC错误发生次数
 * @note 本参数表示CXP采集卡通道CRC错误发生次数【RO】。
\~english
 * @brief Number of CRC errors in CXP frame grabber channel
 * @note This parameter represents the number of CRC errors in CXP frame grabber channel [RO].
 */
#define IKP_CXP_CHANNEL_CRC_ERROR_COUNT (0x30000033)

/**
\~chinese
 * @brief CXP采集卡边沿触发模式
 * @note 本参数表示CXP采集卡边沿触发模式【RW】。
\~english
 * @brief CXP frame grabber edge trigger mode
 * @note This parameter represents CXP frame grabber edge trigger mode [RW].
 */
#define IKP_CXP_TRIG_EDGE_MODE (0x30000034)

/**
\~chinese
 * @brief CXP采集卡压缩传输模式
 * @note 本参数表示CXP采集卡压缩传输模式【RW】。
\~english
 * @brief CXP frame grabber compression transmission mode
 * @note This parameter represents CXP frame grabber compression transmission mode [RW].
 */
#define IKP_CXP_DATA_PACKED_TRANSFER (0x30000035)

/**
\~chinese
 * @brief CXP采集卡传输给相机的触发包电平极性
 * @note 本参数表示CXP采集卡传输给相机的触发包电平极性【RW】。
\~english
 * @brief Level polarity of trigger packets that transfer to camera from SFP frame grabber
 * @note This parameter represents level polarity of trigger packets that transfer to camera from SFP frame grabber [RW].
 */
#define IKP_CXP_TRIG_LEVEL (0x30000036)

/**
\~chinese
 * @brief CXP采集卡板间同步信号1极性
 * @note 本参数表示CXP采集卡板间同步信号1极性【RW】。
\~english
 * @brief CXP frame grabber board synchronous signal1 polarity
 * @note This parameter represents CXP frame grabber board synchronous signal1 polarity [RW].
 */
#define IKP_CXP_BOARD_SYNC1_POLARITY (0x30000037)

/**
\~chinese
 * @brief CXP采集卡板间同步信号2极性
 * @note 本参数表示CXP采集卡板间同步信号2极性【RW】。
\~english
 * @brief CXP frame grabber board synchronous signal2 polarity
 * @note This parameter represents CXP frame grabber board synchronous signal2 polarity [RW].
 */
#define IKP_CXP_BOARD_SYNC2_POLARITY (0x30000038)

/**
\~chinese
 * @brief CXP采集卡板间同步信号1上升沿个数
 * @note 本参数表示CXP采集卡板间同步信号1上升沿个数【RW】。
\~english
 * @brief Number of board synchronous signal1 rising edge of CXP frame grabber
 * @note This parameter represents the number of board synchronous signal1 rising edge of CXP frame grabber [RW].
 */
#define IKP_CXP_BOARD_SYNC1_RISE_COUNT (0x30000039)

/**
\~chinese
 * @brief CXP采集卡板间同步信号1下降沿个数
 * @note 本参数表示CXP采集卡板间同步信号1下降沿个数【RW】。
\~english
 * @brief Number of board synchronous signal1 falling edge of CXP frame grabber
 * @note This parameter represents the number of board synchronous signal1 falling edge of CXP frame grabber [RW].
 */
#define IKP_CXP_BOARD_SYNC1_FALL_COUNT (0x3000003a)

/**
\~chinese
 * @brief CXP采集卡板间同步信号2上升沿个数
 * @note 本参数表示CXP采集卡板间同步信号2上升沿个数【RW】。
\~english
 * @brief Number of board synchronous signal2 rising edge of CXP frame grabber
 * @note This parameter represents the number of board synchronous signal2 rising edge of CXP frame grabber [RW].
 */
#define IKP_CXP_BOARD_SYNC2_RISE_COUNT (0x3000003b)

/**
\~chinese
 * @brief CXP采集卡板间同步信号2下降沿个数
 * @note 本参数表示CXP采集卡板间同步信号2下降沿个数【RW】。
\~english
 * @brief Number of board synchronous signal2 falling edge of CXP frame grabber
 * @note This parameter represents the number of board synchronous signal2 falling edge of CXP frame grabber [RW].
 */
#define IKP_CXP_BOARD_SYNC2_FALL_COUNT (0x3000003c)

/**
\~chinese
 * @brief CXP采集卡相机同步信号源
 * @note 本参数表示CXP采集卡相机同步信号源【RW】。
\~english
 * @brief CXP frame grabber camera synchronous signal source
 * @note This parameter represents CXP frame grabber camera synchronous signal source [RW].
 */
#define IKP_CXP_CAMERA_SYNC_TRIGGER_SOURCE (0x3000003d)

/**
\~chinese
 * @brief CXP采集卡相机同步信号通道
 * @note 本参数表示CXP采集卡相机同步信号通道【RW】。
\~english
 * @brief CXP frame grabber camera synchronous signal channel
 * @note This parameter represents CXP frame grabber camera synchronous signal channel [RW].
 */
#define IKP_CXP_CAMERA_SYNC_TRIGGER_SOURCE_CHANNEL (0x3000003e)

/**
\~chinese
 * @brief SFP采集卡中心线输出模式
 * @note 本参数表示SFP采集卡中心线输出模式【RW】。
\~english
 * @brief SFP frame grabber central line output mode
 * @note This parameter represents SFP frame grabber central line output mode [RW].
 */
#define IKP_SFP_ENABLE_CENTRAL_LINE_OUTPUT_MODE (0x3000003f)

/**
\~chinese
 * @brief
 * @note 。
\~english
 * @brief
 * @note .
 */
#define IKP_DEVICE_SLOT_INDEX (0x30000040)

/**
\~chinese
 * @brief GVB 使能SAccel压缩模式传输
 * @note 本参数表示 GVB 采集卡是否解码SAccel压缩传输的数据【RW】。
\~english
 * @brief GVB enable SAccel compression transfer
 * @note This parameter represents if GVB frame grabber decompress the SAccel compressed data that camera transfer[RW].
 */
#define IKP_GVB_ENABLE_COMPRESSION_TRANSFER (0x31000001)

/**
\~chinese
 * @brief GVB 使能重传包
 * @note 本参数表示 GVB 采集卡是否会在解析到错误数据时发送重传包【RW】。
\~english
 * @brief GVB enable packet resend
 * @note This parameter represents if GVB send the packet resend when packet is error[RW].
 */
#define IKP_GVB_ENABLE_PACKET_RESEND (0x31000002)

///@}

///@{
/**
\~chinese
 * @name 图像数据格式可选项
 * @see IKP_DATA_FORMAT
\~english
 * @name Image data format options
 * @see IKP_DATA_FORMAT
 */
#define IKP_DATA_FORMAT_VAL_8Bit  (8)   ///< \~chinese 8bit位深 \~english 8bit
#define IKP_DATA_FORMAT_VAL_10Bit (10)  ///< \~chinese 10bit位深 \~english 10bit
#define IKP_DATA_FORMAT_VAL_12Bit (12)  ///< \~chinese 12bit位深 \~english 12bit
#define IKP_DATA_FORMAT_VAL_14Bit (14)  ///< \~chinese 14bit位深 \~english 14bit
#define IKP_DATA_FORMAT_VAL_16Bit (16)  ///< \~chinese 16bit位深 \~english 16bit
///@}

///@{
/**
\~chinese
 * @name 图像类型可选项
 * @see IKP_IMAGE_TYPE
\~english
 * @name Image type options
 * @see IKP_IMAGE_TYPE
 */
#define IKP_IMAGE_TYPE_VAL_MONOCHROME (0)  ///< \~chinese 黑白图像 \~english Monochrome
#define IKP_IMAGE_TYPE_VAL_COLORFUL   (1)  ///< \~chinese Bayer图像 \~english Bayer
#define IKP_IMAGE_TYPE_VAL_RGB        (1)  ///< \~chinese 彩色RGB图像 \~english RGB
#define IKP_IMAGE_TYPE_VAL_RGBC                                                                                             \
    (2)  ///< \~chinese 彩色RGBC图像，其中C是图像的亮度信息 \~english RGBC, where C is grayscale information of image
#define IKP_IMAGE_TYPE_VAL_BGR (3)  ///< \~chinese 彩色BGR图像 \~english BGR
#define IKP_IMAGE_TYPE_VAL_BGRC                                                                                             \
    (4)  ///< \~chinese 彩色BGRC图像，其中C是图像的亮度信息 \~english BGRC, where C is grayscale information of image
#define IKP_IMAGE_TYPE_VAL_YUV422      (5)  ///< \~chinese YUV图像 \~english YUV
#define IKP_IMAGE_TYPE_VAL_YUV422_YUYV (5)  ///< \~chinese YUV图像YUYV排列 \~english YUYV
///@}

///@{
/**
\~chinese
 * @name 相机扫描类型可选项
 * @see IKP_SCAN_TYPE
\~english
 * @name Camera scan type options
 * @see IKP_SCAN_TYPE
 */
#define IKP_SCAN_TYPE_VAL_LINEAR (0)  ///< \~chinese 线扫描相机 \~english Line scan camera
#define IKP_SCAN_TYPE_VAL_AREA   (1)  ///< \~chinese 面扫描相机 \~english Area scan camera
///@}

///@{
/**
\~chinese
 * @name 图像序列采集模式可选项
 * @see IKP_GRAB_MODE
\~english
 * @name Image sequence acquisition mode options
 * @see IKP_GRAB_MODE
 */
#define IKP_GRAB_BLOCK                                                                                                      \
    (0)  ///< \~chinese IKapStartGrab将会阻塞直到所有图像传输完毕 \~english IKapStartGrab will block until all images have
         ///< been transmitted
#define IKP_GRAB_NON_BLOCK                                                                                                  \
    (1)  ///< \~chinese IKapStartGrab非阻塞式调用，不等待图像开始传输立即返回 \~english IKapStartGrab is a non blocking call
         ///< that returns immediately without waiting for image to start transmitting
///@}

///@{
/**
\~chinese
 * @name 图像缓冲区传输模式可选项
 * @see IKP_FRAME_TRANSFER_MODE
\~english
 * @name Image buffer transfer mode options
 * @see IKP_FRAME_TRANSFER_MODE
 */
#define IKP_FRAME_TRANSFER_SYNCHRONOUS  (0)  ///< \~chinese 同步传输模式 \~english Synchronous transmission mode
#define IKP_FRAME_TRANSFER_ASYNCHRONOUS (1)  ///< \~chinese 异步传输模式 \~english Asynchronous transmission mode
#define IKP_FRAME_TRANSFER_SYNCHRONOUS_NEXT_EMPTY_WITH_PROTECT                                                              \
    (2)  ///< \~chinese 同步保护传输模式 \~english Synchronous protection transmission mode
///@}

///@{
/**
\~chinese
 * @name 图像缓冲区自动清空机制可选项
 * @see IKP_FRAME_AUTO_CLEAR
\~english
 * @name Automatic clearing mechanism options for image buffer
 * @see IKP_FRAME_AUTO_CLEAR
 */
#define IKP_FRAME_AUTO_CLEAR_VAL_DISABLE (0)  ///< \~chinese 禁止自动清空机制 \~english Disable automatic clearing mechanism
#define IKP_FRAME_AUTO_CLEAR_VAL_ENABLE  (1)  ///< \~chinese 使能自动清空机制 \~english Enable automatic clearing mechanism
///@}

///@{
/**
\~chinese
 * @name Bayer图像解析模式可选项
 * @see IKP_BAYER_PATTERN
\~english
 * @name Bayer image pattern options
 * @see IKP_BAYER_PATTERN
 */
#define IKP_BAYER_PATTERN_VAL_NULL (0)  ///< \~chinese 非Bayer图像 \~english Non Bayer image
#define IKP_BAYER_PATTERN_VAL_BGGR                                                                                          \
    (1)  ///< \~chinese 图像左上角四个像素按照BGGR颜色方式排布 \~english The four pixels in the upper left corner of the
         ///< image are arranged according to the BGGR color scheme
#define IKP_BAYER_PATTERN_VAL_RGGB                                                                                          \
    (2)  ///< \~chinese 图像左上角四个像素按照RGGB颜色方式排布 \~english The four pixels in the upper left corner of the
         ///< image are arranged according to the RGGB color scheme
#define IKP_BAYER_PATTERN_VAL_GBRG                                                                                          \
    (3)  ///< \~chinese 图像左上角四个像素按照GBRG颜色方式排布 \~english The four pixels in the upper left corner of the
         ///< image are arranged according to the GBRG color scheme
#define IKP_BAYER_PATTERN_VAL_GRBG                                                                                          \
    (4)  ///< \~chinese 图像左上角四个像素按照GRBG颜色方式排布 \~english The four pixels in the upper left corner of the
         ///< image are arranged according to the GRBG color scheme
///@}

///@{
/**
\~chinese
 * @name CL采集卡CC<i>信号源可选项
 * @see IKP_CC1_SOURCE
 *      <br>IKP_CC2_SOURCE
 *      <br>IKP_CC3_SOURCE
 *      <br>IKP_CC4_SOURCE
\~english
 * @name CL frame grabber CC<i> signal source options
 * @see IKP_CC1_SOURCE
 *      <br>IKP_CC2_SOURCE
 *      <br>IKP_CC3_SOURCE
 *      <br>IKP_CC4_SOURCE
 */
#define IKP_CC_SOURCE_VAL_NOT_USE             (0)   ///< \~chinese 不使用CC<i>信信号 \~english Do not use CC<i> signal
#define IKP_CC_SOURCE_VAL_INTEGRATION_SIGNAL1 (1)   ///< \~chinese 积分信号1 \~english Integration signal1
#define IKP_CC_SOURCE_VAL_INTEGRATION_SIGNAL2 (2)   ///< \~chinese 积分信号2 \~english Integration signal2
#define IKP_CC_SOURCE_VAL_LOW                 (3)   ///< \~chinese 低电平信号 \~english Low level signal
#define IKP_CC_SOURCE_VAL_HIGH                (4)   ///< \~chinese 高电平信号 \~english High level signal
#define IKP_CC_SOURCE_VAL_SOFTWARE            (5)   ///< \~chinese 软件触发信号 \~english Software trigger signal
#define IKP_CC_SOURCE_VAL_GENERAL_INPUT1      (6)   ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_CC_SOURCE_VAL_GENERAL_INPUT2      (7)   ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_CC_SOURCE_VAL_BOARD_SYNC1         (8)   ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_CC_SOURCE_VAL_BOARD_SYNC2         (9)   ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
#define IKP_CC_SOURCE_VAL_STROBE              (10)  ///< \~chinese 闪光信号 \~english Strobe signal
#define IKP_CC_SOURCE_VAL_SHAFT_ENCODER_A                                                                                   \
    (11)  ///< \~chinese 编码器信号A(仅支持CC1和CC2)\~english SHAFT ENCODER A(Only support CC1 and CC2)
#define IKP_CC_SOURCE_VAL_SHAFT_ENCODER_B                                                                                   \
    (12)  ///< \~chinese 编码器信号B(仅支持CC1和CC2)\~english SHAFT ENCODER B(Only support CC1 and CC2)
///@}

///@{
/**
\~chinese
 * @name 采集卡触发模式可选项
 * @see IKP_BOARD_TRIGGER_MODE
\~english
 * @name Frame grabber trigger mode options
 * @see IKP_BOARD_TRIGGER_MODE
 */
#define IKP_BOARD_TRIGGER_MODE_VAL_INNER  (0)  ///< \~chinese 自由运行模式 \~english Free-run mode
#define IKP_BOARD_TRIGGER_MODE_VAL_OUTTER (1)  ///< \~chinese 外部触发模式 \~english External trigger mode
#define IKP_BOARD_TRIGGER_MODE_VAL_CXP_LEVEL_VALID                                                                          \
    (2)  ///< \~chinese CXP采集卡电平有效模式 \~english CXP frame grabber level effective mode
///@}

///@{
/**
\~chinese
 * @name 采集卡触发信号源可选项
 * @see IKP_BOARD_TRIGGER_SOURCE
\~english
 * @name Frame grabber trigger signal source options
 * @see IKP_BOARD_TRIGGER_SOURCE
 */
#define IKP_BOARD_TRIGGER_SOURCE_VAL_GENERAL_INPUT1       (0)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_BOARD_TRIGGER_SOURCE_VAL_GENERAL_INPUT2       (1)  ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_BOARD_TRIGGER_SOURCE_VAL_SHAFT_ENCODER1       (2)  ///< \~chinese 编码器信号 \~english Encoder signal
#define IKP_BOARD_TRIGGER_SOURCE_VAL_BOARD_SYNC1          (3)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_BOARD_TRIGGER_SOURCE_VAL_BOARD_SYNC2          (4)  ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
#define IKP_BOARD_TRIGGER_SOURCE_VAL_INNER_TRIGGER        (5)  ///< \~chinese 内部触发信号 \~english Internal trigger signal
#define IKP_BOARD_TRIGGER_SOURCE_VAL_SOFTWARE             (6)  ///< \~chinese 软件触发信号 \~english Software trigger signal
#define IKP_BOARD_TRIGGER_SOURCE_VAL_INTEGRATION_SIGNAL_1 (7)  ///< \~chinese 积分信号1 \~english Integration signal1
#define IKP_BOARD_TRIGGER_SOURCE_VAL_INTEGRATION_SIGNAL_2 (8)  ///< \~chinese 积分信号2 \~english Integration signal2
///@}

///@{
/**
\~chinese
 * @name CL采集卡通用输入信号采样模式可选项
 * @see IKP_GENERAL_INPUT1_SAMPLE_MODE
 *      <br>IKP_GENERAL_INPUT2_SAMPLE_MODE
\~english
 * @name CL frame grabber general input signal sampling mode options
 * @see IKP_GENERAL_INPUT1_SAMPLE_MODE
 *      <br>IKP_GENERAL_INPUT2_SAMPLE_MODE
 */
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_ACTIVE_HIGH  (0)  ///< \~chinese 高电平 \~english High level
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_ACTIVE_LOW   (1)  ///< \~chinese 低电平 \~english Low level
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_RISING_EDGE  (2)  ///< \~chinese 上升沿 \~english Rising edge
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_FALLING_EDGE (3)  ///< \~chinese 下降沿 \~english Falling edge
///@}

///@{
/**
\~chinese
 * @name CL采集卡通用输入信号脉冲保护模式可选项
 * @see IKP_GENERAL_INPUT1_PROTECT_MODE
 *      <br>IKP_GENERAL_INPUT2_PROTECT_MODE
\~english
 * @name CL frame grabber general input signal pulse protection mode options
 * @see IKP_GENERAL_INPUT1_PROTECT_MODE
 *      <br>IKP_GENERAL_INPUT2_PROTECT_MODE
 */
#define IKP_GENERAL_INPUT_PROTECT_MODE_VAL_NOT_USE  (0)  ///< \~chinese 不保护 \~english Not protecting
#define IKP_GENERAL_INPUT_PROTECT_MODE_VAL_DELETE   (1)  ///< \~chinese 删除 \~english Delete
#define IKP_GENERAL_INPUT_PROTECT_MODE_VAL_MEMORIZE (2)  ///< \~chinese 记录 \~english Memorize
///@}

///@{
/**
\~chinese
 * @name CL采集卡编码器脉冲保护模式可选项
 * @see IKP_SHAFT_ENCODER1_PROTECT_MODE
\~english
 * @name CL frame grabber encoder pulse protection mode options
 * @see IKP_SHAFT_ENCODER1_PROTECT_MODE
 */
#define IKP_SHAFT_ENCODER_PROTECT_MODE_VAL_NOT_USE  (0)  ///< \~chinese 不保护 \~english Not protecting
#define IKP_SHAFT_ENCODER_PROTECT_MODE_VAL_DELETE   (1)  ///< \~chinese 删除 \~english Delete
#define IKP_SHAFT_ENCODER_PROTECT_MODE_VAL_MEMORIZE (2)  ///< \~chinese 记录 \~english Memorize
///@}

///@{
/**
\~chinese
 * @name 积分控制方法触发信号源可选项
 * @see IKP_INTEGRATION_TRIGGER_SOURCE
\~english
 * @name Integration control method trigger signal source options
 * @see IKP_INTEGRATION_TRIGGER_SOURCE
 */
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_INTERNAL       (0)  ///< \~chinese 内部触发信号 \~english Internal trigger signal
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_GENERAL_INPUT1 (1)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_GENERAL_INPUT2 (2)  ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_SHAFT_ENCODER1 (5)  ///< \~chinese 编码器信号 \~english Encoder signal
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_BOARD_SYNC1    (7)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_BOARD_SYNC2    (8)  ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_SOFTWARE       (9)  ///< \~chinese 软件触发信号 \~english Software trigger signal
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_CAMERA_SYNC_TRIGGER                                                              \
    (10)  ///< \~chinese 相机同步信号 \~english Camera synchronous signal
///@}

///@{
/**
\~chinese
 * @name 闪光触发信号源可选项
 * @see IKP_STROBE_TRIGGER_SOURCE
\~english
 * @name Strobe trigger signal source options
 * @see IKP_STROBE_TRIGGER_SOURCE
 */
#define IKP_STROBE_TRIGGER_SOURCE_VAL_INTERNAL       (0)  ///< \~chinese 内部触发信号 \~english Internal trigger signal
#define IKP_STROBE_TRIGGER_SOURCE_VAL_GENERAL_INPUT1 (1)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_STROBE_TRIGGER_SOURCE_VAL_GENERAL_INPUT2 (2)  ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_STROBE_TRIGGER_SOURCE_VAL_SHAFT_ENCODER1 (5)  ///< \~chinese 编码器信号 \~english Encoder signal
#define IKP_STROBE_TRIGGER_SOURCE_VAL_BOARD_SYNC1    (7)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_STROBE_TRIGGER_SOURCE_VAL_BOARD_SYNC2    (8)  ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
#define IKP_STROBE_TRIGGER_SOURCE_VAL_FRAME_TRANSFER_END                                                                    \
    (9)  ///< \~chinese 帧传输结束信号 \~english Frame transmission end signal
#define IKP_STROBE_TRIGGER_SOURCE_VAL_SOFTWARE (10)  ///< \~chinese 软件触发信号 \~english Software trigger signal
#define IKP_STROBE_TRIGGER_SOURCE_VAL_FRAME_TRANSFER_START                                                                  \
    (11)  ///< \~chinese 帧传输开始信号 \~english Frame transmission start signal
#define IKP_STROBE_TRIGGER_SOURCE_VAL_FRAME_GRAB_START                                                                      \
    (12)  ///< \~chinese 帧采集开始信号 \~english Frame acquisition start signal
#define IKP_STROBE_TRIGGER_SOURCE_VAL_FRAME_GRAB_END                                                                        \
    (13)  ///< \~chinese 帧采集结束信号 \~english Frame acquisition end signal
///@}

///@{
/**
\~chinese
 * @name CL采集卡板间同步输出信号源可选项
 * @see IKP_BOARD_SYNC_OUTPUT1_SOURCE
 *      <br>IKP_BOARD_SYNC_OUTPUT2_SOURCE
\~english
 * @name CL frame grabber board synchronous output signal source options
 * @see IKP_BOARD_SYNC_OUTPUT1_SOURCE
 *      <br>IKP_BOARD_SYNC_OUTPUT2_SOURCE
 */
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_NOT_USE             (0)  ///< \~chinese 不使用 \~english Not use
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_INTERNAL            (1)  ///< \~chinese 内部触发信号 \~english Internal trigger signal
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_GENERAL_INPUT1      (2)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_GENERAL_INPUT2      (3)  ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_SHAFT_ENCODER1      (4)  ///< \~chinese 编码器信号 \~english Encoder signal
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL1 (5)  ///< \~chinese 积分信号1 \~english Integration signal1
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL2 (6)  ///< \~chinese 积分信号2 \~english Integration signal2
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_STROBLE_SIGNAL1     (7)  ///< \~chinese 闪光信号 \~english Strobe signal
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_BOARD_SYNC1         (8)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_BOARD_SYNC2         (9)  ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
///@}

///@{
/**
\~chinese
 * @name 通用输出信号源可选项
 * @see IKP_GENERAL_OUTPUT1_SOURCE
 *      <br>IKP_GENERAL_OUTPUT2_SOURCE
\~english
 * @name General output signal source options
 * @see IKP_GENERAL_OUTPUT1_SOURCE
 *      <br>IKP_GENERAL_OUTPUT2_SOURCE
 */
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_INTERNAL            (0)  ///< \~chinese 内部触发信号 \~english Internal trigger signal
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_GENERAL_INPUT1      (1)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_GENERAL_INPUT2      (2)  ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_SHAFT_ENCODER1      (3)  ///< \~chinese 编码器信号 \~english Encoder signal
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL1 (4)  ///< \~chinese 积分信号1 \~english Integration signal1
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL2 (5)  ///< \~chinese 积分信号2 \~english Integration signal2
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_STROBLE_SIGNAL1     (6)  ///< \~chinese 闪光信号 \~english Strobe signal
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_SOFTWARE            (7)  ///< \~chinese 软件触发信号 \~english Software trigger signal
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_VAL_BOARD_SYNC1     (8)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_VAL_BOARD_SYNC2     (9)  ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
///@}

///@{
/**
\~chinese
 * @name 通用输出信号极性可选项
 * @see IKP_GENERAL_OUTPUT1_POLARITY
 *      <br>IKP_GENERAL_OUTPUT2_POLARITY
\~english
 * @name General output signal polarity options
 * @see IKP_GENERAL_OUTPUT1_POLARITY
 *      <br>IKP_GENERAL_OUTPUT2_POLARITY
 */
#define IKP_GENERAL_OUTPUT_POLARITY_VAL_SAME_TO_SOURCE (0)  ///< \~chinese 与原信号极性相同 \~english Same as original signal
#define IKP_GENERAL_OUTPUT_POLARITY_VAL_OPPOSITE_TO_SOURCE                                                                  \
    (1)  ///< \~chinese 与原信号极性相反 \~english Opposite to original signal
///@}

///@{
/**
\~chinese
 * @name 积分控制方法可选项
 * @see IKP_INTEGRATION_METHOD
\~english
 * @name Integration control method options
 * @see IKP_INTEGRATION_METHOD
 */
#define IKP_INTEGRATION_METHOD_VAL_1 (0)  ///< \~chinese 积分控制方法1 \~english Integration control method1
#define IKP_INTEGRATION_METHOD_VAL_2 (1)  ///< \~chinese 积分控制方法2 \~english Integration control method2
#define IKP_INTEGRATION_METHOD_VAL_3 (2)  ///< \~chinese 积分控制方法3 \~english Integration control method3
#define IKP_INTEGRATION_METHOD_VAL_4 (3)  ///< \~chinese 积分控制方法4 \~english Integration control method4
#define IKP_INTEGRATION_METHOD_VAL_5 (4)  ///< \~chinese 积分控制方法5 \~english Integration control method5
///@}

///@{
/**
\~chinese
 * @name 积分信号极性可选项
 * @see IKP_INTEGRATION_POLARITY1
 *      <br>IKP_INTEGRATION_POLARITY2
\~english
 * @name Integration signal polarity options
 * @see IKP_INTEGRATION_POLARITY1
 *      <br>IKP_INTEGRATION_POLARITY2
 */
#define IKP_INTEGRATION_POLARITY_VAL_HIGH (0)  ///< \~chinese 高电平 \~english High level
#define IKP_INTEGRATION_POLARITY_VAL_LOW  (1)  ///< \~chinese 低电平 \~english Low level
///@}

///@{
/**
\~chinese
 * @name 闪光控制方法可选项
 * @see IKP_STROBE_METHOD
\~english
 * @name Strobe control method options
 * @see IKP_STROBE_METHOD
 */
#define IKP_STROBE_METHOD_VAL_1 (0)  ///< \~chinese 闪光控制方法1 \~english Strobe control method1
#define IKP_STROBE_METHOD_VAL_2 (1)  ///< \~chinese 闪光控制方法2 \~english Strobe control method2
#define IKP_STROBE_METHOD_VAL_3 (2)  ///< \~chinese 闪光控制方法3 \~english Strobe control method3
#define IKP_STROBE_METHOD_VAL_4 (3)  ///< \~chinese 闪光控制方法4 \~english Strobe control method4
///@}

///@{
/**
\~chinese
 * @name 闪光信号极性可选项
 * @see IKP_STROBE_POLARITY
\~english
 * @name Strobe signal polarity options
 * @see IKP_STROBE_POLARITY
 */
#define IKP_STROBE_POLARITY_VAL_HIGH (0)  ///< \~chinese 高电平 \~english High level
#define IKP_STROBE_POLARITY_VAL_LOW  (1)  ///< \~chinese 低电平 \~english Low level
///@}

///@{
/**
\~chinese
 * @name 通用输入信号触发模式可选项
 * @see IKP_GENERAL_INPUT1_TRIGGER_MODE
 *      <br>IKP_GENERAL_INPUT2_TRIGGER_MODE
\~english
 * @name General input signal trigger mode options
 * @see IKP_GENERAL_INPUT1_TRIGGER_MODE
 *      <br>IKP_GENERAL_INPUT2_TRIGGER_MODE
 */
#define IKP_GENERAL_INPUT_TRIGGER_MODE_VAL_EDGE  (0)  ///< \~chinese 边沿触发 \~english Edge sensitive
#define IKP_GENERAL_INPUT_TRIGGER_MODE_VAL_LEVEL (1)  ///< \~chinese 电平触发 \~english Level sensitive
///@}

///@{
/**
\~chinese
 * @name CL采集卡板间同步信号触发模式可选项
 * @see IKP_BOARD_SYNC1_TRIGGER_MODE
 *      <br>IKP_BOARD_SYNC2_TRIGGER_MODE
\~english
 * @name CL frame grabber board synchronous signal trigger mode options
 * @see IKP_BOARD_SYNC1_TRIGGER_MODE
 *      <br>IKP_BOARD_SYNC2_TRIGGER_MODE
 */
#define IKP_BOARD_SYNC_TRIGGER_MODE_VAL_EDGE  (0)  ///< \~chinese 边沿触发 \~english Edge sensitive
#define IKP_BOARD_SYNC_TRIGGER_MODE_VAL_LEVEL (1)  ///< \~chinese 电平触发 \~english Level sensitive
///@}

///@{
/**
\~chinese
 * @name 编码器A/B通道选择可选项
 * @see IKP_SHAFT_ENCODER1_CHANNEL
\~english
 * @name Encoder A/B channel selection options
 * @see IKP_SHAFT_ENCODER1_CHANNEL
 */
#define IKP_SHAFT_ENCODER_CHANNEL_VAL_A (0)  ///< \~chinese A通道 \~english A channel
#define IKP_SHAFT_ENCODER_CHANNLE_VAL_B (1)  ///< \~chinese B通道 \~english B channel
///@}

///@{
/**
\~chinese
 * @name 编码器信号倍频系数可选项
 * @see IKP_SHAFT_ENCODER1_MULTIPLY_FACTOR
\~english
 * @name Encoder signal multiple factor options
 * @see IKP_SHAFT_ENCODER1_MULTIPLY_FACTOR
 */
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_1   (0)  ///< \~chinese 1倍频 \~english x1
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_2   (1)  ///< \~chinese 2倍频 \~english x2
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_4   (2)  ///< \~chinese 4倍频 \~english x4
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_8   (3)  ///< \~chinese 8倍频 \~english x8
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_16  (4)  ///< \~chinese 16倍频 \~english x16
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_32  (5)  ///< \~chinese 32倍频 \~english x32
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_64  (6)  ///< \~chinese 64倍频 \~english x64
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_128 (7)  ///< \~chinese 128倍频 \~english x128
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_256 (8)  ///< \~chinese 256倍频 \~english x256
#define IKP_SHAFT_ENCODER_MULTIPLY_FACTOR_VAL_512 (9)  ///< \~chinese 512倍频 \~english x512
///@}

///@{
/**
\~chinese
 * @name CL采集卡LVAL滤波控制可选项
 * @see IKP_LVAL_FILTER
\~english
 * @name CL frame grabber LVAL filtering control options
 * @see IKP_LVAL_FILTER
 */
#define IKP_LVAL_FILTER_DISABLE (0)  ///< \~chinese 禁用 \~english Disable
#define IKP_LVAL_FILTER_ENABLE  (1)  ///< \~chinese 使能 \~english Enable
///@}

///@{
/**
\~chinese
 * @name CL采集卡外触发超时系数可选项
 * @see IKP_FPGA_EXTERNAL_TRIGGER_TIMEOUT
\~english
 * @name CL frame grabber external trigger timeout coefficient options
 * @see IKP_FPGA_EXTERNAL_TRIGGER_TIMEOUT
 */
#define IKP_FPGA_EXTERNAL_TRIGGER_TIMEOUT_MIN (8)           ///< \~chinese 最小超时时间 \~english Minimum timeout time
#define IKP_FPGA_EXTERNAL_TRIGGER_TIMEOUT_MAX (0xFFFFFFFF)  ///< \~chinese 最大超时时间 \~english Maximum timeout time
///@}

///@{
/**
\~chinese
 * @name 通用输入信号极性可选项
 * @see IKP_GENERAL_INPUT1_POLARITY
 *      <br>IKP_GENERAL_INPUT2_POLARITY
\~english
 * @name General input signal polarity options
 * @see IKP_GENERAL_INPUT1_POLARITY
 *      <br>IKP_GENERAL_INPUT2_POLARITY
 */
#define IKP_GENERAL_INPUT_POLARITY_VAL_HIGH (0)  ///< \~chinese 高电平/上升沿 \~english High level/Rising edge
#define IKP_GENERAL_INPUT_POLARITY_VAL_LOW  (1)  ///< \~chinese 低电平/下降沿 \~english Low level/Falling edge
///@}

///@{
/**
\~chinese
 * @name 通用输入信号最小脉冲宽度可选项
 * @see IKP_GENERAL_INPUT1_MIN_WIDTH
 *      <br>IKP_GENERAL_INPUT2_MIN_WIDTH
\~english
 * @name General input signal minimum pulse width options
 * @see IKP_GENERAL_INPUT1_MIN_WIDTH
 *      <br>IKP_GENERAL_INPUT2_MIN_WIDTH
 */
#define IKP_GENERAL_INPUT_MIN_WIDTH_VAL_MINIMUM (50)  ///< \~chinese 最小脉冲宽度 \~english Minimum pulse width
///@}

///@{
/**
\~chinese
 * @name CL采集卡PCIe内部缓冲区块大小可选项
 * @see IKP_PCIE_KERNAL_BLOCK_SIZE
\~english
 * @name CL frame grabber PCIe internal buffer block size options
 * @see IKP_PCIE_KERNAL_BLOCK_SIZE
 */
#define IKP_PCIE_KERNAL_BLOCK_SIZE_VAL_1M  (0)  ///< \~chinese 1MB \~english 1MB
#define IKP_PCIE_KERNAL_BLOCK_SIZE_VAL_4M  (1)  ///< \~chinese 4MB \~english 4MB
#define IKP_PCIE_KERNAL_BLOCK_SIZE_VAL_8M  (2)  ///< \~chinese 8MB \~english 8MB
#define IKP_PCIE_KERNAL_BLOCK_SIZE_VAL_12M (3)  ///< \~chinese 12MB \~english 12MB
#define IKP_PCIE_KERNAL_BLOCK_SIZE_VAL_16M (4)  ///< \~chinese 16MB \~english 16MB
///@}

///@{
/**
\~chinese
 * @name 软件触发极性可选项
 * @see IKP_SOFTWARE_TRIGGER_POLARITY
\~english
 * @name Software trigger polarity options
 * @see IKP_SOFTWARE_TRIGGER_POLARITY
 */
#define IKP_SOFTWARE_TRIGGER_POLARITY_VAL_HIGH                                                                              \
    (0)  ///< \~chinese 默认低电平，有效时为高电平 \~english Default low level, high level when valid
#define IKP_SOFTWARE_TRIGGER_POLARITY_VAL_LOW                                                                               \
    (1)  ///< \~chinese 默认高电平，有效时为低电平 \~english Default high level, low level when valid
///@}

///@{
/**
\~chinese
 * @name 软件触发同步模式可选项
 * @see IKP_SOFTWARE_TRIGGER_SYNC_MODE
\~english
 * @name Software trigger synchronous mode options
 * @see IKP_SOFTWARE_TRIGGER_SYNC_MODE
 */
#define IKP_SOFTWARE_TRIGGER_SYNC_MODE_VAL_DISABLE                                                                          \
    (0)  ///< \~chinese 禁用，此时软件触发信号周期由软件触发脉冲周期参数控制 \~english Disabled. At this time, software
         ///< trigger signal period is controlled by software trigger pulse period parameter
#define IKP_SOFTWARE_TRIGGER_SYNC_MODE_VAL_ENABLE                                                                           \
    (1)  ///< \~chinese
         ///< 使能，此时软件触发信号周期由相机帧率决定，每当相机输出完整一帧图像后，应用程序会立即产生一个软件触发信号，使相机继续产生下一帧图像
         ///< \~english Enable. At this time, software trigger signal period is determined by camera frame rate. Whenever
         ///< camera outputs a complete frame of image, application will immediately generate a software trigger signal,
         ///< causing camera to continue generating the next frame of image
///@}

///@{
/**
\~chinese
 * @name CXP采集卡触发输出选择可选项
 * @see IKP_CXP_TRIGGER_OUTPUT_SELECTOR
\~english
 * @name CXP frame grabber trigger output selection options
 * @see IKP_CXP_TRIGGER_OUTPUT_SELECTOR
 */
#define IKP_CXP_TRIGGER_OUTPUT_NO                  (0)  ///< \~chinese 关闭输出功能 \~english Off output function
#define IKP_CXP_TRIGGER_OUTPUT_INTEGRATION_SIGNAL1 (1)  ///< \~chinese 积分信号1 \~english Integration signal1
#define IKP_CXP_TRIGGER_OUTPUT_INTEGRATION_SIGNAL2 (2)  ///< \~chinese 积分信号2 \~english Integration signal2
#define IKP_CXP_TRIGGER_OUTPUT_BOARD_SYNC1         (3)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_CXP_TRIGGER_OUTPUT_BOARD_SYNC2         (4)  ///< \~chinese 板间同步信号2 \~english Board synchronous signal2
///@}

///@{
/**
\~chinese
 * @name IO事件可选项
 * @see IKP_DISABLE_IO_EVENT
\~english
 * @name IO event options
 * @see IKP_DISABLE_IO_EVENT
 */
#define IKP_EVENT_INPUT_INTERNAL          (1 << 0)  ///< \~chinese 内部信号 \~english Internal signal
#define IKP_EVENT_INPUT_GENERAL_1         (1 << 1)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_EVENT_INPUT_GENERAL_2         (1 << 2)  ///< \~chinese 通用输入信号2 \~english General input signal2
#define IKP_EVENT_INPUT_SHAFT_ENCODER_A   (1 << 3)  ///< \~chinese 编码器A通道信号 \~english Encoder A channel signal
#define IKP_EVENT_INPUT_SHFAT_ENCODER_B   (1 << 4)  ///< \~chinese 编码器B通道信号 \~english Encoder B channel signal
#define IKP_EVENT_INPUT_BOARD_SYNC_IN_1   (1 << 5)  ///< \~chinese 板间同步信号1 \~english Board synchronous signal1
#define IKP_EVENT_INPUT_INTEGRATION_SIG_1 (1 << 6)  ///< \~chinese 积分信号1 \~english Integration signal1
#define IKP_EVENT_INPUT_INTEGRATION_SIG_2 (1 << 7)  ///< \~chinese 积分信号2 \~english Integration signal2
///@}

///@{
/**
\~chinese
 * @name CXP采集卡测试图像可选项
 * @see IKP_CXP_TEST_IMAGE
  * @name CXP frame grabber test image options
 * @see IKP_CXP_TEST_IMAGE
\~english
 */
#define IKP_CXP_TEST_IMAGE_OFF (0)  ///< \~chinese 关闭测试图像 \~english Turn off test image
#define IKP_CXP_TEST_IMAGE_1   (1)  ///< \~chinese 测试图像1 \~english Test image1
#define IKP_CXP_TEST_IMAGE_2   (2)  ///< \~chinese 测试图像2 \~english Test image2
///@}

///@{
/**
\~chinese
 * @name 编码器信号有效方向可选项
 * @see IKP_SHAFT_ENCODER1_VALID_DIRECTION
\~english
 * @name Encoder signal effective direction options
 * @see IKP_SHAFT_ENCODER1_VALID_DIRECTION
 */
#define IKP_SHAFT_ENCODER1_VALID_DIR_BOTH                                                                                   \
    (0)  ///< \~chinese 正向或反向均视为有效信号 \~english Both forward and backward directions are considered valid signals
#define IKP_SHAFT_ENCODER1_VALID_DIR_FORWARD                                                                                \
    (1)  ///< \~chinese 正向视为有效信号 \~english Forward is considered as a valid signal
#define IKP_SHAFT_ENCODER1_VALID_DIR_BACKWARD                                                                               \
    (2)  ///< \~chinese 反向视为有效信号 \~english Backward is considered as a valid signal
///@}

///@{
/**
\~chinese
 * @name 编码器信号反转补偿功能可选项
 * @see IKP_SHAFT_ENCODER1_REVERSE_COMPENSATION
\~english
 * @name Encoder signal reverse compensation function options
 * @see IKP_SHAFT_ENCODER1_REVERSE_COMPENSATION
 */
#define IKP_SHAFT_ENCODER1_REVERSE_COMPENSATION_OFF (0)  ///< \~chinese 禁用 \~english Disable
#define IKP_SHAFT_ENCODER1_REVERSE_COMPENSATION_ON  (1)  ///< \~chinese 使能 \~english Enable
///@}

///@{
/**
\~chinese
 * @name CXP采集卡编码器输入信号去抖窗口长度可选项
 * @see IKP_CXP_SHAFT_ENCODER_DEBOUNCE
\~english
 * @name CXP frame grabber encoder input signal debounce window length options
 * @see IKP_CXP_SHAFT_ENCODER_DEBOUNCE
 */
#define IKP_CXP_SHAFT_ENCODER1_DEBOUNCE_PERIOD_MIN                                                                          \
    (0)  ///< \~chinese 最小去抖窗口长度 \~english Minimum debounce window length
#define IKP_CXP_SHAFT_ENCODER1_DEBOUNCE_PERIOD_MAX                                                                          \
    (65535)  ///< \~chinese 最大去抖窗口长度 \~english Maximum debounce window length
///@}

///@{
/**
\~chinese
 * @name CXP采集卡编码器计数器模式可选项
 * @see IKP_CXP_SHAFT_ENCODER_TICK_MODE
\~english
 * @name CXP frame grabber encoder counter mode options
 * @see IKP_CXP_SHAFT_ENCODER_TICK_MODE
 */
#define IKP_CXP_SHAFT_ENCODER_TICK_MODE_FOLLOW_DIRECTION                                                                    \
    (0)  ///< \~chinese 正向递增反向递减 \~english Forward increasing and backward decreasing
#define IKP_CXP_SHAFT_ENCODER_TICK_MODE_ANY_DIRECTION                                                                       \
    (1)  ///< \~chinese 任意方向均递增 \~english Increasing in any direction
///@}

///@{
/**
\~chinese
 * @name CXP采集卡固件类型可选项
 * @see IKP_CXP_FIRMWARE_TYPE
\~english
 * @name CXP frame grabber firmware type options
 * @see IKP_CXP_FIRMWARE_TYPE
 */
#define IKP_CXP_FIRMWARE_TYPE_1_CAMERA     (0)  ///< \~chinese 1拖1 \~english 1-1
#define IKP_CXP_FIRMWARE_TYPE_2_CAMERA     (1)  ///< \~chinese 1拖2 \~english 1-2
#define IKP_CXP_FIRMWARE_TYPE_4_CAMERA     (2)  ///< \~chinese 1拖4 \~english 1-4
#define IKP_CXP_FIRMWARE_TYPE_2_CAMERA_NEW (3)
#define IKP_CXP_FIRMWARE_TYPE_8_CAMERA     (7)  ///< \~chinese 1拖8 \~english 1-8
///@}

///@{
/**
\~chinese
 * @name CXP采集卡通用输出信号通道可选项
 * @see IKP_CXP_GENERAL_OUTPUT1_SOURCE_CHANNEL
 *      <br>IKP_CXP_GENERAL_OUTPUT2_SOURCE_CHANNEL
\~english
 * @name CXP frame grabber general output signal channel options
 * @see IKP_CXP_GENERAL_OUTPUT1_SOURCE_CHANNEL
 *      <br>IKP_CXP_GENERAL_OUTPUT2_SOURCE_CHANNEL
 */
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_A (0)  ///< \~chinese 通道A \~english A channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_B (1)  ///< \~chinese 通道B \~english B channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_C (2)  ///< \~chinese 通道C \~english C channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_D (3)  ///< \~chinese 通道D \~english D channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_E (4)  ///< \~chinese 通道E \~english E channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_F (5)  ///< \~chinese 通道F \~english F channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_G (6)  ///< \~chinese 通道G \~english G channel
#define IKP_CXP_GENERAL_OUTPUT_SOURCE_CHANNEL_H (7)  ///< \~chinese 通道H \~english H channel
///@}

///@{
/**
\~chinese
 * @name CXP采集卡通用输入信号类型可选项
 * @see IKP_CXP_GENERAL_INPUT1_TYPE
 *      <br>IKP_CXP_GENERAL_INPUT2_TYPE
\~english
 * @name CXP frame grabber general input signal type options
 * @see IKP_CXP_GENERAL_INPUT1_TYPE
 *      <br>IKP_CXP_GENERAL_INPUT2_TYPE
 */
#define IKP_CXP_GENERAL_INPUT_TYPE_DIFFERENTIAL (0)  ///< \~chinese 差分 \~english Differential
#define IKP_CXP_GENERAL_INPUT_TYPE_SINGLE_END   (1)  ///< \~chinese 单端 \~english Single ended
///@}

///@{
/**
\~chinese
 * @name CL采集卡有效列可选项
 * @see IKP_CL_VALID_COLUMN
\~english
 * @name CL frame grabber valid column options
 * @see IKP_CL_VALID_COLUMN
 */
#define IKP_CL_VALID_COLUMN_ALL  (0)  ///< \~chinese 所有列 \~english All columns
#define IKP_CL_VALID_COLUMN_EVEN (1)  ///< \~chinese 偶数列 \~english Even columns
#define IKP_CL_VALID_COLUMN_ODD  (2)  ///< \~chinese 奇数列 \~english Odd columns
///@}

///@{
/**
\~chinese
 * @name CL采集卡有效列可选项
 * @see IKP_CL_VALID_COLUMN
\~english
 * @name CL frame grabber valid column options
 * @see IKP_CL_VALID_COLUMN
 */
#define IKP_CL_SIGNAL_ENHANCE_MODE_OFF (0)  ///< \~chinese 关闭 \~english Off
#define IKP_CL_SIGNAL_ENHANCE_MODE_ON  (3)  ///< \~chinese 开启 \~english On
///@}

///@{
/**
\~chinese
 * @name CL采集卡远距离传输功能可选项
 * @see IKP_CL_LONG_DISTANCE_TRANSMISSION
\~english
 * @name CL frame grabber long distance transmission function options
 * @see IKP_CL_LONG_DISTANCE_TRANSMISSION
 */
#define IKP_CL_LONG_DISTANCE_TRANSMISSION_OFF                                                                               \
    (0)  ///< \~chinese 传输线缆小于等于7米时关闭该功能 \~english When transmission cable is less than or equal to 7 meters,
         ///< turn off this function
#define IKP_CL_LONG_DISTANCE_TRANSMISSION_ON                                                                                \
    (1)  ///< \~chinese 传输线缆大于7米时开启该功能 \~english When transmission cable is longer than 7 meters, turn on this
         ///< function
///@}

#define IKP_CXP_UART_PORT (8)  ///< \~chinese CXP采集卡串口索引 \~english CXP frame grabber serial port index

///@{
/**
\~chinese
 * @name 图像压缩标志可选项
 * @see IKapSaveBuffer
\~english
 * @name Image compression flag options
 * @see IKapSaveBuffer
 */
#define IKP_DEFAULT_COMPRESSION (0x0000)  ///< \~chinese 默认压缩 \~english Default compression
#define IKP_JPEG_QUALITYSUPERB                                                                                              \
    (0x0001)  ///< \~chinese 保存为高品质jpeg图像（100:1） \~english Save as superb quality jpeg image（100:1）
#define IKP_JPEG_QUALITYGOOD                                                                                                \
    (0x0002)  ///< \~chinese 保存为好品质jpeg图像（75:1） \~english Save as good quality jpeg image（75:1）
#define IKP_JPEG_QUALITYNORMAL                                                                                              \
    (0x0003)  ///< \~chinese 保存为普通品质jpeg图像（50:1） \~english Save as normal quality jpeg image（50:1）
#define IKP_JPEG_QUALITYAVERAGE                                                                                             \
    (0x0004)  ///< \~chinese 保存为平均品质jpeg图像（25:1） \~english Save as average quality jpeg image（25:1）
#define IKP_JPEG_QUALITYBAD                                                                                                 \
    (0x0005)  ///< \~chinese 保存为低品质jpeg图像（10:1） \~english Save as bad quality jpeg image（10:1）
#define IKP_TIFF_NONE (0x0100)  ///< \~chinese 保存为无压缩tiff图像 \~english Save as uncompressed tiff image
#define IKP_TIFF_LZW  (0x0101)  ///< \~chinese 保存为LZW压缩tiff图像 \~english Save as LZW compressed tiff image
#define IKP_PNG_Z_NO_COMPRESSION                                                                                            \
    (0x0200)  ///< \~chinese 保存为无zlib压缩png图像 \~english Save as compressed png image without zlib
#define IKP_PNG_Z_BEST_SPEED                                                                                                \
    (0x0201)  ///< \~chinese 保存为zlib第1级压缩png图像（默认值为6） \~english Save as zlib level 1 compressed png image
              ///< (default value is 6)
#define IKP_PNG_Z_DEFAULT_COMPRESSION                                                                                       \
    (0x0202)  ///< \~chinese 保存为zlib第6级压缩png图像（默认推荐值） \~english Save as zlib level 6 compressed png image
              ///< (default value is commended value)
#define IKP_PNG_Z_BEST_COMPRESSION                                                                                          \
    (0x0203)  ///< \~chinese 保存为zlib第9级压缩png图像（默认值为6） \~english Save as zlib level 9 compressed png image
              ///< (default value is 6)
///@}

///@{
/**
\~chinese
 * @name CXP采集卡通用输出信号阈值可选项
 * @see IKP_CXP_GENERAL_OUTPUT1_THRESHOLD
 *      <br>IKP_CXP_GENERAL_OUTPUT2_THRESHOLD
\~english
 * @name CXP frame grabber general output signal threshold options
 * @see IKP_CXP_GENERAL_OUTPUT1_THRESHOLD
 *      <br>IKP_CXP_GENERAL_OUTPUT2_THRESHOLD
 */
#define IKP_GENERAL_OUTPUT_THRESHOLD_3V3 (0x0)  ///< \~chinese 3.3V \~english 3.3V
#define IKP_GENERAL_OUTPUT_THRESHOLD_24V (0x1)  ///< \~chinese 24V \~english 24V
///@}

///@{
/**
\~chinese
 * @name 编码器输入信号去抖窗口长度可选项
 * @see IKP_CXP_SHAFT_ENCODER_DEBOUNCE
\~english
 * @name Encoder input signal debounce window length options
 * @see IKP_CXP_SHAFT_ENCODER_DEBOUNCE
 */
#define IKP_SHAFT_ENCODER_DEBOUNCE_MIN (0)  ///< \~chinese 最小去抖窗口长度 \~english Minimum debounce window length
#define IKP_SHAFT_ENCODER_DEBOUNCE_MAX                                                                                      \
    (1000 * 1000 * 1000)  ///< \~chinese 最大去抖窗口长度 \~english Maximum debounce window length
///@}

///@{
/**
\~chinese
 * @name CXP采集卡通用输入信号阈值可选项
 * @see IKP_CXP_GENERAL_INPUT_THRESHOLD
\~english
 * @name CXP frame grabber general input signal threshold options
 * @see IKP_CXP_GENERAL_INPUT_THRESHOLD
 */
#define IKP_CXP_GENERAL_INPUT_THRESHOLD_5V (0)  ///< \~chinese 5V \~english 5V
#define IKP_CXP_GENERAL_INPUT_THRESHOLD_3V (1)  ///< \~chinese 3V \~english 3V
///@}

///@{
/**
\~chinese
 * @name CL采集卡通用输入信号延迟模式可选项
 * @see IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_MODE
\~english
 * @name CL frame grabber general input signal delay mode options
 * @see IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_MODE
 */
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_MODE_IN_LINES (0)  ///< \~chinese 行延迟 \~english Line delay
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_MODE_IN_US    (1)  ///< \~chinese 时间延迟 \~english Time delay

#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_IN_LINES_MIN (0)  ///< \~chinese 最小延迟行数 \~english Minimum delay lines
#define IKP_HARDWARE_TRIGGER_GENERAL_INPUT_DELAY_IN_LINES_MAX                                                               \
    (65535)  ///< \~chinese 最大延迟行数 \~english Maximum delay lines
///@}

///@{
/**
\~chinese
 * @name CL采集卡编码器4倍频以上信号来源可选项
 * @see IKP_SHAFT_ENCODER1_QUAD_FREQUENCY_SOURCE_TYPE
\~english
 * @name CL frame grabber encoder 4 times or more signal source options
 * @see IKP_SHAFT_ENCODER1_QUAD_FREQUENCY_SOURCE_TYPE
 */
#define IKP_SHAFT_ENCODER1_QUAD_FREQUENCY_SOURCE_TYPE_VAL_DOUBLE_CHANNEL (0)  ///< \~chinese 双通道 \~english Double channel
#define IKP_SHAFT_ENCODER1_QUAD_FREQUENCY_SOURCE_TYPE_VAL_SINGLE_CHANNEL (1)  ///< \~chinese 单通道 \~english Single channel
///@}

///@{
/**
\~chinese
 * @name 不定长采集模式可选项
 * @see IKP_TRIGGER_FRAME_ACTIVE_MODE
\~english
 * @name Frame active acquisition mode options
 * @see IKP_TRIGGER_FRAME_ACTIVE_MODE
 */
#define IKP_TRIGGER_FRAME_ACTIVE_MODE_OFF        (0)  ///< \~chinese 关闭 \~english Off
#define IKP_TRIGGER_FRAME_ACTIVE_MODE_ON         (1)  ///< \~chinese 开启 \~english On
#define IKP_TRIGGER_FRAME_ACTIVE_MODE_ALL_LEVELS (2)  ///< \~chinese all_levels模式 \~english all_levels mode
///@}

///@{
/**
\~chinese
 * @name JPEG压缩模式可选项
 * @see IKP_JPEG_COMPRESS_ENABLE
\~english
 * @name JPEG compression mode options
 * @see IKP_JPEG_COMPRESS_ENABLE
 */
#define IKP_JPEG_COMPRESS_ENABLE_OFF  (0)    ///< \~chinese 关闭 \~english Off
#define IKP_JPEG_COMPRESS_ENABLE_ON   (1)    ///< \~chinese 开启 \~english On
#define IKP_JPEG_COMPRESS_QUALITY_MIN (1)    ///< \~chinese 最低质量系数 \~english Minimum quality coefficient
#define IKP_JPEG_COMPRESS_QUALITY_MAX (100)  ///< \~chinese 最高质量系数 \~english Maximum quality coefficient
///@}

///@{
/**
\~chinese
 * @name 编码器信号占空比补偿功能类型可选项
 * @see IKP_SHAFT_ENCODER1_CLOCK_DUTY_COMPENSATION_TYPE
\~english
 * @name Encoder signal duty cycle compensation function type options
 * @see IKP_SHAFT_ENCODER1_CLOCK_DUTY_COMPENSATION_TYPE
 */
#define IKP_SHAFT_ENCODER1_CLOCK_DUTY_COMPENSATION_RISING_EDGE  (0)  ///< \~chinese 上升沿 \~english Rising edge
#define IKP_SHAFT_ENCODER1_CLOCK_DUTY_COMPENSATION_FALLING_EDGE (1)  ///< \~chinese 下降沿 \~english Falling edge
///@}

///@{
/**
\~chinese
 * @name CXP采集卡编码器工作模式可选项
 * @see IKP_CXP_SHAFT_ENCODER_REVERSE_MODE
\~english
 * @name CXP frame grabber encoder working mode options
 * @see IKP_CXP_SHAFT_ENCODER_REVERSE_MODE
 */
#define IKP_CXP_SHAFT_ENCODER_REVERSE_MODE_FORWARD_ONLY  (0)  ///< \~chinese 仅正向 \~english Only forward
#define IKP_CXP_SHAFT_ENCODER_REVERSE_MODE_ANY_DIRECTION (1)  ///< \~chinese 任意方向 \~english Any direction
#define IKP_CXP_SHAFT_ENCODER_REVERSE_MODE_BACKWARD_ONLY (2)  ///< \~chinese 仅反向 \~english Only backward
///@}

///@{
/**
\~chinese
 * @name CXP采集卡边沿触发模式可选项
 * @see IKP_CXP_TRIG_EDGE_MODE
\~english
 * @name CXP frame grabber edge trigger mode options
 * @see IKP_CXP_TRIG_EDGE_MODE
 */
#define IKP_CXP_TRIG_EDGE_MODE_DOUBLE_EDGE (0)  ///< \~chinese 双边 \~english Double edge
#define IKP_CXP_TRIG_EDGE_MODE_RISE_ONLY   (1)  ///< \~chinese 单边 \~english Single edge
///@}

///@{
/**
\~chinese
 * @name CXP采集卡压缩传输模式可选项
 * @see IKP_CXP_DATA_PACKED_TRANSFER
\~english
 * @name CXP frame grabber compression transmission mode options
 * @see IKP_CXP_DATA_PACKED_TRANSFER
 */
#define IKP_CXP_DATA_PACKED_TRANSFER_OFF (0)  ///< \~chinese 关闭 \~english Off
#define IKP_CXP_DATA_PACKED_TRANSFER_ON  (1)  ///< \~chinese 开启 \~english On
///@}

///@{
/**
\~chinese
 * @name CXP采集卡传输给相机的触发包电平极性可选项
 * @see IKP_CXP_TRIG_LEVEL
\~english
 * @name Level polarity of trigger packets that transfer to camera from SFP frame grabber options
 * @see IKP_CXP_TRIG_LEVEL
 */
#define IKP_CXP_TRIG_LEVEL_ALL_LOW        (0)  ///< \~chinese 低电平 \~english Low level
#define IKP_CXP_TRIG_LEVEL_ALL_HIGH       (1)  ///< \~chinese 高电平 \~english High level
#define IKP_CXP_TRIG_LEVEL_GENERAL_INPUT1 (2)  ///< \~chinese 通用输入信号1 \~english General input signal1
#define IKP_CXP_TRIG_LEVEL_GENERAL_INPUT2 (3)  ///< \~chinese 通用输入信号2 \~english General input signal2
///@}

///@{
/**
\~chinese
 * @name 缩略尺寸系数可选项
 * @see IKP_THUMBNAIL_SIZE_FACTOR
\~english
 * @name Thumbnail size factor options
 * @see IKP_THUMBNAIL_SIZE_FACTOR
 */
#define IKP_THUMBNAIL_SIZE_FACTOR_0  (0)   ///< \~chinese 0 \~english 0
#define IKP_THUMBNAIL_SIZE_FACTOR_4  (4)   ///< \~chinese 4 \~english 4
#define IKP_THUMBNAIL_SIZE_FACTOR_8  (8)   ///< \~chinese 8 \~english 8
#define IKP_THUMBNAIL_SIZE_FACTOR_16 (16)  ///< \~chinese 16 \~english 16
#define IKP_THUMBNAIL_SIZE_FACTOR_32                                                                                        \
    (32)  ///< \~chinese 32 \~english 32
          ///@}
