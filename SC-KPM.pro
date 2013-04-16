#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T23:58:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SC-KPM
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
    
INCLUDEPATH += ../sc-machine/sc-memory/src
INCLUDEPATH += ../SC-KPM/sc_kpm_additional
INCLUDEPATH += ../SC-KPM/sc_system_operators
INCLUDEPATH += ../sc-machine/sc-memory/src/sc-store
DESTDIR = ../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../sc-machine/bin" -lsc_memoryd
    LIBS += -L "../sc-machine/bin" -lsc_kpm_additionald
    LIBS += -L "../sc-machine/bin" -lsc_system_operatorsd

    INCLUDEPATH += "../glib/include/glib-2.0"
    INCLUDEPATH += "../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../glib/lib/glib-2.0.lib
    LIBS += ../glib/lib/glib-2.0.lib
}

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    PKGCONFIG += gmodule-2.0

    LIBS += -L "../sc-machine/bin" -lsc_memory
    LIBS += -L "../sc-machine/bin" -lsc_kpm_additional
    LIBS += -L "../sc-machine/bin" -lsc_system_operators
}

HEADERS +=
