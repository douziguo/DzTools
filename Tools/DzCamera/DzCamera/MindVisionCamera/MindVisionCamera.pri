#############################################
#
#  迈德威视相机
#
#  版本：v2023/11/22
#
#############################################

INCLUDEPATH += \
    $$PWD \
    $$PWD/Include

LIBS += -L$$PWD
LIBS += -lLib/MVCAMSDK_X64

DEFINES += \
    SPEED_MINDVISION_CAMERA_LIB

HEADERS += \
    $$PWD/MindVisionCamera.h \
    $$PWD/MindVisionCameraInstance.h \
    $$PWD/gst417m.h

SOURCES += \
    $$PWD/MindVisionCamera.cpp \
    $$PWD/MindVisionCameraInstance.cpp
