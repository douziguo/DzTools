
# 巴斯勒相机库
INCLUDEPATH += $$(PYLON_DEV_DIR)/include
win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -L$$(PYLON_DEV_DIR)/lib/Win32
    } else {
        LIBS += -L$$(PYLON_DEV_DIR)/lib/x64
    }
}

DEFINES += \
    SPEED_BASLER_CAMERA_LIB

HEADERS += \
    $$PWD/BaslerCamera.h \
    $$PWD/BaslerEventer.h \
    $$PWD/BaslerInstance.h \

SOURCES += \
    $$PWD/BaslerCamera.cpp \
    $$PWD/BaslerInstance.cpp \

INCLUDEPATH += \
    $$PWD

TR_EXCLUDE += \
    $$(PYLON_DEV_DIR)/*
