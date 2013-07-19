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
    CONFIG += link_pkgconfig
}

HEADERS += \
    src/scp_types.h \
    src/scp_functions.h \
    src/scp_factory.h \
    src/scp_searchElStr3.h \
    src/scp_utils.h \
    src/scp_genElStr3.h \
    src/scp_genElStr5.h \
    src/scp_searchElStr5.h \
    src/scp_eraseElStr3.h \
    src/scp_eraseElStr5.h \
    src/scp_eraseSetStr3.h \
    src/scp_eraseSetStr5.h \
    src/scp_iterator3.h \
    src/scp_iterator5.h \
    src/scp_system_operators/sc_system_gen.hpp \
    src/scp_system_operators/sc_system_operators.hpp \
    src/scp_system_operators/sc_system_search.hpp \
    src/scp_system_operators/scp_sys_search.h \
    src/scp_system_operators/scp_sys.h

SOURCES += \
    src/scp_functions.c \
    src/scp_types.c \
    src/scp_searchElStr3.c \
    src/scp_utils.c \
    src/scp_genElStr3.c \
    src/scp_genElStr5.c \
    src/scp_searchElStr5.c \
    src/scp_eraseElStr3.c \
    src/scp_eraseElStr5.c \
    src/scp_eraseSetStr3.c \
    src/scp_eraseSetStr5.c \
    src/scp_iterator3.c \
    src/scp_iterator5.c \
    src/scp_system_operators/sc_system_search.cpp \
    src/scp_system_operators/sc_system_operators.cpp \
    src/scp_system_operators/sc_system_gen.cpp \
    src/scp_system_operators/scp_sys_search.cpp \
    src/scp_system_operators/scp_sys.c
