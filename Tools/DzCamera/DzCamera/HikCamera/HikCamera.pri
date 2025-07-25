# 海康相机库配置
INCLUDEPATH += $$(MVCAM_COMMON_RUNENV)/Includes

win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -L$$(MVCAM_COMMON_RUNENV)/Libraries/win32 -lMvCameraControl
    } else {
        LIBS += -L$$(MVCAM_COMMON_RUNENV)/Libraries/win64 -lMvCameraControl
    }
}

DEFINES += SPEED_HIK_CAMERA_LIB

HEADERS += \
    $$PWD/HikCamera.h \
    $$PWD/HikInstance.h

SOURCES += \
    $$PWD/HikCamera.cpp \
    $$PWD/HikInstance.cpp

INCLUDEPATH += $$PWD
TR_EXCLUDE += $$(MVCAM_COMMON_RUNENV)/*

