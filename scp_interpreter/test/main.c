
#include "scp_interpreter.h"
#include "sc_helper.h"
#include "sc_memory_headers.h"

#include <stdio.h>

void create_process_test(){
    sc_addr quest,prog;
    sc_helper_resolve_system_identifier("question_scp_interpretation_request",&quest);
    sc_helper_resolve_system_identifier("test_prog1",&prog);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,prog);
}

int main(void)
{
    scp_interpreter_init((sc_char *)"repo", (sc_char *)"test.ini");

    //printf("EQUALS=%d\n",(0&33)==0);

    create_process_test();

    return 0;
}
