
#include "scp_interpreter.h"
#include "sc_helper.h"
#include "sc_memory_headers.h"

#include <stdio.h>

void create_process_test()
{
    sc_addr quest, prog;
    sc_helper_resolve_system_identifier("question_scp_interpretation_request", &quest);
    sc_helper_resolve_system_identifier("quest1", &prog);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, prog);



}

void test1()
{
    sc_addr node;
    node = sc_memory_node_new(0);
    //sc_memory_element_free(node);
    if (SC_FALSE == sc_memory_is_element(node))
    {
        printf("FALSE\n");
    }
    else
    {
        printf("TRUE\n");
    }
}

int main(void)
{
    scp_interpreter_init((sc_char *)"repo", (sc_char *)"test.ini");

    //test1();
    create_process_test();

    return 0;
}
