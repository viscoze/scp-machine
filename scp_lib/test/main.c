#include "scp_functions.h"
#include "scp_types.h"

int main (void)
{
    scp_element param;
    param.element_type=scp_type_node|scp_type_const;
    param.param_type=SCP_ASSIGN;

    genEl(&param);

    return 0;
}
