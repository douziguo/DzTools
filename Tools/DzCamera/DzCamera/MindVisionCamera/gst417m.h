
#ifndef _PRODUCTNAME_GST417M_
#define _PRODUCTNAME_GST417M_

//#include "CameraGigeDebugBase.h"
#include <windows.h>

//#define	GF120_DEV_VERSION		"******V1.01******"		// 完成基本的测温和热红外图形功能
//#define	GF120_DEV_VERSION		"V1.0.3"                //增加了sensor温度自动校正补偿功能，将4次方函数计算改为查表计算
//#define	GF120_DEV_VERSION		"V1.0.4"                //增加配置文件格式和flash读取的格式一致
//#define	GF120_DEV_VERSION		"V1.0.5"                //增加自动重新校正 采用了线程读取数据帧
//#define	GF120_DEV_VERSION		"V1.0.6"                //增加软件和硬件触发
//#define	GF120_DEV_VERSION		"V1.0.7"                //增加软件防抱死，静电干扰后重新初始化sensor
//#define	GF120_DEV_VERSION		"V1.0.8"                //增加同时获取伪彩色和温度数据模式
//#define	GF120_DEV_VERSION		"V1.0.9"                //增加到26种伪彩色图像模式，修改了模式切换回卡死的问题
//#define	GF120_DEV_VERSION		"V1.0.10"               //修改了开机会花屏的问题
//#define	GF120_DEV_VERSION		"V1.0.11"               //修改了校正时网络卡导致的校正不正确问题
//#define	GF120_DEV_VERSION		"V1.0.12"               //增加了8个用户自定义区域测温
//#define	GF120_DEV_VERSION		"V1.0.13"               //增加帧率控制
//#define	GF120_DEV_VERSION		"V1.0.14"               //增加冷机模式 修改静电出错后不能正常校正的问题
//#define	GF120_DEV_VERSION		"V1.0.15"               //增加开机配置模式，开机改变测温模式导致出错
#define	GF120_DEV_VERSION		"V1.0.16"                   //修改触发计数不对
//sensor gst417M
//[0] ssr_rest	[1] tec_en	[2]开始输出同步信号	[3]开始一次NUC调整   [4]可以输出视频
#define		SSR_REST						 1 << 0
#define		TEC_EN							 1 << 1
#define		SYNC_INIT						 1 << 2
#define		NUC_INIT						 1 << 3
#define		IMG_OUT_EN						 1 << 4
#define		GSK_COMPLETE					 1 << 5
#define		BACK_INIT						 1 << 6
#define		RESPONSE_INIT					 1 << 7

#define		USER_ONCONTI_MODE				 1 << 9

#define		SHUTTER_OPEN					2
#define		SHUTTER_CLOSE					1


//必须等待DDR初始化完成才能进行NUC计算
#define		ADDR_BUF_STA					 0x003c
#define		ADDR_PG_BUF_CURID_L				 0x0030
#define		ADDR_PG_BUF_CURID_H				 0x0031
#define		ADDR_ORG_FPS					 0x0193		//有效帧率统计 每4s统计一次
		

#define		ADDR_GST417M_CTRL                0x0176		//WR
#define		ADDR_SSR_HVCNT					 0x0177		//WR
#define		ADDR_SHUTTER_CTRL                0x0178     //控制快门
#define		ADDR_GST417_STA                  0x0179
#define		ADDR_NUC_TEST_VALUE				 0x017A     //WR
#define		ADDR_NUC_DDR_REST				 0x017B     //WR
#define		ADDR_GSK_ADC_VALUE           	 0x017C
//NUC 调节使用	//中心点X16=8000±200	MCU写入 	
#define		ADDR_NUC_HIGH_VALUE				 0x017D 	//WR
#define		ADDR_NUC_LOW_VALUE				 0x017E     //WR
#define		ADDR_SSR_I2C_EN                  0x017F
#define		ADDR_FRAME_TEST					 0x0200
#define		ADDR_FRAME_DIV					 0x014B		

#define		ADDR_TRIG_CTL					 0x0055
#define		MCU_ADDR_SSR_I2C_EN				 0x10000180



#define		GST_MIDD_AD		3500								//需要调节到的中位值
#define		GST_AD_RANGE	1500								//GST在中值调节的范围	相当于粗调
#define		NUC_AD_1_SETP	200									//NUC在中值调节的范围	相当于细调 nuc步长为1的范围
#define		NUC_AD_4_SETP	400									//NUC在中值调节的范围	相当于细调 nuc步长为4的范围	[0-512]

