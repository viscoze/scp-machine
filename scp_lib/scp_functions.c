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

#include "scp_functions.h"
#include "scp_searchElStr3.h"
#include "scp_searchElStr5.h"
#include "scp_genElStr3.h"
#include "scp_genElStr5.h"
#include "scp_eraseElStr3.h"
#include "scp_eraseElStr5.h"
#include "scp_eraseSetStr3.h"
#include "scp_eraseSetStr5.h"
#include "scp_utils.h"
#include "sc_stream.h"
#include "sc_helper.h"
#include "sc_memory.h"
#include "sc_iterator3.h"
#include <stdio.h>
#include <malloc.h>

scp_result printError(const char *operator_name, const char *text)
{
    printf("\nSCP LIBRARY ERROR: %s : %s\n", operator_name, text);
    return SCP_ERROR;
}

scp_result scp_lib_init(const sc_char *repo_path, const sc_char *config_file)
{
    if (sc_memory_initialize(repo_path, config_file) == SC_FALSE)
    {
        return SCP_FALSE;
    }
    sc_helper_init();
    return SCP_TRUE;
}

scp_result scp_lib_shutdown()
{
    sc_memory_shutdown();
    sc_helper_shutdown();
    return SCP_TRUE;
}

scp_result genEl(scp_operand *param)
{
    if (param->param_type != SCP_ASSIGN)
    {
        return printError("genEl", "Parameter must have ASSIGN modifier");
    }
    if ((param->element_type & scp_type_node) != scp_type_node)
    {
        return printError("genEl", "Only node element can be generated. Use genElStr3 for arcs");
    }
    param->addr = sc_memory_node_new(param->element_type);
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return printError("genEl", "Element cannot be generated");
    }
    return SCP_TRUE;
}

