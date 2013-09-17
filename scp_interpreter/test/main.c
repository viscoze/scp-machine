
#include "scp_interpreter.h"
#include "sc_helper.h"
#include "sc_memory_headers.h"

#include <stdio.h>

#include <glib.h>

void create_process_test()
{
    sc_addr quest, init, request;

    sc_helper_resolve_system_identifier("question_scp_interpretation_request", &request);
    sc_helper_resolve_system_identifier("quest2", &quest);
    sc_helper_resolve_system_identifier("question_initiated", &init);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, request, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);
}

void create_preprocessing_test()
{
    sc_addr quest, init, request, prog;

    sc_helper_resolve_system_identifier("question_scp_procedure_preprocessing_request", &request);
    sc_helper_resolve_system_identifier("test_prog3", &prog);
    sc_helper_resolve_system_identifier("question_initiated", &init);
    quest = sc_memory_node_new(scp_type_const);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, request, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, prog);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);
}

void test_scp_process_creating(int value)
{
    int i = 0;
    for (i = 0; i < value; i++)
    {
        create_process_test();
    }
}

void test_scp_procedure_preprocessor(int value)
{
    int i = 0;
    for (i = 0; i < value; i++)
    {
        create_preprocessing_test();
    }
}

int main(void)
{
    scp_interpreter_init((sc_char *)"repo", (sc_char *)"test.ini");

    GTimer *timer = 0;
    timer = g_timer_new();
    g_timer_start(timer);

    test_scp_procedure_preprocessor(1);
    //test_scp_process_creating(1000);

    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    return 0;
}