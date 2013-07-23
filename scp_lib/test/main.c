#include "scp_functions.h"
#include "scp_types.h"
#include <stdio.h>
#include "sc_memory.h"
#include <glib.h>
#include "malloc.h"
#include "sc_stream.h"
#include "sc_helper.h"
#include "scp_iterator3.h"
#include "scp_iterator5.h"

#include "scp_system_operators/scp_sys.h"

/*void foo()
{
    sc_addr addr1 = sc_memory_node_new(0);
    sc_addr addr2 = sc_memory_node_new(0);
    sc_memory_arc_new(0, addr1, addr2);

    sc_memory_element_free(addr1);
    sc_memory_element_free(addr2);

    sc_iterator3 *it = sc_iterator3_f_a_a_new(addr1, 0, 0);
    while (sc_iterator3_next(it))
    {
        printf("ELEM FOUND\n");
    }
    sc_iterator3_free(it);
}*/


void foo1()
{
    scp_operand param2;
    param2.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("link1", &(param2.addr));
    //param2.addr = sc_memory_node_new(sc_type_link);
    if (SCP_RESULT_TRUE == ifFormCont(&param2))
    {
        printf("OK\n");
    }
    else
    {
        printf("NO\n");
    }
}

void iterator3_test()
{
    scp_operand param1;
    sc_helper_resolve_system_identifier("iter_test", &(param1.addr));
    param1.element_type = scp_type_node | scp_type_const;
    param1.param_type = SCP_FIXED;

    scp_operand param2;
    param2.element_type = scp_type_const;
    param2.param_type = SCP_ASSIGN;

    scp_operand param3;
    param3.element_type = scp_type_const;
    sc_helper_resolve_system_identifier("node1", &(param3.addr));
    param3.param_type = SCP_FIXED;

    scp_iterator3 *it = scp_iterator3_new(&param1, &param2, &param3);
    param3.param_type = SCP_ASSIGN;
    while (scp_iterator3_next(it, &param1, &param2, &param3) == SCP_RESULT_TRUE)
    {
        printEl(&param2);
    }
    scp_iterator3_free(it);
}

void test1()
{
    scp_operand param1;
    param1.param_type = SCP_ASSIGN;

    scp_operand param2;
    sc_helper_resolve_system_identifier("link1", &(param2.addr));
    param2.param_type = SCP_FIXED;

    scp_operand param3;
    sc_helper_resolve_system_identifier("link2", &(param3.addr));
    param3.param_type = SCP_FIXED;

    //printNl(&param1);
    //printNl(&param2);

    contDiv(&param1, &param2, &param3);

    printNl(&param1);
    printNl(&param2);
    printNl(&param3);

    //param1.param_type = SCP_FIXED;

    contAdd(&param1, &param1, &param2);

    printNl(&param1);
    printNl(&param2);
    printNl(&param3);

}

void iterator5_test()
{
    scp_operand param1;
    sc_helper_resolve_system_identifier("iter_test", &(param1.addr));
    param1.element_type = scp_type_node | scp_type_const;
    param1.param_type = SCP_FIXED;

    scp_operand param2;
    param2.element_type = scp_type_const;
    param2.param_type = SCP_ASSIGN;

    scp_operand param3;
    param3.element_type = scp_type_const;
    param3.param_type = SCP_ASSIGN;

    scp_operand param4;
    param4.element_type = scp_type_const;
    param4.param_type = SCP_ASSIGN;

    scp_operand param5;
    param5.element_type = scp_type_const;
    param5.param_type = SCP_ASSIGN;

    scp_iterator5 *it = scp_iterator5_new(&param1, &param2, &param3, &param4, &param5);
    while (scp_iterator5_next(it, &param1, &param2, &param3, &param4, &param5) == SCP_RESULT_TRUE)
    {
        printEl(&param5);
    }
    scp_iterator5_free(it);
}

void test_system_operator()
{
    GTimer *timer = 0;
    timer = g_timer_new();
    g_timer_start(timer);

    scp_operand param1;
    sc_helper_resolve_system_identifier("pattern4", &(param1.addr));
    param1.param_type = SCP_FIXED;

    scp_operand param2;
    param2.param_type = SCP_ASSIGN;

    /*scp_operand_pair param2;
    scp_operand param2_1;
    param2_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_a", &(param2_1.addr));
    scp_operand param2_2;
    param2_2.set = SCP_TRUE;
    param2_2.param_type = SCP_ASSIGN;

    param2.operand1 = &param2_1;
    param2.operand2 = &param2_2;*/

    scp_operand_pair *param3 = calloc(3, sizeof(scp_operand_pair));
    scp_operand param3_1;
    param3_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_b", &(param3_1.addr));
    scp_operand param3_2;
    param3_2.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("node1", &(param3_2.addr));

    param3[0].operand1 = &param3_1;
    param3[0].operand2 = &param3_2;

    scp_operand param3_1_1;
    param3_1_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_a", &(param3_1_1.addr));
    scp_operand param3_2_1;
    param3_2_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("iter_test1", &(param3_2_1.addr));

    param3[1].operand1 = &param3_1_1;
    param3[1].operand2 = &param3_2_1;

    /*scp_operand param3_1_2;
    param3_1_2.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_rel", &(param3_1_2.addr));
    scp_operand param3_2_2;
    param3_2_2.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("attr1", &(param3_2_2.addr));

    param3[2].operand1 = &param3_1_2;
    param3[2].operand2 = &param3_2_2;*/

    scp_operand param4;
    param4.element_type = scp_type_const;
    param4.param_type = SCP_ASSIGN;

    scp_sys_search(&param1, &param2, param3, 1, &param4, SCP_TRUE);
    //scp_sys_search_for_variables(&param1, &param2, 1, param3, 1, &param4);

    printEl(&param4);

    //printf("VAR=%d|%d\n", param3_1.addr.seg, param3_1.addr.offset);

    free(param3);
    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);
}

