
#include "scp_interpreter.h"
#include "scp_keynodes.h"
#include "sc_helper.h"
#include "sc_memory_headers.h"

#include <stdio.h>

#include <glib.h>

void create_process_test()
{
    sc_addr quest, init, request;

    sc_helper_resolve_system_identifier("question_scp_interpretation_request", &request);
    sc_helper_resolve_system_identifier("quest_proc_search_all_input", &quest);
    sc_helper_resolve_system_identifier("question_initiated", &init);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, request, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);
}

void preprocess_procedure(const sc_char *name)
{
    sc_addr quest, init, request, prog;

    sc_helper_resolve_system_identifier("question_scp_procedure_preprocessing_request", &request);
    sc_helper_resolve_system_identifier(name, &prog);
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

int main(void)
{
    scp_interpreter_init((sc_char *)"repo", (sc_char *)"sctp_config.ini");

    GTimer *timer = 0;
    timer = g_timer_new();
    g_timer_start(timer);

    preprocess_procedure("test_prog2");
    preprocess_procedure("test_prog2_2");
    preprocess_procedure("test_prog3");
    preprocess_procedure("test_prog4");
    preprocess_procedure("proc_search_all_output");
    preprocess_procedure("proc_search_all_input");

    test_scp_process_creating(1);

    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    return 0;
}
