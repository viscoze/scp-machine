
//#include "scp_interpreter.h"
//#include "scp_keynodes.h"
#include "scp_lib.h"
#include "sc_helper.h"
#include "sc_memory_headers.h"

#include <stdio.h>

#include <glib.h>

void create_process_test()
{
    sc_addr quest, init, nrel_answer;
    scp_operand op;

    sc_helper_resolve_system_identifier("test_question", &quest);
    sc_helper_resolve_system_identifier("question_initiated", &init);
    sc_helper_resolve_system_identifier("question_nrel_answer", &nrel_answer);

    sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);

    sc_iterator5 *it = sc_iterator5_f_a_a_a_f_new(quest, sc_type_arc_common, 0, sc_type_arc_pos_const_perm, nrel_answer);
    while (SC_TRUE == sc_iterator5_next(it))
    {
        op.addr=sc_iterator5_value(it,2);
        printEl(&op);
    }
    sc_iterator5_free(it);
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
    sc_memory_initialize((sc_char *)"repo", (sc_char *)"sctp_config.ini");
    sc_helper_init();
    sc_memory_initialize_ext("extensions");
    //scp_interpreter_init();

    GTimer *timer = 0;
    timer = g_timer_new();
    g_timer_start(timer);

    test_scp_process_creating(1);

    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    return 0;
}
