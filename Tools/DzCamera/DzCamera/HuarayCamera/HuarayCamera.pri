##############################################################
#
#   华睿相机
#
##############################################################

isEmpty(HUARAY_DIR) {
    error(未找到华睿相机 SDK 路径 HUARAY_DIR，请按照 README 中的说明配置 HUARAY_DIR 路径！)
} else {
    message(使用项目配置华睿相机 SDK 路径 HUARAY_DIR：$$HUARAY_DIR)
}

HUARAY_DEV_DIR = $$HUARAY_DIR

# 华睿相机库
INCLUDEPATH += $$HUARAY_DEV_DIR/Include/IMV
win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -L$$HUARAY_DEV_DIR/Lib/win32  -lMVSDKmd
    } else {
        LIBS += -L$$HUARAY_DEV_DIR/Lib/x64 -lMVSDKmd
    }
}

HEADERS += \
    $$PWD/HuarayCamera.h \
    $$PWD/HuarayInstance.h

SOURCES += \
    $$PWD/HuarayCamera.cpp \
    $$PWD/HuarayInstance.cpp
