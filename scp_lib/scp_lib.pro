TEMPLATE = lib

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
DESTDIR = ../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../sc-machine/bin" -lsc_memoryd

    INCLUDEPATH += "../glib/include/glib-2.0"
    INCLUDEPATH += "../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../glib/lib/glib-2.0.lib
    LIBS += ../glib/lib/glib-2.0.lib
}


unix {
    LIBS += -L "../../sc-machine/bin" -lsc_memory
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    PKGCONFIG += gmodule-2.0
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
    scp_eraseSetStr3.h \
    scp_eraseSetStr5.h \
    scp_iterator3.h \
    scp_iterator5.h

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
    scp_eraseSetStr3.c \
    scp_eraseSetStr5.c \
    scp_iterator3.c \
    scp_iterator5.c
