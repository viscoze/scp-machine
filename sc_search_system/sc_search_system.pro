TEMPLATE = lib

SOURCES += \
    sc_search_system.cpp

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
INCLUDEPATH += ../../SC-KPM/sc_kpm_additional
DESTDIR = ../../sc-machine/bin

win32 {
    CONFIG += qt console
    LIBS += -L "../../bin" -lsc_memoryd

    INCLUDEPATH += "../../glib/include/glib-2.0"
    INCLUDEPATH += "../../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../../glib/lib/glib-2.0.lib
    LIBS += ../../glib/lib/glib-2.0.lib
}


unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    PKGCONFIG += gmodule-2.0

    LIBS += -L "../../sc-machine/bin" -lsc_memory
}

HEADERS += \
    sc_search_system.h