scp_result genElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_bool fixed1 = SC_FALSE;
    sc_bool fixed3 = SC_FALSE;
    if (param2->param_type == SCP_FIXED)
    {
        return printError("genElStr3", "Parameter 2 must have ASSIGN modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("genElStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = SC_TRUE;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("genElStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = SC_TRUE;
    }
    if (fixed1 == SC_TRUE && fixed3 == SC_TRUE)
    {
        return genElStr3_f_a_f(param1, param2, param3);
    }
    if (fixed1 != SC_TRUE && fixed3 == SC_TRUE)
    {
        return genElStr3_a_a_f(param1, param2, param3);
    }
    if (fixed1 == SC_TRUE && fixed3 != SC_TRUE)
    {
        return genElStr3_f_a_a(param1, param2, param3);
    }
    if (fixed1 != SC_TRUE && fixed3 != SC_TRUE)
    {
        return genElStr3_a_a_a(param1, param2, param3);
    }
    return SCP_ERROR;
}

scp_result genElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    sc_bool fixed1 = SC_FALSE;
    sc_bool fixed3 = SC_FALSE;
    sc_bool fixed5 = SC_FALSE;
    if (param2->param_type == SCP_FIXED)
    {
        return printError("genElStr5", "Parameter 2 must have ASSIGN modifier");
    }
    if (param4->param_type == SCP_FIXED)
    {
        return printError("genElStr5", "Parameter 4 must have ASSIGN modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("genElStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = SC_TRUE;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("genElStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = SC_TRUE;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return printError("genElStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed5 = SC_TRUE;
    }
    if (fixed1 == SC_TRUE && fixed3 == SC_TRUE && fixed5 == SC_TRUE)
    {
        return genElStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
    }
    if (fixed1 != SC_TRUE && fixed3 == SC_TRUE && fixed5 == SC_TRUE)
    {
        return genElStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
    }
    if (fixed1 == SC_TRUE && fixed3 != SC_TRUE && fixed5 == SC_TRUE)
    {
        return genElStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
    }
    if (fixed1 == SC_TRUE && fixed3 == SC_TRUE && fixed5 != SC_TRUE)
    {
        return genElStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
    }
    if (fixed1 != SC_TRUE && fixed3 != SC_TRUE && fixed5 == SC_TRUE)
    {
        return genElStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
    }
    if (fixed1 != SC_TRUE && fixed3 == SC_TRUE && fixed5 != SC_TRUE)
    {
        return genElStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
    }
    if (fixed1 == SC_TRUE && fixed3 != SC_TRUE && fixed5 != SC_TRUE)
    {
        return genElStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
    }
    if (fixed1 != SC_TRUE && fixed3 != SC_TRUE && fixed5 != SC_TRUE)
    {
        return genElStr5_a_a_a_a_a(param1, param2, param3, param4, param5);
    }
    return SCP_ERROR;
}

scp_result searchElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_bool fixed1 = SC_FALSE;
    sc_bool fixed2 = SC_FALSE;
    sc_bool fixed3 = SC_FALSE;
    if (param1->param_type == SCP_ASSIGN && param2->param_type == SCP_ASSIGN && param3->param_type == SCP_ASSIGN)
    {
        return printError("searchElStr3", "At least one operand must have FIXED modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("searchElStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = SC_TRUE;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return printError("searchElStr3", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param2->addr, scp_type_node))
        {
            return printError("searchElStr3", "Parameter 2 is not an arc");
        }
        fixed2 = SC_TRUE;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("searchElStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = SC_TRUE;
    }
    if (fixed1 == SC_TRUE && fixed2 == SC_TRUE && fixed3 == SC_TRUE)
    {
        return searchElStr3_f_f_f(param1, param2, param3);
    }
    if (fixed1 != SC_TRUE && fixed2 == SC_TRUE && fixed3 == SC_TRUE)
    {
        return searchElStr3_a_f_f(param1, param2, param3);
    }
    if (fixed1 != SC_TRUE && fixed2 != SC_TRUE && fixed3 == SC_TRUE)
    {
        return searchElStr3_a_a_f(param1, param2, param3);
    }
    if (fixed1 != SC_TRUE && fixed2 == SC_TRUE && fixed3 != SC_TRUE)
    {
        return searchElStr3_a_f_a(param1, param2, param3);
    }
    if (fixed1 == SC_TRUE && fixed2 != SC_TRUE && fixed3 != SC_TRUE)
    {
        return searchElStr3_f_a_a(param1, param2, param3);
    }
    if (fixed1 == SC_TRUE && fixed2 == SC_TRUE && fixed3 != SC_TRUE)
    {
        return searchElStr3_f_f_a(param1, param2, param3);
    }
    if (fixed1 == SC_TRUE && fixed2 != SC_TRUE && fixed3 == SC_TRUE)
    {
        return searchElStr3_f_a_f(param1, param2, param3);
    }
    return SCP_ERROR;
}

scp_result searchElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    int fixed1 = 0;
    int fixed2 = 0;
    int fixed3 = 0;
    int fixed4 = 0;
    int fixed5 = 0;
    long fixed = 0;
    if (param1->param_type == SCP_ASSIGN && param2->param_type == SCP_ASSIGN && param3->param_type == SCP_ASSIGN && param4->param_type == SCP_ASSIGN && param5->param_type == SCP_ASSIGN)
    {
        return printError("searchElStr5", "At least one operand must have FIXED modifier");
    }
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("searchElStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return printError("searchElStr5", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param2->addr, scp_type_node))
        {
            return printError("searchElStr5", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("searchElStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param4->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param4->addr))
        {
            return printError("searchElStr5", "Parameter 4 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param4->addr, scp_type_node))
        {
            return printError("searchElStr5", "Parameter 4 is not an arc");
        }
        fixed4 = 0x1000;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return printError("searchElStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed5 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x11111:
            return searchElStr5_f_f_f_f_f(param1, param2, param3, param4, param5);
            break;
        case 0x10101:
            return searchElStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x10001:
            return searchElStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x00101:
            return searchElStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x10100:
            return searchElStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x00100:
            return searchElStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x00001:
            return searchElStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x10000:
            return searchElStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
            break;
        default:
            return printError("searchElStr5", "Unsupported parameter type combination");
    }
    return SCP_ERROR;
}

scp_result eraseEl(scp_operand *param)
{
    if (param->param_type != SCP_FIXED)
    {
        return printError("eraseEl", "Parameter must have FIXED modifier");
    }
    if (param->erase != SCP_ERASE_TRUE)
    {
        return printError("eraseEl", "Parameter must have ERASE_TRUE modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return printError("eraseEl", "Element has not value");
    }
    sc_memory_element_free(param->addr);
    SC_ADDR_MAKE_EMPTY(param->addr);
    return SCP_TRUE;
}

scp_result eraseElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    int fixed1 = 0;
    int fixed2 = 0;
    int fixed3 = 0;
    int fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("eraseElStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return printError("eraseElStr3", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param2->addr, scp_type_node))
        {
            return printError("eraseElStr3", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("eraseElStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed2 | fixed3);
    switch (fixed)
    {
        case 0x001:
            return eraseElStr3_f_a_a(param1, param2, param3);
            break;
        case 0x100:
            return eraseElStr3_a_a_f(param1, param2, param3);
            break;
        case 0x101:
            return eraseElStr3_f_a_f(param1, param2, param3);
            break;
        default:
            return printError("eraseElStr3", "Unsupported parameter type combination");
    }
    return SCP_ERROR;
}

scp_result eraseElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    int fixed1 = 0;
    int fixed2 = 0;
    int fixed3 = 0;
    int fixed4 = 0;
    int fixed5 = 0;
    int fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("eraseElStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return printError("eraseElStr5", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param2->addr, scp_type_node))
        {
            return printError("eraseElStr5", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("eraseElStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param4->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param4->addr))
        {
            return printError("eraseElStr5", "Parameter 4 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param4->addr, scp_type_node))
        {
            return printError("eraseElStr5", "Parameter 4 is not an arc");
        }
        fixed2 = 0x1000;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return printError("eraseElStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed3 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x10101:
            return eraseElStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x10001:
            return eraseElStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x00101:
            return eraseElStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x10100:
            return eraseElStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x00100:
            return eraseElStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x00001:
            return eraseElStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x10000:
            return eraseElStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
            break;
        default:
            return printError("eraseElStr5", "Unsupported parameter type combination");
    }
    return SCP_ERROR;
}

scp_result eraseSetStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    int fixed1 = 0;
    int fixed2 = 0;
    int fixed3 = 0;
    int fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("eraseSetStr3", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return printError("eraseSetStr3", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param2->addr, scp_type_node))
        {
            return printError("eraseSetStr3", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("eraseSetStr3", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    fixed = (fixed1 | fixed2 | fixed3);
    switch (fixed)
    {
        case 0x001:
            return eraseSetStr3_f_a_a(param1, param2, param3);
            break;
        case 0x100:
            return eraseSetStr3_a_a_f(param1, param2, param3);
            break;
        case 0x101:
            return eraseSetStr3_f_a_f(param1, param2, param3);
            break;
        default:
            return printError("eraseSetStr3", "Unsupported parameter type combination");
    }
    return SCP_ERROR;
}

scp_result eraseSetStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5)
{
    int fixed1 = 0;
    int fixed2 = 0;
    int fixed3 = 0;
    int fixed4 = 0;
    int fixed5 = 0;
    int fixed = 0;
    if (param1->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return printError("eraseSetStr5", "Parameter 1 has modifier FIXED, but has not value");
        }
        fixed1 = 0x1;
    }
    if (param2->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param2->addr))
        {
            return printError("eraseSetStr5", "Parameter 2 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param2->addr, scp_type_node))
        {
            return printError("eraseSetStr5", "Parameter 2 is not an arc");
        }
        fixed2 = 0x10;
    }
    if (param3->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param3->addr))
        {
            return printError("eraseSetStr5", "Parameter 3 has modifier FIXED, but has not value");
        }
        fixed3 = 0x100;
    }
    if (param4->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param4->addr))
        {
            return printError("eraseSetStr5", "Parameter 4 has modifier FIXED, but has not value");
        }
        if (SCP_TRUE == checkType(param4->addr, scp_type_node))
        {
            return printError("eraseSetStr5", "Parameter 4 is not an arc");
        }
        fixed2 = 0x1000;
    }
    if (param5->param_type == SCP_FIXED)
    {
        if (SC_FALSE == sc_memory_is_element(param5->addr))
        {
            return printError("eraseSetStr5", "Parameter 5 has modifier FIXED, but has not value");
        }
        fixed3 = 0x10000;
    }
    fixed = (fixed1 | fixed2 | fixed3 | fixed4 | fixed5);
    switch (fixed)
    {
        case 0x10101:
            return eraseSetStr5_f_a_f_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x10001:
            return eraseSetStr5_f_a_a_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x00101:
            return eraseSetStr5_f_a_f_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x10100:
            return eraseSetStr5_a_a_f_a_f(param1, param2, param3, param4, param5);
            break;
        case 0x00100:
            return eraseSetStr5_a_a_f_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x00001:
            return eraseSetStr5_f_a_a_a_a(param1, param2, param3, param4, param5);
            break;
        case 0x10000:
            return eraseSetStr5_a_a_a_a_f(param1, param2, param3, param4, param5);
            break;
        default:
            return printError("eraseSetStr5", "Unsupported parameter type combination");
    }
    return SCP_ERROR;
}

scp_result ifVarAssign(scp_operand *param)
{
    if (SC_FALSE == sc_memory_is_element(param->addr))
        return SCP_FALSE;
    else
        return SCP_TRUE;
}

scp_result ifCoin(scp_operand *param1, scp_operand *param2)
{
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return printError("ifCoin", "Parameter 1 has no value");
    }
    if (SC_FALSE == sc_memory_is_element(param2->addr))
    {
        return printError("ifCoin", "Parameter 2 has no value");
    }
    if (SC_ADDR_IS_EQUAL(param1->addr, param2->addr))
        return SCP_TRUE;
    else
        return SCP_FALSE;
}

scp_result ifType(scp_operand *param)
{
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return printError("ifType", "Parameter has no value");
    }
    return checkType(param->addr, param->element_type);
}

scp_result printEl(scp_operand *param)
{
    sc_addr element = param->addr;
    sc_addr addr2, addr3;
    sc_addr idtf;
    sc_iterator3 *it = nullptr;
    if (SC_FALSE == sc_memory_is_element(param->addr))
    {
        return printError("printEl", "Parameter has not value");
    }
    if (SC_RESULT_OK == sc_helper_get_system_identifier(element, &idtf))
    {
        sc_stream *stream;
        sc_uint length = 0, read_length = 0;
        sc_char *data = calloc(length, sizeof(sc_char));
        sc_memory_get_link_content(idtf, &stream);
        sc_stream_get_length(stream, &length);
        sc_stream_read_data(stream, data, length, &read_length);
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
        return SCP_ERROR;
    }
    printf("Input arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);

        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr3, &idtf))
        {
            sc_stream *stream;
            sc_uint length = 0, read_length = 0;
            sc_char *data = calloc(length, sizeof(sc_char));
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            sc_stream_read_data(stream, data, length, &read_length);
            printf("\t%s <- ", data);
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            printf("\t%u|%u <- ", addr3.seg, addr3.offset);
        }
        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr2, &idtf))
        {
            sc_stream *stream;
            sc_uint length = 0, read_length = 0;
            sc_char *data = calloc(length, sizeof(sc_char));
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            sc_stream_read_data(stream, data, length, &read_length);
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

    it = sc_iterator3_f_a_a_new(element, 0, 0);
    if (it == 0)
    {
        return SCP_ERROR;
    }
    printf("Output arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);

        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr2, &idtf))
        {
            sc_stream *stream;
            sc_uint length = 0, read_length = 0;
            sc_char *data = calloc(length, sizeof(sc_char));
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            sc_stream_read_data(stream, data, length, &read_length);
            printf("\t%s -> ", data);
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            printf("\t%u|%u -> ", addr2.seg, addr2.offset);
        }
        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr3, &idtf))
        {
            sc_stream *stream;
            sc_uint length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
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
    return SCP_TRUE;
}
