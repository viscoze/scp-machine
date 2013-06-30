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
    scp_functions.h \
    scp_factory.h \
    scp_searchElStr3.h \
    scp_utils.h \
    scp_genElStr3.h \
    scp_genElStr5.h \
    scp_searchElStr5.h \
    scp_eraseElStr3.h \
    scp_eraseElStr5.h \
    scp_eraseSetStr3.h

SOURCES += \
    scp_functions.c \
    scp_types.c \
    scp_searchElStr3.c \
    scp_utils.c \
    scp_genElStr3.c \
    scp_genElStr5.c \
    scp_searchElStr5.c \
    scp_eraseElStr3.c \
    scp_eraseElStr5.c \
    scp_eraseSetStr3.c