#define		NUC_ADJUST_CNT	16									//NUC调节次数	[0-256] 每次调节80ms
#define		MAX_CAL_NUM		12									//校正需要采集的图像个数


#define		GSK_LOW_AD		GST_MIDD_AD - GST_AD_RANGE			//GSK调节低点	
#define		GSK_HIGH_AD		GST_MIDD_AD + GST_AD_RANGE			//GSK调节高点

//步长为1的调节范围
#define		NUC_1_LOW_AD		GST_MIDD_AD - NUC_AD_1_SETP		//NUC调节低点
#define		NUC_1_HIGH_AD		GST_MIDD_AD + NUC_AD_1_SETP		//NUC调节高点
//步长为4的调节范围
#define		NUC_4_LOW_AD		NUC_1_LOW_AD - NUC_AD_4_SETP	//NUC调节低点
#define		NUC_4_HIGH_AD		NUC_1_HIGH_AD + NUC_AD_4_SETP	//NUC调节高点

#define		PIXEL_H_VAL_NUM		400                             //中心区域V
#define		PIXEL_V_VAL_NUM		300                             //中心区域H


#define		SAMPLE_NUM			128                             //样本个数


#define		CENTRE_WIDTH		3                               //中心区域V

#define		CENTRE_V_NUM		(128 )                          //中心区域V
#define		CENTRE_H_NUM		(128 )                          //中心区域H



#define		CENTRE_H_START		 ((PIXEL_H_VAL_NUM - CENTRE_H_NUM) >> 1)		//中心区域开始H
#define		CENTRE_H_END		 ((PIXEL_H_VAL_NUM + CENTRE_H_NUM) >> 1) 		//中心区域结束H
#define		CENTRE_V_START		 ((PIXEL_V_VAL_NUM - CENTRE_V_NUM) >> 1) 		//中心区域开始V
#define		CENTRE_V_END		 ((PIXEL_V_VAL_NUM + CENTRE_V_NUM) >> 1)		//中心区域结束V

#define		COLOUR						1			//伪彩色显示
#define		PACK14BIT					1			//12bit显示
//#define		COLLECT_SAMPLE				1

//温度曲线网址
//http://www.qinms.com/webapp/curvefit/cf.aspx
// 前四种自动以彩色 后面22种伪彩色是Opencv自带的彩色
//具体彩色如下
//https://blog.csdn.net/kingkee/article/details/92785118
#define		COLOR_RAINBOW_NEW			0			//彩虹色
#define		COLOR_HOT_METAL				1			//热金属
#define		COLOR_WHITE					2			//白热
#define		COLOR_BLACK					3			//黑热
#define		COLOR_AUTUMN				4
#define		COLOR_BONE					5
#define		COLOR_JET					6
#define		COLOR_WINTER				7
#define		COLOR_RAINBOW				8
#define		COLOR_OCEAN					9
#define		COLOR_SUMMER				10
#define		COLOR_SPRING				11
#define		COLOR_COOL					12
#define		COLOR_HSV					13
#define		COLOR_PINK					14
#define		COLOR_HOT					15
#define		COLOR_PARULA				16
#define		COLOR_MAGMA					17
#define		COLOR_INFERNO				18
#define		COLOR_PLASMA				19
#define		COLOR_VIRIDIS				20
#define		COLOR_CIVIDIS				21
#define		COLOR_TWILIGHT				22
#define		COLOR_TWILIGHT_SHIFTED		23
#define		COLOR_TURBO					24
#define		COLOR_DEEPGREEN				25

#define		GST417M_IMG_WIDTH			400
#define		GST417M_IMG_HIGH			300

#define		ADDR_PG_BUF_BLK_SIZE        0x0026
#define		ADDR_PG_BUF_BLK_NUM         0x0027
#define		GST_PIXEL_FORMAT            0x23

#define		SHARPEN_GRADE				0 //锐化等级 0 - 100
#define		DDE_GRADE					50

//人体皮肤长波红外发射率为0.98
#define			USER_EMISS_RATE			98	//用户设置发射率
#define			TEMP_A					2.75	//((25*USER_EMISS_RATE)/100) 3个16bit 为0.01度  响应率归一化的值
#define			OUTSIDE_COEFF			16	 // 环境温度每改变0.01度改变的AD值 用做补偿
#define			TEMP_DIFF				0 //快门温度和测试物体有温度差



