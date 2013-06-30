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

#include "scp_eraseSetStr3.h"
#include "scp_utils.h"
#include "sc_memory.h"
#include "sc_iterator3.h"

scp_result eraseSetStr3_a_a_f(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_iterator3 *it = sc_iterator3_a_a_f_new(param1->element_type, param2->element_type, param3->addr);
    sc_bool flag = SC_FALSE;
    while (sc_iterator3_next(it))
    {
        flag = SC_TRUE;
        sc_memory_element_free(sc_iterator3_value(it, 0));
    }
    if (param3->erase == SCP_ERASE_TRUE)
    {
        sc_memory_element_free(param3->addr);
    }
    sc_iterator3_free(it);
    if (flag == SC_TRUE)
        return SCP_TRUE;
    else
        return SCP_FALSE;
}

scp_result eraseSetStr3_f_a_a(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_iterator3 *it = sc_iterator3_f_a_a_new(param1->addr, param2->element_type, param3->element_type);
    sc_bool flag = SC_FALSE;
    while (sc_iterator3_next(it))
    {
        flag = SC_TRUE;
        sc_memory_element_free(sc_iterator3_value(it, 2));
    }
    if (param1->erase == SCP_ERASE_TRUE)
    {
        sc_memory_element_free(param1->addr);
    }
    sc_iterator3_free(it);
    if (flag == SC_TRUE)
        return SCP_TRUE;
    else
        return SCP_FALSE;
}

scp_result eraseSetStr3_f_a_f(scp_operand *param1, scp_operand *param2, scp_operand *param3)
{
    sc_iterator3 *it = sc_iterator3_f_a_f_new(param1->addr, param2->element_type, param3->addr);
    sc_bool flag = SC_FALSE;
    while (sc_iterator3_next(it))
    {
        flag = SC_TRUE;
        sc_memory_element_free(sc_iterator3_value(it, 1));
    }
    if (param1->erase == SCP_ERASE_TRUE)
    {
        sc_memory_element_free(param1->addr);
    }
    if (param3->erase == SCP_ERASE_TRUE)
    {
        sc_memory_element_free(param3->addr);
    }
    sc_iterator3_free(it);
    if (flag == SC_TRUE)
        return SCP_TRUE;
    else
        return SCP_FALSE;
}

