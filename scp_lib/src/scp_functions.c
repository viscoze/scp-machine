/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2013 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "sc_memory_headers.h"
#include "sc_helper.h"

#include "scp_functions.h"
#include "scp_searchElStr3.h"
#include "scp_searchElStr5.h"
#include "scp_searchSetStr3.h"
#include "scp_searchSetStr5.h"
#include "scp_genElStr3.h"
#include "scp_genElStr5.h"
#include "scp_eraseElStr3.h"
#include "scp_eraseElStr5.h"
#include "scp_eraseSetStr3.h"
#include "scp_eraseSetStr5.h"
#include "scp_utils.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

scp_result scp_lib_init()
{
    //! TODO Add keynodes loading
    return SCP_RESULT_TRUE;
}

scp_result scp_lib_shutdown()
{
    //sc_memory_shutdown();
    //sc_helper_shutdown();
    return SCP_RESULT_TRUE;
}

scp_result scp_lib_resolve_system_identifier(const char *idtf, scp_operand *param)
{
    if (SC_TRUE == sc_helper_resolve_system_identifier(idtf, &(param->addr)))
    {
        return SCP_RESULT_TRUE;
    }
    else
    {
        return SCP_RESULT_ERROR;
    }
}

scp_result genEl(scp_operand *param)
{
    if (param->param_type != SCP_ASSIGN)
    {
        return print_error("genEl", "Parameter must have ASSIGN modifier");
    }
    if ((param->element_type & scp_type_node) != scp_type_node)
    {
        return print_error("genEl", "Only node element can be generated. Use genElStr3 for arcs");
    }
    param->addr = sc_memory_node_new(param->element_type);
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return print_error("genEl", "Element cannot be generated");
    }
    return SCP_RESULT_TRUE;
}