//环境温度影响曲线	为了精确可以和相机配合的 这里给出一个固定的值
//用于计算在2次快门校正的时间内sensor板温度变化引起的误差

//150摄氏度sensor温升补偿
#define		AD_COEFF_150_K3			0
#define		AD_COEFF_150_K2			0.003448
#define		AD_COEFF_150_K1			-9.997757
#define		AD_COEFF_150_K0			22535

//400摄氏度sensor温升补偿
#define		AD_COEFF_400_K3			0
#define		AD_COEFF_400_K2			0.000591
#define		AD_COEFF_400_K1			-1.445086
#define		AD_COEFF_400_K0			19470


//1200摄氏度sensor温升补偿
#define		AD_COEFF_1200_K3			0
#define		AD_COEFF_1200_K2			0
#define		AD_COEFF_1200_K1			0
#define		AD_COEFF_1200_K0			0
//802

#define		SHUTTER_COEFF_K3			2.66666666666668E-05
#define		SHUTTER_COEFF_K2			-0.0045714285714286
#define		SHUTTER_COEFF_K1			0.676190476190478
#define		SHUTTER_COEFF_K0			0

//050
//#define		SHUTTER_COEFF_K3			5.11062981E-06
//#define		SHUTTER_COEFF_K2			-7.9284324E-05
//#define		SHUTTER_COEFF_K1			0.7174916
//#define		SHUTTER_COEFF_K0			5.593903

//#define		SHUTTER_COEFF_K0			-2240	//505


#define		CALIBRATION_DISTANCE		150		//定标距离150cm
#define		CALIBRATION_TEMP			3000	//环境温度中值 高低温都向改温度靠近



#define		NO_SAMPLE_MODE					0
#define		RESPONSE_SAMPLE_MODE			1	//响应率采集
#define		TEMP_SAMPLE_MODE				2	//温度曲线采集
#define		SHUTTER_TEMP_SAMPLE_MODE		3	//快门温升采集
#define		SENSOR_TEMP_SAMPLE_MODE			4	//SENSOR板温升采集
#define		COVER_SAMPLE_MODE				5	//锅盖采集
#define		FACTORY_SAMPLE_MODE				6	//出厂校正

//统计基图的直方分布图 使用%5的统计作为最高和最低范围
//直方图最小宽度为2整个AD范围的20%
#define		MAX_POINT_NUM		100
//客户可设置的温度区间映射值
#define		MIN_SET_POINT		1600
#define		MAX_SET_POINT		1750


#define		RAINBOW_COLOR						0			//彩虹色
#define		HOT_METAL_COLOR						1			//热金属
#define		WHITE_FEVER_COLOR					2			//白热
#define		BLACK_FEVER_COLOR					3			//黑热

#define		TEMP_20_50      					0			//20-50摄氏度
#define		TEMP_40_150      					1			//-40-150摄氏度
#define		TEMP_40_500      					2			//40-500摄氏度

#define		IMAGE_TEMP_ENABLE                   0           //输出帧数据为温度数据
#define		IMAGE_RGB888_ENABLE                 1           //输出帧数据为RGB88数据
#define		IMAGE_RGB888_TEMP                	2           //输出帧数据为RGB88数据和温度数据 cp from mainwindow.h ljy


#define		STOP_CORRECT_ENABLE                 1           //关闭自动校正
#define		STOP_CORRECT_DISABLE                0           //打开自动校正

#define		WINDOWS_QT_ENABLE                   1           //使用windows的qt例程
#define		WINDOWS_QT_DISABLE                  0           //没有使用windows的qt例程


#define		GF120_IO_CTL_BASE					(0x8000)
//用户需要使用的命令
#define		SET_TEMP_MODE						(GF120_IO_CTL_BASE+0) 	//设置测温模式
#define		SET_COLOR_MODE						(GF120_IO_CTL_BASE+1)	//伪彩色模式							彩虹色	热金属	白热	黑热
#define		SET_USER_EMISSIVITY					(GF120_IO_CTL_BASE+2)	//设置发射率							默认发射率0.98
#define		SET_SHARPEN_GRADE					(GF120_IO_CTL_BASE+3)	//设置锐化等级							默认锐化等级	0
#define		SET_RGB888_ENABLE					(GF120_IO_CTL_BASE+4)	//输出16bit灰度数据 或者伪彩色数据		输出为RGB伪彩色或者0.01摄氏度的温度值
#define		SET_TEMP_CHECK						(GF120_IO_CTL_BASE+5)	//执行一次温度校正
#define     SET_STOP_CORRECT                    (GF120_IO_CTL_BASE+6)	//停止快门校正							在软件触发和硬件触发是需要停止快门校正
#define		GET_GF120_PARAM						(GF120_IO_CTL_BASE+7)	//获取所有实时数据
#define		SET_QT_IMG							(GF120_IO_CTL_BASE+8)	//windows下QT 数据需要RB对调和上下镜像 linux下QT不需要 演示SDK不需要
#define		SET_COLOR_PART						(GF120_IO_CTL_BASE+9)  //设置需要微彩映射的温度范围

