#include "scp_functions.h"
#include "scp_types.h"
#include "sc_memory.h"
#include "sc_helper.h"
#include <stdio.h>

int main (void)
{
    sc_memory_initialize((sc_char*)"repo",(sc_char*)"test.ini");
    sc_helper_init();

    scp_operand param;
    param.element_type=scp_type_node|scp_type_const;
    param.param_type=SCP_ASSIGN; 

    //genEl(&param);
    printEl(&param);

    sc_helper_shutdown();
    return 0;
}
