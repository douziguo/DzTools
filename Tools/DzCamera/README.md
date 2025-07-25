# Qt 通用工业相机模块


提供统一的接口对相机进行控制及管理，**只支持 2D 相机**。



### 功能总览

|          | 搜寻 | 加载 | 软触发 | 硬触发 | 曝光 | 包大小 | I/O  | 数字移位 | 增益 |
| -------- | ---- | ---- | ------ | ------ | ---- | ------ | ---- | -------- | ---- |
| 虚拟相机 | √    | √    | √      |        | √    | √      | √    | √        | √    |
| 巴斯勒   | √    | √    | √      | √      | √    | √      | √    | √        | √    |
| 海康威视 | √    | √    | √      | √      | √    | √      |      | √        | √    |
| 欧姆龙   | √    | √    | √      |        | √    |        | √    |          |      |
| 大恒     | √    | √    | √      |        | √    | √      | √    |          |      |
| Dalsa    | √    | √    | √      |        |      |        |      |          |      |
| 迈德威视 | √    | √    | √      |        | √    |        |      |          |      |
| 埃科光电 | √    | √    |        |        |      |        |      |          |      |



###  使用方式

1、安装好对应相机的 SDK；

2、复制以下内容，粘贴至 Qt 项目的 .pro 文件中：

```bash
# 按需启用指定品牌的相机 SDK 即可
DEFINES += ENABLE_SPEED_CAMERA_BASLER       # 启用巴斯勒相机
DEFINES += ENABLE_SPEED_CAMERA_SENTECH      # 启用欧姆龙相机
DEFINES += ENABLE_SPEED_CAMERA_HIK          # 启用海康相机
DEFINES += ENABLE_SPEED_CAMERA_DAHENG       # 启用大恒相机
DEFINES += ENABLE_SPEED_CAMERA_DALSA        # 启用 Dalsa 相机
DEFINES += ENABLE_SPEED_CAMERA_MINDVISION   # 启用迈德威视相机
DEFINES += ENABLE_SPEED_CAMERA_IKAP   		# 启用埃科光电相机

# 引入工业相机模块
include(libs/SpeedCamera/SpeedCamera.pri)
```



### 开发计划

#### 计划支持的相机

- [x] 虚拟相机（用于在不连接相机的情况下调试程序）
- [x] 巴斯勒 Basler
  - SDK 下载  https://www.baslerweb.com/cn/sales-support/downloads/software-downloads/
- [x] 欧姆龙 Sentech
  - SDK 下载  https://www.fa.omron.com.cn/products/family/3684/download/catalog.html
- [x] 海康威视 Hikvision
  - SDK 下载  https://www.hikrobotics.com/cn/machinevision/service/download?module=0
- [x] 大恒
  - SDK 下载  https://www.daheng-imaging.com/index.php?m=content&c=index&a=lists&catid=59&czxt=&sylx=23&syxj=44#mmd
- [x] 迈德威视
  - SDK 下载 https://www.mindvision.com.cn/rjxz/list_12.aspx?lcid=138
- [ ] 埃科光电
  - SDK 下载
- [ ] 大华
- [ ] 华睿
- [ ] 映美精
- [ ] <del>图漾？</del>
- [ ] photoneo
- [ ] 其它 常用的工业相机及SDK  https://blog.csdn.net/libaineu2004/article/details/105266252/

#### 计划支持的功能

- [x] 相机的扫描、加载
- [x] 曝光设置
- [x] 包大小设置
- [x] I/O 控制
- [ ] ……

#### 其它

- [ ] 封装成动态链接库
- [x] 支持多品牌相机共用
- [ ] 开放通用 GenICam 接口
- [ ] 相机数据 xml 导出、导入
- [ ] 获取相机列表时，返回更多相机信息（序列号、IP、MAC 地址、型号……）
- [ ] 连续拍照模式（图片改为信号发出）



### 更新日志

#### 2025/02/21

- 新增对埃科光电相机的支持

#### 2023/11/23

- 内置函数逐步改造为线程安全
- 支持传入 parent 指针
- 新增 `Dalsa` 相机封装
- 新增 `迈德威视` 相机封装

#### 2023/5/20

- **重要说明**：从此版本起，本相机库的接口有较大改动
- 原 `SpeedCamera` 改为 `Camera`
- 所有类加入 `SpeedCamera` 命名空间
- 更新相机库翻译
- 移除部分冗余代码

#### 2023/4/28

- **重构模块**：各品牌相机改为继承自 SpeedCamera 并派生
- **重要说明**：从此版本起，本相机库的接口有较大改动，如需使用之前的版本，请切换到 [v1](https://git.speedbot.net/QtLibs/SpeedCamera/-/tree/v1) 分支！
- 回调取图加锁，防止多线程使用崩溃

#### 2022/9/5

- 支持巴斯勒彩色相机
- 海康相机采图优化
- 增加 `setDigitalShift` 设置数字移位接口

#### 2022/6/9

- 新增海康相机封装

#### 2022/6/8

- 修复巴斯勒图片转码不正确
- 修复引入模块后导致项目无法正常使用 Qt 语言家更新翻译

#### 2021/4/20

- 新增虚拟相机



### 参考资料

- Qt调用工业相机之巴斯勒相机  https://blog.csdn.net/qq_34139994/article/details/105653286
- Qt调用工业相机之海康威视相机  https://blog.csdn.net/qq_34139994/article/details/107706251
- Qt调用工业相机之映美精相机  https://blog.csdn.net/qq_34139994/article/details/105653257
- 工业相机编程模型和流程  https://blog.csdn.net/wenzhou1219/article/details/45874779