#define		SET_OSD_ENABLE						(GF120_IO_CTL_BASE+10)	//打开OSD功能
#define		SET_OSD_TEMP_DISPLAY				(GF120_IO_CTL_BASE+11)	//打开OSD温度显示功能
#define		SET_OSD_ROI_DISPLAY					(GF120_IO_CTL_BASE+12)	//打开OSD区域温度显示功能

#define		SET_COMPENSATE_TEMP					(GF120_IO_CTL_BASE+13)  //设置总的温度补偿
#define		SET_CALIBRATION_ROI					(GF120_IO_CTL_BASE+14)	//设置黑体标定区域

#define		SET_SAMPLE_MODE                     (GF120_IO_CTL_BASE+16)	//设置采样模式
#define		SET_MANUAL_MODE                     (GF120_IO_CTL_BASE+17)	//设置手动模式
#define     SET_DISTANCE_COMPENSATE_TEMP        (GF120_IO_CTL_BASE+18)	//设置距离补偿

#define		SET_COVER_TEMP						(GF120_IO_CTL_BASE+19)	//锅盖采集温度
#define		SET_COVER_START						(GF120_IO_CTL_BASE+20) 	//开始采集指定温度的锅盖样本
#define		SET_LOAD_COVER_FILE					(GF120_IO_CTL_BASE+21)	//加载锅盖文件

#define		SET_FRAME_CAL						(GF120_IO_CTL_BASE+22)	//每多少帧统计一次温度 取温度均值
#define		SET_FACTORY_CHECK					(GF120_IO_CTL_BASE+23)	//
#define		SET_DDE_GRADE						(GF120_IO_CTL_BASE+24)	//DDE 增强等级
#define		SET_FRAME_RATE						(GF120_IO_CTL_BASE+25)	//设置帧率
#define		SET_ROI_COLOR						(GF120_IO_CTL_BASE+26)	//设置ROI色彩

#define		SET_COLD_MODE						(GF120_IO_CTL_BASE+27)	//设置非连续模式
#define		GET_CHECK_STATUS					(GF120_IO_CTL_BASE+28)	//获取校正状态
#define     SET_TEMP_FAST_CHECK                 (GF120_IO_CTL_BASE+29)	//执行一次快速校正
	
//校正需要使用命令 用户不需要使用
#define		SET_RESPONSE_RATE_TEMP				(GF120_IO_CTL_BASE+32)	//响应率采集温度
#define		SET_RESPONSE_RATE_START				(GF120_IO_CTL_BASE+33)  //开始采集指定温度的响应率样本
#define		SET_COVER_STOP						(GF120_IO_CTL_BASE+34)  //开始采集指定温度的锅盖样本
#define		SET_RESPONSE_RATE_STOP				(GF120_IO_CTL_BASE+35) 	//开始采集指定温度的响应率样本
#define		SET_LOAD_RESPONSE_FILE				(GF120_IO_CTL_BASE+36)	//加载响应率文件
#define		SET_EXPOSURE_TIME					(GF120_IO_CTL_BASE+37)	//设置曝光时间
#define		SET_SHUTTER_MODE                    (GF120_IO_CTL_BASE+38)	//打开或者关闭快门
#define		GET_COVER_STATUS					(GF120_IO_CTL_BASE+39)	//获取锅盖采样结果
#define		GET_RESPONSE_RATE_STATUS			(GF120_IO_CTL_BASE+40)	//获取响应率采样结果
#define		SET_WRITE_CONFIG_FILES				(GF120_IO_CTL_BASE+41)	//保存校正文件到相机
#define     GET_GF120SET_PARAM                  (GF120_IO_CTL_BASE+42)  //获取相机内GF120_set_param_t数据
#define     SET_TEMP_COMPENSATE                 (GF120_IO_CTL_BASE+43)
#define     SET_HUMIDITY_COMPENSATE             (GF120_IO_CTL_BASE+44)
#define     SET_GAIN                            (GF120_IO_CTL_BASE+45)
#define		MAX_USER_ROI                        8


