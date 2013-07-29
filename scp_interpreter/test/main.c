
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

int main(void)
{
    scp_interpreter_init((sc_char *)"repo", (sc_char *)"test.ini");

    /*scp_operand p;
    sc_helper_resolve_system_identifier("searchElStr5", &(p.addr));
    printEl(&p);*/


    create_process_test();

    return 0;
}
