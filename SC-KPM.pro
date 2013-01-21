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


SOURCES += main.cpp \
    system.c \
    question.c \
    search_operations.c \
	system_pattern.cpp
    
INCLUDEPATH += ../sc-machine/sc-memory/src
INCLUDEPATH += ../sc-machine/sc-memory/src/sc-store
DESTDIR = ../sc-machine/bin

win32 {
    CONFIG += qt console
    LIBS += -L "../bin" -lsc_memoryd

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
}

HEADERS += \
    system.h \
    question.h \
    search_operations.h \
	system_pattern.h
