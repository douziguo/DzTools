
# 埃科光电 SDK

#INCLUDEPATH += $$PWD/inc

win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -L$$PWD/IKap/Lib/x86
    } else {
        LIBS += -L$$PWD/IKap/Lib/x64
    }

    LIBS += -lIKapBoard
    LIBS += -lIKapC
}