typedef struct _WIDTH_HEIGHT{
    int     display_width;
    int     display_height;
    int     xOffsetFOV;
    int     yOffsetFOV;
    int     sensor_width;
    int     sensor_height;
    int     buffer_size;
}Width_Height;

//struct GF120_roi_t{
//    USHORT		user_roi_enable;			//用户设置区域检测温度功能打开
//    USHORT		user_width_start;			//用户设置区域检测温度区宽开始点
//    USHORT		user_width_number;			//用户设置区域检测温度区宽像素点个数
//    USHORT		user_high_start;			//用户设置区域检测温度区高开始点
//    USHORT		user_high_number;			//用户设置区域检测温度区高素点个数
//    USHORT		user_roi_emissivity;
//};
struct GF120_roi_t{
    USHORT		user_roi_enable;			//用户设置区域检测温度功能打开
    USHORT		user_width_start;			//用户设置区域检测温度区宽开始点
    USHORT		user_width_end;				//用户设置区域检测温度区宽结束点
    USHORT		user_high_start;			//用户设置区域检测温度区高开始点
    USHORT		user_high_end;				//用户设置区域检测温度区高结束点
	USHORT		user_emissivity;				//用户设置区域检测温度区高结束点
};


//黑体炉校正
struct GF120_calibration_t{
    USHORT		user_calibration_enable;	//用户设置区域检测温度功能打开
	INT		    user_calibration_temp;		//黑体炉设置温度
    USHORT		user_width_start;			//用户设置区域检测温度区宽开始点
    USHORT		user_width_end;				//用户设置区域检测温度区宽结束点
    USHORT		user_high_start;			//用户设置区域检测温度区高开始点
    USHORT		user_high_end;				//用户设置区域检测温度区高结束点
};

struct GF120_color_t
{
    USHORT		user_color_enable;			//用户设置 温度微彩范围 三段曲线的中间两个点
    INT		    user_color_high;			//用户设置 低温色彩
    INT		    user_color_low;				//用户设置 高温色彩
};
//用户设置的参数和用户需要获取的参数
//用户设置的参数和用户需要获取的参数
struct GF120_set_param_t
{
	USHORT		temp_mode;					//三种测温区间	-40℃~150℃	-40~800℃	20~50℃
    USHORT		sample_mode;				//样本采样模式
    USHORT      manual_mode;                //手动模式
    INT         manual_temp;                //手动模式温度
	USHORT		stop_correct;				//停止校正
	USHORT		shutter_on;					//快门强制操作
    USHORT		collect_cover_sample;		//采集锅盖现象样本使用
    SHORT		collect_cover_temp;			//采集锅盖现象样本使用
    USHORT		collect_response_sample;
    SHORT		collect_response_temp;
    USHORT		response_rate_sample;		//响应率样本采集 高低温个一个
    USHORT		color_mode;					//伪彩色编码种类 支持用户调色板 256个RGB色度值
    USHORT		user_emissivity;			//设置的发射率
    USHORT		sharpen_grade;				//锐化等级 设置我0 不锐化
	USHORT		exposure_time;				//曝光时间
    USHORT      gain;
    USHORT		out_rgb888_enable;			//输出8bit伪彩色图形 否则输出16位灰度数据
    USHORT		osd_enable;					//在输出伪彩色图像时是否添加OSD显示，最高最低温度
    USHORT		qt_img;						//qt需要RB对调 和上下镜像
    USHORT		temp_display_enable;		//在输出伪彩色图像时是否添加OSD显示，最高最低温度
    INT		    user_compensate_temp;       //用户自定义补偿
    INT		    humidity_compensate_temp;   //湿度补偿
    INT		    distance_compensate_temp;   //距离补偿
    INT		    compensate_temp;            //三种补偿和
    USHORT      high_temp_warm_enable;      //高温报警使能
    INT         high_temp_warm_temp;        //高温报警温度
    USHORT      low_temp_warm_enable;       //高温报警使能
    INT         low_temp_warm_temp;         //高温报警温度
    char		low_cover_file[256];		//低温锅盖采样文件
    char		high_cover_file[256];		//高温锅盖采样文件
    char		low_response_file[256];		//低温响应率采样文件
    char		high_response_file[256];	//高温响应率采样文件
    GF120_roi_t		GF120_roi;
    GF120_color_t	GF120_color;
    GF120_calibration_t  GF120_calibration;
    UINT		frame_temp_cnt;				//多少帧进行一次温度统计 伪彩色使用25帧统计一次 抓图可以这是为1帧统计一次
    USHORT		dde_grade;					//锐化等级 设置我0 不锐化
    USHORT		frame_rate_set;				//锐化等级 设置我0 不锐化
    USHORT		ROI_R_COLOR;				//ROI R色彩
    USHORT		ROI_G_COLOR;				//ROI G色彩
    USHORT		ROI_B_COLOR;				//ROI B色彩
    USHORT		cold_mode;					//冷机模式
};

