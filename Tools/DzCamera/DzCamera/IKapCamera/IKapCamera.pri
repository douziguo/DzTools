
# 埃科光电相机库

include($$PWD/IKap.pri)

DEFINES += \
    SPEED_CAMERA_IKAP_LIB

HEADERS += \
    $$PWD/IKapCamera.h \
    $$PWD/IKapInstance.h

SOURCES += \
    $$PWD/IKapCamera.cpp \
    $$PWD/IKapInstance.cpp

INCLUDEPATH += \
    $$PWD
