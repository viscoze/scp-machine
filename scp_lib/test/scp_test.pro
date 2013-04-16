#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T23:58:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = scp_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.c
    
INCLUDEPATH += ../../../sc-machine/sc-memory/src/sc-store
INCLUDEPATH += ../
DESTDIR = ../../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../../sc-machine/bin" -lsc_memoryd
    LIBS += -L "../../../sc-machine/bin" -lscp_libd
}

unix {
    LIBS += -L "../../../sc-machine/bin" -lsc_memory
    LIBS += -L "../../../sc-machine/bin" -lscp_lib
}
