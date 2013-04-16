TEMPLATE = lib

SOURCES += \
    sc_system_search.cpp \
    sc_system_gen.cpp \
    sc_system_operators.cpp

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
INCLUDEPATH += ../../SC-KPM/sc_kpm_additional
DESTDIR = ../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../bin" -lsc_memoryd
}


unix {
    LIBS += -L "../../sc-machine/bin" -lsc_memory
}

HEADERS += \
    sc_system_search.h \
    sc_system_operators.h \
    sc_system_gen.h
