TEMPLATE = lib

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
DESTDIR = ../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../sc-machine/bin" -lsc_memoryd
}


unix {
    LIBS += -L "../../sc-machine/bin" -lsc_memory
}

HEADERS += \
    scp_types.h \
    scp_functions.h

SOURCES += \
    scp_functions.c \
    scp_types.c
