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
    sc_iterator5.c
    
INCLUDEPATH += ../sc-memory/src 
INCLUDEPATH += ../sc-memory/src/sc-store
DESTDIR = ../bin

win32 {
    CONFIG += qt console
    LIBS += -L "../bin" -lsc_memoryd
}

HEADERS += \
    search.h \
    system.h \
    identification.h \
    sc_iterator5.h
