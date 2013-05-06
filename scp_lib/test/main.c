#include "scp_functions.h"
#include "scp_types.h"
#include <stdio.h>

int main (void)
{
    scp_lib_init((sc_char*)"repo",(sc_char*)"test.ini");

    scp_operand param;
    param.element_type=scp_type_node|scp_type_const;
    param.param_type=SCP_ASSIGN; 

    genEl(&param);
    printEl(&param);

    scp_lib_shutdown();
    return 0;
}
