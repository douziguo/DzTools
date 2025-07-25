
# 大恒相机库

INCLUDEPATH += $$PWD/inc
win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -L$$PWD/lib/x86 -lGxIAPICPPEx
    } else {
        LIBS += -L$$PWD/lib/x64 -lGxIAPICPPEx
    }
}


DEFINES += \
    SPEED_DAHENG_CAMERA_LIB

HEADERS += \
    $$PWD/DahengCamera.h \
    $$PWD/DahengInstance.h \

SOURCES += \
    $$PWD/DahengCamera.cpp \
    $$PWD/DahengInstance.cpp \

INCLUDEPATH += \
    $$PWD

TR_EXCLUDE += \
    $$PWD/inc/*
