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
#include "scp_operator_interpreter_agents.h"
#include "scp_operator_interpreter_functions.h"
#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"

#include <stdio.h>

sc_event *event_search_operators_interpreter;

sc_result interpreter_agent_search_operators(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, node1, operator_node, operator_type;

    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    if (SCP_RESULT_TRUE != ifVarAssign(&arc1))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &operator_node))
    {
        print_error("scp-operator interpreting", "Can't find operator node");
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    operator_node.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    if (SCP_RESULT_TRUE != resolve_operator_type(&operator_node, &operator_type))
    {
        print_error("scp-operator interpreting", "Can't resolve operator type");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_searchElStr3))
    {
        scp_operand operands[3];
        if (SCP_RESULT_TRUE != resolve_operand_modifiers(&operator_node, operands, &rrel_1))
        {
            return SC_RESULT_ERROR;
        }
        if (SCP_RESULT_TRUE != resolve_operand_modifiers(&operator_node, operands + 1, &rrel_2))
        {
            return SC_RESULT_ERROR;
        }
        if (SCP_RESULT_TRUE != resolve_operand_modifiers(&operator_node, operands + 2, &rrel_3))
        {
            return SC_RESULT_ERROR;
        }
        resolve_operands_values(&operator_node, operands, 3);

        // !TODO searchElStr3

        // !TODO update variables values

        // !TODO got then ot else or goto

        return SC_RESULT_OK;
    }



    return SC_RESULT_OK;
}

scp_result scp_operator_interpreter_agents_init()
{
    event_search_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_search_operators, 0);
    if (event_search_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_operator_interpreter_agents_shutdown()
{
    sc_event_destroy(event_search_operators_interpreter);
    return SCP_RESULT_TRUE;
}

