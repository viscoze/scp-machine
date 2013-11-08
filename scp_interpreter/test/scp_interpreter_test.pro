#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T23:58:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = scp_interpreter_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.c
    
INCLUDEPATH += ../../../sc-machine/sc-memory/src/sc-store
INCLUDEPATH += ../../../sc-machine/sc-memory/src
INCLUDEPATH += ../../scp_lib/src
INCLUDEPATH += ../src
DESTDIR = ../../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../../sc-machine/bin" -lsc_memoryd
    LIBS += -L "../../../sc-machine/bin" -lscp_libd

    INCLUDEPATH += "../glib/include/glib-2.0"
    INCLUDEPATH += "../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../glib/lib/glib-2.0.lib
    LIBS += ../glib/lib/glib-2.0.lib
}

unix {
    LIBS += -L "../../../sc-machine/bin" -lsc_memory
    LIBS += -L "../../../sc-machine/bin" -lscp_lib
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    PKGCONFIG += gmodule-2.0
}
