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
    scp_operand input_arc, node1, operator_node, operator_type;
    scp_result res;

    MAKE_DEFAULT_OPERAND_FIXED(input_arc);
    input_arc.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    if (SCP_RESULT_TRUE != ifVarAssign(&input_arc))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &input_arc, &operator_node))
    {
        print_error("scp-operator interpreting", "Can't find operator node");
        return SC_RESULT_ERROR;
    }
    operator_node.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    if (SCP_RESULT_TRUE != resolve_operator_type(&operator_node, &operator_type))
    {
        print_error("scp-operator interpreting", "Can't resolve operator type");
        return SC_RESULT_ERROR;
    }

    //searchElStr3 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_searchElStr3))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
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

        if (SCP_RESULT_TRUE != get_operands_values(&operator_node, operands, operand_values, 3))
        {
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = searchElStr3(operand_values, operand_values + 1, operand_values + 2);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
                set_operands_values(&operator_node, operands, operand_values, 3);
                if (SCP_RESULT_TRUE != goto_conditional(&operator_node, &rrel_then))
                {
                    return SC_RESULT_ERROR;
                }
                return SC_RESULT_OK;
            }
            case SCP_RESULT_FALSE:
            {
                if (SCP_RESULT_TRUE != goto_conditional(&operator_node, &rrel_else))
                {
                    return SC_RESULT_ERROR;
                }
                return SC_RESULT_OK;
            }
            case SCP_RESULT_ERROR:
            {
                if (SCP_RESULT_TRUE != goto_conditional(&operator_node, &rrel_error))
                {
                    return SC_RESULT_ERROR;
                }
                return SC_RESULT_OK;
            }
        }
        return SC_RESULT_ERROR;
    }

    //searchElStr5 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_searchElStr5))
    {
        scp_operand operands[5], operand_values[5];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
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
        if (SCP_RESULT_TRUE != resolve_operand_modifiers(&operator_node, operands + 3, &rrel_4))
        {
            return SC_RESULT_ERROR;
        }
        if (SCP_RESULT_TRUE != resolve_operand_modifiers(&operator_node, operands + 4, &rrel_5))
        {
            return SC_RESULT_ERROR;
        }

        if (SCP_RESULT_TRUE != get_operands_values(&operator_node, operands, operand_values, 5))
        {
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = searchElStr5(operand_values, operand_values + 1, operand_values + 2, operand_values + 3, operand_values + 4);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
                set_operands_values(&operator_node, operands, operand_values, 5);
                if (SCP_RESULT_TRUE != goto_conditional(&operator_node, &rrel_then))
                {
                    return SC_RESULT_ERROR;
                }
                return SC_RESULT_OK;
            }
            case SCP_RESULT_FALSE:
            {
                if (SCP_RESULT_TRUE != goto_conditional(&operator_node, &rrel_else))
                {
                    return SC_RESULT_ERROR;
                }
                return SC_RESULT_OK;
            }
            case SCP_RESULT_ERROR:
            {
                if (SCP_RESULT_TRUE != goto_conditional(&operator_node, &rrel_error))
                {
                    return SC_RESULT_ERROR;
                }
                return SC_RESULT_OK;
            }
        }
        return SC_RESULT_ERROR;
    }

    return SC_RESULT_ERROR;
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