scp_result genElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed = 0;
    if (param2->param_type == SCP_FIXED)
    {
        return print_error("genElStr3", "Parameter 2 must have ASSIGN modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("genElStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("genElStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed3);
    switch (fixed)
    {
        case 0x101:
            return genElStr3_f_a_f(param1, param2, param3);
        case 0x100:
            return genElStr3_a_a_f(param1, param2, param3);
        case 0x001:
            return genElStr3_f_a_a(param1, param2, param3);
        case 0x000:
            return genElStr3_a_a_a(param1, param2, param3);
        default:
            return print_error("genElStr3", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result genElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed5 = 0;
    sc_uint32 fixed = 0;
    if (param2->param_type == SCP_FIXED)
    {
        return print_error("genElStr5", "Parameter 2 must have ASSIGN modifier");
    }
    if (param4->param_type == SCP_FIXED)
    {
        return print_error("genElStr5", "Parameter 4 must have ASSIGN modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("genElStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            printEl(param1);
            return print_error("genElStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return print_error("genElStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed5 = 0x10000;
    }
    fixed = (fixed1 | fixed3 | fixed5);
    switch (fixed)
    {
        case 0x10101:
            return genElStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x00101:
            return genElStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x10001:
            return genElStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
        case 0x10100:
            return genElStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x10000:
            return genElStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
        case 0x00100:
            return genElStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x00001:
            return genElStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
        case 0x00000:
            return genElStr5_a_a_a_a_a(param1, param2, param3, param4, param5);
        default:
            return print_error("genElStr5", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result searchElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed = 0;
    if (param1->param_type == SCP_ASSIGN && param2->param_type == SCP_ASSIGN && param3->param_type == SCP_ASSIGN)
    {
        return print_error("searchElStr3", "At least one operand must have FIXED modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("searchElStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return print_error("searchElStr3", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param2->addr, scp_type_node))
        {
            return print_error("searchElStr3", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("searchElStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed2 | fixed3);
    switch (fixed)
    {
        case 0x001:
            return searchElStr3_f_a_a(param1, param2, param3);
        case 0x010:
            return searchElStr3_a_f_a(param1, param2, param3);
        case 0x100:
            return searchElStr3_a_a_f(param1, param2, param3);
        case 0x011:
            return searchElStr3_f_f_a(param1, param2, param3);
        case 0x101:
            return searchElStr3_f_a_f(param1, param2, param3);
        case 0x110:
            return searchElStr3_a_f_f(param1, param2, param3);
        case 0x111:
            return searchElStr3_f_f_f(param1, param2, param3);
        default:
            return print_error("searchElStr3", "Unsupported parameter type combination");
    }

    return SCP_RESULT_ERROR;
}

scp_result searchSetStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *sets)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed = 0;
    if (param2->param_type == SCP_FIXED)
    {
        return print_error("searchSetStr3", "Parameter 2 must have ASSIGN modifier");
    }
    if (param1->param_type == SCP_ASSIGN && param2->param_type == SCP_ASSIGN && param3->param_type == SCP_ASSIGN)
    {
        return print_error("searchSetStr3", "At least one operand must have FIXED modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SCP_TRUE == sets[0].set)
        {
            return print_error("searchSetStr3", "Parameter 1 has modifier FIXED, but marked as SET");
        }
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("searchSetStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SCP_TRUE == sets[2].set)
        {
            return print_error("searchSetStr3", "Parameter 3 has modifier FIXED, but marked as SET");
        }
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("searchSetStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed2 | fixed3);
    switch (fixed)
    {
        case 0x001:
            return searchSetStr3_f_a_a(param1, param2, param3, sets);
        case 0x100:
            return searchSetStr3_a_a_f(param1, param2, param3, sets);
        case 0x101:
            return searchSetStr3_f_a_f(param1, param2, param3, sets);
        default:
            return print_error("searchElStr3", "Unsupported parameter type combination");
    }

    return SCP_RESULT_ERROR;
}

scp_result searchElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed4 = 0;
    sc_uint32 fixed5 = 0;
    sc_uint32 fixed = 0;
    if (param1->param_type == SCP_ASSIGN && param2->param_type == SCP_ASSIGN && param3->param_type == SCP_ASSIGN && param4->param_type == SCP_ASSIGN && param5->param_type == SCP_ASSIGN)
    {
        return print_error("searchElStr5", "At least one operand must have FIXED modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("searchElStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return print_error("searchElStr5", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param2->addr, scp_type_node))
        {
            return print_error("searchElStr5", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("searchElStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param4->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param4->addr))
        {
            return print_error("searchElStr5", "Parameter 4 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param4->addr, scp_type_node))
        {
            return print_error("searchElStr5", "Parameter 4 is not an arc");
        }
        fixed4 = 0x1000;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return print_error("searchElStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed5 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x11111:
            return searchElStr5_f_f_f_f_f(param1, param2, param3, param4, param5);
        case 0x10101:
            return searchElStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x10001:
            return searchElStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
        case 0x00101:
            return searchElStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x10100:
            return searchElStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x00100:
            return searchElStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x00001:
            return searchElStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
        case 0x10000:
            return searchElStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
        default:
            return print_error("searchElStr5", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result searchSetStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5, scp_operand *sets)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed4 = 0;
    sc_uint32 fixed5 = 0;
    sc_uint32 fixed = 0;
    if (param2->param_type == SCP_FIXED)
    {
        return print_error("searchSetStr5", "Parameter 2 must have ASSIGN modifier");
    }
    if (param4->param_type == SCP_FIXED)
    {
        return print_error("searchSetStr5", "Parameter 4 must have ASSIGN modifier");
    }

    if (param1->param_type == SCP_FIXED)
    {
        if (SCP_TRUE == sets[0].set)
        {
            return print_error("searchSetStr5", "Parameter 1 has modifier FIXED, but marked as SET");
        }
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("searchSetStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SCP_TRUE == sets[2].set)
        {
            return print_error("searchSetStr5", "Parameter 3 has modifier FIXED, but marked as SET");
        }
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("searchSetStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SCP_TRUE == sets[4].set)
        {
            return print_error("searchSetStr5", "Parameter 5 has modifier FIXED, but marked as SET");
        }
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return print_error("searchSetStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed5 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x10101:
            return searchSetStr5_f_a_f_a_f(param1, param2, param3, param4, param5, sets);
        case 0x10001:
            return searchSetStr5_f_a_a_a_f(param1, param2, param3, param4, param5, sets);
        case 0x00101:
            return searchSetStr5_f_a_f_a_a(param1, param2, param3, param4, param5, sets);
        case 0x10100:
            return searchSetStr5_a_a_f_a_f(param1, param2, param3, param4, param5, sets);
        case 0x00100:
            return searchSetStr5_a_a_f_a_a(param1, param2, param3, param4, param5, sets);
        case 0x00001:
            return searchSetStr5_f_a_a_a_a(param1, param2, param3, param4, param5, sets);
        case 0x10000:
            return searchSetStr5_a_a_a_a_f(param1, param2, param3, param4, param5, sets);
        default:
            return print_error("searchSetStr5", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result eraseEl(scp_operand *param)
{
    if (param->param_type != SCP_FIXED)
    {
        return print_error("eraseEl", "Parameter must have FIXED modifier");
    }
    if (param->erase != SCP_TRUE)
    {
        return print_error("eraseEl", "Parameter must have ERASE modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return print_error("eraseEl", "Element has not value");
    }
    sc_memory_element_free(param->addr);
    SC_ADDR_MAKE_EMPTY(param->addr);
    return SCP_RESULT_TRUE;
}

scp_result eraseElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("eraseElStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return print_error("eraseElStr3", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param2->addr, scp_type_node))
        {
            return print_error("eraseElStr3", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("eraseElStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed2 | fixed3);
    switch (fixed)
    {
        case 0x001:
            return eraseElStr3_f_a_a(param1, param2, param3);
        case 0x100:
            return eraseElStr3_a_a_f(param1, param2, param3);
        case 0x101:
            return eraseElStr3_f_a_f(param1, param2, param3);
        default:
            return print_error("eraseElStr3", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result eraseElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed4 = 0;
    sc_uint32 fixed5 = 0;
    sc_uint32 fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("eraseElStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return print_error("eraseElStr5", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param2->addr, scp_type_node))
        {
            return print_error("eraseElStr5", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("eraseElStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param4->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param4->addr))
        {
            return print_error("eraseElStr5", "Parameter 4 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param4->addr, scp_type_node))
        {
            return print_error("eraseElStr5", "Parameter 4 is not an arc");
        }
        fixed2 = 0x1000;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return print_error("eraseElStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed3 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x10101:
            return eraseElStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x10001:
            return eraseElStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
        case 0x00101:
            return eraseElStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x10100:
            return eraseElStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x00100:
            return eraseElStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x00001:
            return eraseElStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
        case 0x10000:
            return eraseElStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
        default:
            return print_error("eraseElStr5", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result eraseSetStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("eraseSetStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return print_error("eraseSetStr3", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param2->addr, scp_type_node))
        {
            return print_error("eraseSetStr3", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("eraseSetStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed2 | fixed3);
    switch (fixed)
    {
        case 0x001:
            return eraseSetStr3_f_a_a(param1, param2, param3);
        case 0x100:
            return eraseSetStr3_a_a_f(param1, param2, param3);
        case 0x101:
            return eraseSetStr3_f_a_f(param1, param2, param3);
        default:
            return print_error("eraseSetStr3", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result eraseSetStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    sc_uint32 fixed1 = 0;
    sc_uint32 fixed2 = 0;
    sc_uint32 fixed3 = 0;
    sc_uint32 fixed4 = 0;
    sc_uint32 fixed5 = 0;
    sc_uint32 fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error("eraseSetStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return print_error("eraseSetStr5", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param2->addr, scp_type_node))
        {
            return print_error("eraseSetStr5", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return print_error("eraseSetStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param4->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param4->addr))
        {
            return print_error("eraseSetStr5", "Parameter 4 has modifier FIXED, but has not value");
        }
        if (SCP_RESULT_TRUE == check_type(param4->addr, scp_type_node))
        {
            return print_error("eraseSetStr5", "Parameter 4 is not an arc");
        }
        fixed2 = 0x1000;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return print_error("eraseSetStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed3 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x10101:
            return eraseSetStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x10001:
            return eraseSetStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
        case 0x00101:
            return eraseSetStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x10100:
            return eraseSetStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
        case 0x00100:
            return eraseSetStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
        case 0x00001:
            return eraseSetStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
        case 0x10000:
            return eraseSetStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
        default:
            return print_error("eraseSetStr5", "Unsupported parameter type combination");
    }
    return SCP_RESULT_ERROR;
}

scp_result ifVarAssign(scp_operand *param)
{
    if (SC_FALSE == sc_memory_is_element(param->addr))
        return SCP_RESULT_FALSE;
    else
        return SCP_RESULT_TRUE;
}

scp_result ifCoin(scp_operand *param1, scp_operand *param2)
{
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error("ifCoin", "Parameter 1 has no value");
    }
    if (SC_FALSE == sc_memory_is_element(param2->addr))
    {
        return print_error("ifCoin", "Parameter 2 has no value");
    }
    if (SC_ADDR_IS_EQUAL(param1->addr, param2->addr))
        return SCP_RESULT_TRUE;
    else
        return SCP_RESULT_FALSE;
}

scp_result ifType(scp_operand *param)
{
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return print_error("ifType", "Parameter has no value");
    }
    return check_type(param->addr, param->element_type);
}

scp_result printEl(scp_operand *param)
{
    sc_addr element = param->addr;
    sc_addr addr2, addr3;
    sc_addr idtf;
    sc_iterator3 *it = nullptr;
    sc_uint32 out_c = 0, in_c = 0;
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return print_error("printEl", "Parameter has not value");
    }
    if (SC_RESULT_OK == sc_helper_get_system_identifier(element, &idtf))
    {
        sc_stream *stream;
        sc_uint32 length = 0, read_length = 0;
        sc_char *data;
        sc_memory_get_link_content(idtf, &stream);
        sc_stream_get_length(stream, &length);
        data = calloc(length + 1, sizeof(sc_char));
        sc_stream_read_data(stream, data, length, &read_length);
        data[length] = '\0';
        printf("\nPrint element: %s =\n", data);
        sc_stream_free(stream);
        free(data);
    }
    else
    {
        printf("\nPrint element: %u|%u =\n", element.seg, element.offset);
    }

    it = sc_iterator3_a_a_f_new(0, 0, element);
    if (it == 0)
    {
        return SCP_RESULT_ERROR;
    }
    printf("Input arcs:\n");
    while (SC_TRUE == sc_iterator3_next(it))
    {
        in_c++;
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);

        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr3, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            if (SCP_RESULT_TRUE == check_type(addr3, scp_type_arc_access))
            {
                printf("\t%s <- ", data);
            }
            else
            {
                printf("\t%s <= ", data);
            }
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            if (SCP_RESULT_TRUE == check_type(addr3, scp_type_arc_access))
            {
                printf("\t%u|%u <- ", addr3.seg, addr3.offset);
            }
            else
            {
                printf("\t%u|%u <= ", addr3.seg, addr3.offset);
            }
        }
        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr2, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            printf("%s;\n", data);
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            printf("%u|%u;\n", addr2.seg, addr2.offset);
        }
    }
    sc_iterator3_free(it);
    printf("Total input arcs: %d\n", in_c);

    it = sc_iterator3_f_a_a_new(element, 0, 0);
    if (it == 0)
    {
        return SCP_RESULT_ERROR;
    }
    printf("Output arcs:\n");
    while (SC_TRUE == sc_iterator3_next(it))
    {
        out_c++;
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);

        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr2, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            if (SCP_RESULT_TRUE == check_type(addr2, scp_type_arc_access))
            {
                printf("\t%s -> ", data);
            }
            else
            {
                printf("\t%s => ", data);
            }
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            if (SCP_RESULT_TRUE == check_type(addr2, scp_type_arc_access))
            {
                printf("\t%u|%u -> ", addr2.seg, addr2.offset);
            }
            else
            {
                printf("\t%u|%u => ", addr2.seg, addr2.offset);
            }

        }
        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr3, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            printf("%s;\n", data);
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            printf("%u|%u;\n", addr3.seg, addr3.offset);
        }
    }
    sc_iterator3_free(it);
    printf("Total output arcs: %d\n", out_c);
    return SCP_RESULT_TRUE;
}

scp_result printL(scp_operand *param, sc_bool new_line)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data;
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return print_error("print", "Parameter has not value");
    }
    /*if (SCP_RESULT_FALSE == check_type(param->addr, sc_type_link))
    {
        return print_error("print", "Parameter is not an sc-link");
    }*/
    if (sc_memory_get_link_content(param->addr, &stream) != SC_RESULT_OK)
    {
        return print_error("print", "Content reading error");
    }
    sc_stream_get_length(stream, &length);
    data = calloc(length + 1, sizeof(sc_char));
    sc_stream_read_data(stream, data, length, &read_length);
    data[length] = '\0';
    printf("%s", data);
    if (SC_TRUE == new_line)
    {
        printf("\n");
    }
    sc_stream_free(stream);
    free(data);
    return SCP_RESULT_TRUE;
}

scp_result print(scp_operand *param)
{
    return printL(param, SC_FALSE);
}

scp_result printNl(scp_operand *param)
{
    return printL(param, SC_TRUE);
}

scp_result varAssign(scp_operand *param1, scp_operand *param2)
{
    if (SCP_FIXED == param1->param_type)
    {
        return print_error("varAssign", "Parameter 1 must have ASSIGN modifier");
    }
    if (SCP_ASSIGN == param2->param_type)
    {
        return print_error("varAssign", "Parameter 2 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param2->addr))
    {
        return print_error("varAssign", "Parameter 2 has not value");
    }
    param1->addr = param2->addr;
    return SCP_RESULT_TRUE;
}

scp_result ifFormCont(scp_operand *param)
{
    sc_stream *stream;
    if (SCP_ASSIGN == param->param_type)
    {
        return print_error("ifFormCont", "Parameter must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return print_error("ifFormCont", "Parameter has not value");
    }
    if (check_type(param->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error("ifFormCont", "Parameter must have link type");
    }
    sc_result res = sc_memory_get_link_content(param->addr, &stream);
    if (res == SC_RESULT_OK)
    {
        sc_stream_free(stream);
        return SCP_RESULT_TRUE;
    }
    else
    {
        return SCP_RESULT_FALSE;
    }
    return SCP_RESULT_ERROR;
}

scp_result contAssign(scp_operand *param1, scp_operand *param2)
{
    sc_stream *stream;
    sc_char *data;
    sc_uint32 length, read_length;
    if (SCP_ASSIGN == param2->param_type)
    {
        return print_error("contAssign", "Parameter 2 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param2->addr))
    {
        return print_error("contAssign", "Parameter 2 has not value");
    }
    if (check_type(param2->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error("contAssign", "Parameter 2 must have link type");
    }
    if (sc_memory_get_link_content(param2->addr, &stream) != SC_RESULT_OK)
    {
        return print_error("contAssign", "Parameter 2 content reading error");
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contAssign", param1))
    {
        return SCP_RESULT_ERROR;
    }
    sc_stream_get_length(stream, &length);
    data = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data, length, &read_length);
    sc_stream_free(stream);

    sc_stream_memory_new(data, length, SC_STREAM_READ, SC_FALSE);
    sc_memory_set_link_content(param1->addr, stream);
    sc_stream_free(stream);
    return SCP_RESULT_TRUE;
}

scp_result contErase(scp_operand *param1)
{
    return SCP_RESULT_TRUE;
}

scp_result ifEq(scp_operand *param1, scp_operand *param2)
{
    double num1, num2;
    if (SCP_RESULT_ERROR == resolve_numbers_1_2("ifEq", param1, param2, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (num1 == num2)
    {
        return SCP_RESULT_TRUE;
    }
    else
    {
        return SCP_RESULT_FALSE;
    }
    return SCP_RESULT_ERROR;
}

scp_result ifGr(scp_operand *param1, scp_operand *param2)
{
    double num1, num2;
    if (SCP_RESULT_ERROR == resolve_numbers_1_2("ifGr", param1, param2, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (num1 > num2)
    {
        return SCP_RESULT_TRUE;
    }
    else
    {
        return SCP_RESULT_FALSE;
    }
    return SCP_RESULT_ERROR;
}

scp_result contLn(scp_operand *param1, scp_operand *param2)
{
    double num;
    if (SCP_RESULT_ERROR == resolve_number_2("contLn", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contLn", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(log(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contCos(scp_operand *param1, scp_operand *param2)
{
    double num;
    if (SCP_RESULT_ERROR == resolve_number_2("contCos", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contCos", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(cos(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contSin(scp_operand *param1, scp_operand *param2)
{
    double num;
    if (SCP_RESULT_ERROR == resolve_number_2("contSin", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contSin", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(sin(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contTg(scp_operand *param1, scp_operand *param2)
{
    double num;

    if (SCP_RESULT_ERROR == resolve_number_2("contTg", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contTg", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(tan(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contACos(scp_operand *param1, scp_operand *param2)
{
    double num;

    if (SCP_RESULT_ERROR == resolve_number_2("contACos", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contACos", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(acos(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contASin(scp_operand *param1, scp_operand *param2)
{
    double num;
    if (SCP_RESULT_ERROR == check_link_parameter_1("contASin", param1))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == resolve_number_2("contASin", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(asin(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contATg(scp_operand *param1, scp_operand *param2)
{
    double num;

    if (SCP_RESULT_ERROR == check_link_parameter_1("contATg", param1))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == resolve_number_2("contATg", param2, &num))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(atan(num), param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contAdd(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    double num1, num2;
    if (SCP_RESULT_ERROR == resolve_numbers_2_3("contAdd", param2, param3, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contAdd", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(num1 + num2, param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contSub(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    double num1, num2;

    if (SCP_RESULT_ERROR == resolve_numbers_2_3("contSub", param2, param3, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contSub", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(num1 - num2, param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contMult(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    double num1, num2;

    if (SCP_RESULT_ERROR == resolve_numbers_2_3("contMult", param2, param3, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contMult", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(num1 * num2, param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contDiv(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    double num1, num2;

    if (SCP_RESULT_ERROR == resolve_numbers_2_3("contDiv", param2, param3, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contDiv", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(num1 / num2, param1->addr);
    return SCP_RESULT_TRUE;
}

scp_result contPow(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    double num1, num2;

    if (SCP_RESULT_ERROR == resolve_numbers_2_3("contPow", param2, param3, &num1, &num2))
    {
        return SCP_RESULT_ERROR;
    }
    if (SCP_RESULT_ERROR == check_link_parameter_1("contPow", param1))
    {
        return SCP_RESULT_ERROR;
    }
    write_link_content_number(pow(num1, num2), param1->addr);
    return SCP_RESULT_TRUE;
}
