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


SOURCES += main.c \
    system.c \
    search.c \
    identification.c \
    question.c \
    search_operations.c \
	system_pattern.cpp
    
INCLUDEPATH += ../sc-memory/src 
INCLUDEPATH += ../sc-memory/src/sc-store
DESTDIR = ../bin

win32 {
    CONFIG += qt console
    LIBS += -L "../bin" -lsc_memoryd

    INCLUDEPATH += "../glib/include/glib-2.0"
    INCLUDEPATH += "../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../glib/lib/glib-2.0.lib
    LIBS += ../glib/lib/glib-2.0.lib
}

HEADERS += \
    search.h \
    system.h \
    identification.h \
    question.h \
    search_operations.h \
	system_pattern.h
