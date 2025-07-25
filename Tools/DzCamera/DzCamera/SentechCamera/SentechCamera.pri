
# 欧姆龙相机库
INCLUDEPATH += \
    $$(STAPI_ROOT_PATH)/Include/StApi    \
    $$(STAPI_ROOT_PATH)/Include/GenICam

win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -L$$(STAPI_ROOT_PATH)/lib/Win32
    } else {
        LIBS += -L$$(STAPI_ROOT_PATH)/lib/x64
    }
}


DEFINES += \
    SPEED_SENTECH_CAMERA_LIB

HEADERS += \
    $$PWD/SentechCamera.h \
    $$PWD/SentechInstance.h

SOURCES += \
    $$PWD/SentechCamera.cpp \
    $$PWD/SentechInstance.cpp

INCLUDEPATH += \
    $$PWD

TR_EXCLUDE += \
    $$(STAPI_ROOT_PATH)/*
