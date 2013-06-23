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

#include "scp_searchElStr3.h"
#include "scp_utils.h"
#include "sc_memory.h"
#include "sc_iterator3.h"

scp_result searchElStr3_a_a_f(scp_operand *param1, scp_operand *param2, scp_operand *param3) {
    sc_iterator3 *it = sc_iterator3_a_a_f_new(param1->element_type, param2->element_type, param3->addr);
    if (sc_iterator3_next(it))
    {
        param1->addr = sc_iterator3_value(it, 0);
        param2->addr = sc_iterator3_value(it, 1);
        sc_iterator3_free(it);
        return SCP_TRUE;
    }
    sc_iterator3_free(it);
    return SCP_FALSE;
}
scp_result searchElStr3_f_a_a(scp_operand *param1, scp_operand *param2, scp_operand *param3) {
    sc_iterator3 *it = sc_iterator3_f_a_a_new(param1->addr, param2->element_type, param3->element_type);
    if (sc_iterator3_next(it))
    {
        param2->addr = sc_iterator3_value(it, 1);
        param3->addr = sc_iterator3_value(it, 2);
        sc_iterator3_free(it);
        return SCP_TRUE;
    }
    sc_iterator3_free(it);
    return SCP_FALSE;
}

scp_result searchElStr3_f_a_f(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_iterator3 *it = sc_iterator3_f_a_f_new(param1->addr, param2->element_type, param3->addr);
    if (sc_iterator3_next(it))
    {
        param2->addr = sc_iterator3_value(it, 1);
        sc_iterator3_free(it);
        return SCP_TRUE;
    }
    sc_iterator3_free(it);
    return SCP_FALSE;
}

scp_result searchElStr3_a_f_a(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_addr arc = param2->addr;
    sc_addr begin;
    sc_addr end;
    if (SC_RESULT_OK != sc_memory_get_arc_begin(arc, &begin))
    {
        return SCP_ERROR;
    }
    if (SC_RESULT_OK != sc_memory_get_arc_end(arc, &end))
    {
        return SCP_ERROR;
    }
    if (SCP_TRUE != checkType(begin, param1->element_type) && SCP_TRUE != checkType(end, param3->element_type))
    {
        param1->addr = begin;
        param3->addr = end;
        return SCP_TRUE;
    }
    else
    {
        return SCP_FALSE;
    }
}
scp_result searchElStr3_f_f_a(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_addr arc = param2->addr;
    sc_addr begin;
    if (SC_RESULT_OK != sc_memory_get_arc_begin(arc, &begin))
    {
        return SCP_ERROR;
    }
    if (SC_ADDR_IS_EQUAL(param1->addr, begin))
    {
        sc_addr end;
        if (SC_RESULT_OK != sc_memory_get_arc_end(arc, &end))
        {
            return SCP_ERROR;
        }
        if (SCP_TRUE != checkType(end, param3->element_type))
        {
            return SCP_FALSE;
        }
        param3->addr = end;
        return SCP_TRUE;
    }
    else
    {
        return SCP_FALSE;
    }
}
scp_result searchElStr3_a_f_f(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_addr arc = param2->addr;
    sc_addr end;
    if (SC_RESULT_OK != sc_memory_get_arc_end(arc, &end))
    {
        return SCP_ERROR;
    }
    if (SC_ADDR_IS_EQUAL(param3->addr, end))
    {
        sc_addr begin;
        if (SC_RESULT_OK != sc_memory_get_arc_begin(arc, &begin))
        {
            return SCP_ERROR;
        }
        if (SCP_TRUE != checkType(begin, param1->element_type))
        {
            return SCP_FALSE;
        }
        param1->addr = begin;
        return SCP_TRUE;
    }
    else
    {
        return SCP_FALSE;
    }
}

scp_result searchElStr3_f_f_f(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_addr arc = param2->addr;
    sc_addr begin;
    sc_addr end;
    if (SC_RESULT_OK != sc_memory_get_arc_begin(arc, &begin))
    {
        return SCP_ERROR;
    }
    if (SC_RESULT_OK != sc_memory_get_arc_end(arc, &end))
    {
        return SCP_ERROR;
    }
    if (SC_ADDR_IS_EQUAL(param1->addr, begin) && SC_ADDR_IS_EQUAL(param3->addr, end))
    {
        return SCP_TRUE;
    }
    else
    {
        return SCP_FALSE;
    }
}