struct GF120_get_param_t
{
	char		gf120_dev_version[32];
    USHORT		frame_val;                  //指示改帧是否有效，在校正其间传输的是校正前的静止图像
    INT		    gst417m_temp;               //红外相机焦面温度
    INT		    gst417m_tec_temp;           //红外相机设置温度
    INT 		outside_temp;               //红外相机设置温度
    INT    		shutter_temp;               //红外相机快门温度
    USHORT      gst417m_gain;
    USHORT		gst417m_ctia;
    int			low_temp;                   //最低温值
    USHORT		low_temp_width;             //最低温宽坐标
    USHORT		low_temp_hight;             //最低温高坐标
    int			high_temp;                  //最高温值
    USHORT		high_temp_width;            //最高温宽坐标
    USHORT		high_temp_hight;            //最高温高坐标
    int			center_temp;                //图像中心位置温度
    int			user_temp;                  //用户设置区域温度
    USHORT		ad_value;
    SHORT		diff_ad_value;
    SHORT		diff_temp_value;
    char		config_dir[256];            //配置文件目录
    int			calibration_high_temp;      //高温黑体炉温度
    int			calibration_low_temp;       //低温黑体炉温度
    int			gst417m_frame_cnt;          //相机输出帧个数
    int			gst417m_frame_rate;         //统计到的帧率
};	

/*官方提供的测温方案	测温范围即-40℃~150℃
档位				对应快门温传温度Ts范围	TEC稳定温度		
测温档				-40℃≤T＜-10℃			-15℃					
测温档				-10℃≤T≤50℃			40℃
测温档				50℃＜T					65
*/

//开机需要等待温度稳定后设置参数
//根据芯片参考手设置
//外挂温度		tec设置温度	积分时间	GFID	GAIN	中心点		GSK				NUC				
//-127<T<-30	-25			24			200		0		5000		±1000			±200
//-30<T<-15		-15			24			200		0		5000		±1000			±200
//-15<T< 0		  0			24			200		1		5000		±1000			±200
// 0<T< 10		 10			24			200		1		6000		±1000			±200
//10<T< 20		 20			56			200		1		7000		±1000			±200
//20<T< 30		 30			56			200		2		8000		±1000			±200
//30<T< 40		 40			56			200		3		8000		±1000			±200
//40<T< 50		 55			56			180		6		9000		±1000			±200
//50<T< 127		 65			56			180		7		10000		±1000			±200

//vtemp = 0.012*T + 1.101 (vtemp 是gst温度输出电压 T是gst417M焦温)
//vset_temp = 2.5 - vtemp = 1.399 - 0.012*T (现在有误差 温度需要加2度)
//计算分桥电压使用了TINA软件 数组电位器100K可以256组分压

//gst417M 不同温度下的设置参数
//外挂温度	tec设置温度	积分时间	GFID	GAIN	中心点		GSK				NUC步长为4范围	NUC步长为1范围
struct GST417M_set_t
{
  SHORT     temp_mode;                      //环境高温
  SHORT     outside_low_temp;               //环境高温
  SHORT     outside_higth_temp;             //环境低温	用来查找
  SHORT     tec_set_temp;					//设置温度
  SHORT     tec_set_vol;					//设置电位器值
  UINT      gst417m_ctia;					//积分时间
  UINT      gst417m_gfid;					//GFID
  UINT      gst417m_gain;					//GAIN
  UINT      outside_coeff;
  UINT      gst417m_middle;                 //中心点
  UINT      gst417m_gsk;					//GSK					中心点±GST_AD_RANGE
  UINT      gst417m_nuc_one;				//NUC步长为1范围		中心点±NUC_AD_1_SETP
  UINT      gst417m_nuc_four;				//NUC步长为4范围		中心点±NUC_AD_1_SETP±NUC_AD_4_SETP

};

#define	TMEP_MAX_NUM		10
//外挂温度为了提高精度扩大了10倍单位为0.1度

#endif
