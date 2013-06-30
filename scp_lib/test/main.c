#include "scp_functions.h"
#include "scp_types.h"
#include <stdio.h>
#include "sc_memory.h"
#include "sc_iterator3.h"

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

int main(void)
{
    scp_lib_init((sc_char *)"repo", (sc_char *)"test.ini");
    //foo();
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

    if (res == SCP_TRUE)
    {
        printf("TRUE\n");
    }
    if (res == SCP_FALSE)
    {
        printf("FALSE\n");
    }
    if (res == SCP_ERROR)
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

    param1.erase = SCP_ERASE_FALSE;
    param1.param_type = SCP_ASSIGN;
    param2.erase = SCP_ERASE_TRUE;
    param2.param_type = SCP_ASSIGN;
    param3.erase = SCP_ERASE_FALSE;
    param3.param_type = SCP_ASSIGN;
    param4.erase = SCP_ERASE_FALSE;
    param4.param_type = SCP_ASSIGN;
    param5.erase = SCP_ERASE_FALSE;
    param5.param_type = SCP_FIXED;

    eraseSetStr5(&param1, &param2, &param3, &param4, &param5);

    printf("PRINT:\n");

    printEl(&param1);
    printEl(&param2);
    printEl(&param3);
    printEl(&param4);
    printEl(&param5);

    //scp_lib_shutdown();
    return 0;
}
