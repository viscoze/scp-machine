TEMPLATE = lib

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
INCLUDEPATH += ../scp_lib/src
DESTDIR = ../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../sc-machine/bin" -lsc_memoryd
    LIBS += -L "../../sc-machine/bin" -lscp_libd

    INCLUDEPATH += "../glib/include/glib-2.0"
    INCLUDEPATH += "../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../glib/lib/glib-2.0.lib
    LIBS += ../glib/lib/glib-2.0.lib
}

unix {
    LIBS += -L "../../sc-machine/bin" -lsc_memory
    LIBS += -L "../../sc-machine/bin" -lscp_lib
    CONFIG += link_pkgconfig

    PKGCONFIG += glib-2.0
    PKGCONFIG += gmodule-2.0
}

HEADERS += \
    src/scp_interpreter.h \
    src/scp_keynodes.h \
    src/scp_operator_keynodes.h \
    src/scp_interpreter_utils.h \
    src/scp_process_creator.h \
    src/scp_process_destroyer.h \
    src/scp_operator_interpreter_agents.h \
    src/scp_operator_interpreter_functions.h \
    src/scp_procedure_preprocessor.h

SOURCES += \
    src/scp_interpreter.c \
    src/scp_keynodes.c \
    src/scp_operator_keynodes.c \
    src/scp_interpreter_utils.c \
    src/scp_process_creator.c \
    src/scp_process_destroyer.c \
    src/scp_operator_interpreter_agents.c \
    src/scp_operator_interpreter_functions.c \
    src/scp_procedure_preprocessor.c