void test_system_operator_gen()
{
    GTimer *timer = 0;
    timer = g_timer_new();
    g_timer_start(timer);

    scp_operand param1;
    sc_helper_resolve_system_identifier("pattern4", &(param1.addr));
    param1.param_type = SCP_FIXED;

    //scp_operand param2;
    //param2.param_type = SCP_ASSIGN;

    scp_operand_pair param2;
    scp_operand param2_1;
    param2_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_e", &(param2_1.addr));
    scp_operand param2_2;
    param2_2.param_type = SCP_ASSIGN;

    param2.operand1 = &param2_1;
    param2.operand2 = &param2_2;

    scp_operand_pair *param3 = calloc(3, sizeof(scp_operand_pair));
    scp_operand param3_1;
    param3_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_b", &(param3_1.addr));
    scp_operand param3_2;
    param3_2.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("node1", &(param3_2.addr));

    param3[0].operand1 = &param3_1;
    param3[0].operand2 = &param3_2;

    scp_operand param3_1_1;
    param3_1_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("_a", &(param3_1_1.addr));
    scp_operand param3_2_1;
    param3_2_1.param_type = SCP_FIXED;
    sc_helper_resolve_system_identifier("iter_test1", &(param3_2_1.addr));

    param3[1].operand1 = &param3_1_1;
    param3[1].operand2 = &param3_2_1;

    scp_operand param4;
    param4.element_type = scp_type_const;
    param4.param_type = SCP_ASSIGN;

    //scp_sys_search(&param1, &param2, &param3, 1, &param4, SCP_TRUE);
    scp_sys_gen_for_variables(&param1, &param2, 1, param3, 0, &param4);

    printEl(&param4);

    //printf("VAR=%d|%d\n", param3_1.addr.seg, param3_1.addr.offset);

    free(param3);
    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);
}

void print_test()
{
    scp_operand param1;
    sc_helper_resolve_system_identifier("hypermedia_nrel_system_identifier", &(param1.addr));
    param1.element_type = scp_type_node | scp_type_const;
    param1.param_type = SCP_FIXED;

    printEl(&param1);
}

int main(void)
{
    scp_lib_init((sc_char *)"repo", (sc_char *)"test.ini");
    test_system_operator_gen();
    return 0;
    scp_operand param1;
    param1.element_type = scp_type_node | scp_type_const;
    param1.param_type = SCP_ASSIGN;

    genEl(&param1);

    param1.param_type = SCP_FIXED;

    printEl(&param1);

    scp_operand param2;
    param2.element_type = scp_type_const;
    param2.param_type = SCP_ASSIGN;

    scp_operand param3;
    param3.element_type = scp_type_node | scp_type_const;
    param3.param_type = SCP_ASSIGN;

    scp_operand param4;
    param4.element_type = scp_type_const;
    param4.param_type = SCP_ASSIGN;

    scp_operand param5;
    param5.element_type = scp_type_node | scp_type_const;
    param5.param_type = SCP_ASSIGN;

    genElStr5(&param1, &param2, &param3, &param4, &param5);

    printEl(&param1);

    param1.param_type = SCP_FIXED;
    param2.param_type = SCP_ASSIGN;
    param3.param_type = SCP_ASSIGN;
    param4.param_type = SCP_ASSIGN;
    param5.param_type = SCP_FIXED;
    scp_result res = searchElStr5(&param1, &param2, &param3, &param4, &param5);

    if (res == SCP_RESULT_TRUE)
    {
        printf("TRUE\n");
    }
    if (res == SCP_RESULT_FALSE)
    {
        printf("FALSE\n");
    }
    if (res == SCP_RESULT_ERROR)
    {
        printf("ERROR\n");
    }

    if (param1.param_type == SCP_ASSIGN)
    {
        printEl(&param1);
    }
    if (param2.param_type == SCP_ASSIGN)
    {
        printEl(&param2);
    }
    if (param3.param_type == SCP_ASSIGN)
    {
        printEl(&param3);
    }
    if (param4.param_type == SCP_ASSIGN)
    {
        printEl(&param4);
    }
    if (param5.param_type == SCP_ASSIGN)
    {
        printEl(&param5);
    }

    param1.erase = SCP_TRUE;
    param1.param_type = SCP_ASSIGN;
    param2.erase = SCP_TRUE;
    param2.param_type = SCP_ASSIGN;
    param3.erase = SCP_TRUE;
    param3.param_type = SCP_ASSIGN;
    param4.erase = SCP_TRUE;
    param4.param_type = SCP_ASSIGN;
    param5.erase = SCP_TRUE;
    param5.param_type = SCP_FIXED;

    eraseSetStr5(&param1, &param2, &param3, &param4, &param5);

    printf("PRINT:\n");

    printEl(&param1);
    printEl(&param2);
    printEl(&param3);
    printEl(&param4);
    printEl(&param5);

    //scp_lib_shutdown();

    sc_addr link;
    sc_helper_resolve_system_identifier("link1", &link);
    param1.addr = link;
    printNl(&param1);
    return 0;
}
