
# Dalsa 相机库

INCLUDEPATH += \
    $$(SAPERADIR)/Include \
    $$(SAPERADIR)/Classes/Basic \
    # $$(SAPERADIR)/Classes/Gui

LIBS += -L$$(SAPERADIR)/Lib/Win64

LIBS += \
    -lSapClassBasic

HEADERS += \
    $$PWD/DalsaCamera.h \
    $$PWD/DalsaCameraInstance.h

SOURCES += \
    $$PWD/DalsaCamera.cpp \
    $$PWD/DalsaCameraInstance.cpp
