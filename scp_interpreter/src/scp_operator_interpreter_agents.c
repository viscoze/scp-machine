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

sc_event *event_interpreting_finished_succesfully;

sc_event *event_search_operators_interpreter;
sc_event *event_return_operator_interpreter;
sc_event *event_print_operators_interpreter;

scp_bool debug_mode = SCP_FALSE;

void print_debug_info(const char *info)
{
    if (debug_mode == SCP_TRUE)
    {
        printf(">>%s\n", info);
    }
}

sc_result interpreter_agent_search_operators(sc_event *event, sc_addr arg)
{
    scp_operand input_arc, node1, operator_node, operator_type;
    scp_result res;

    MAKE_DEFAULT_OPERAND_FIXED(input_arc);
    input_arc.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(operator_node);
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
        operator_interpreting_crash(&operator_node);
        return SC_RESULT_ERROR;
    }

    //searchElStr3 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_searchElStr3))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("searchElStr3");

        resolve_operands_modifiers(&operator_node, operands, 3);

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
                set_operands_values(operands, operand_values, 3);
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
        print_debug_info("searchElStr5");

        resolve_operands_modifiers(&operator_node, operands, 5);

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
                set_operands_values(operands, operand_values, 5);
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

sc_result interpreter_agent_return_operator(sc_event *event, sc_addr arg)
{
    scp_operand input_arc, node1, operator_node, operator_type;

    MAKE_DEFAULT_OPERAND_FIXED(input_arc);
    input_arc.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(operator_node);
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
        operator_interpreting_crash(&operator_node);
        return SC_RESULT_ERROR;
    }

    //return case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_return))
    {
        scp_operand scp_process_node, arc1, arc2, quest;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("return");
        MAKE_COMMON_ARC_ASSIGN(arc1);
        MAKE_DEFAULT_ARC_ASSIGN(arc2);
        MAKE_DEFAULT_NODE_ASSIGN(quest);
        find_scp_process_for_scp_operator(&operator_node, &scp_process_node);
        searchElStr5(&quest, &arc1, &scp_process_node, &arc2, &nrel_scp_process);
        quest.param_type = SCP_FIXED;
        finish_question_successfully(&quest);
        scp_process_node.param_type = SCP_FIXED;
        mark_scp_process_as_useless(&scp_process_node);
    }

    return SC_RESULT_ERROR;
}

sc_result interpreter_agent_print_operators(sc_event *event, sc_addr arg)
{
    scp_operand input_arc, node1, operator_node, operator_type;

    MAKE_DEFAULT_OPERAND_FIXED(input_arc);
    input_arc.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(operator_node);
    if (SCP_RESULT_TRUE != ifVarAssign(&input_arc))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &input_arc, &operator_node))
    {
        print_error("scp-operator interpreting", "Can't find operator node");
        operator_interpreting_crash(&operator_node);
        return SC_RESULT_ERROR;
    }
    operator_node.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    if (SCP_RESULT_TRUE != resolve_operator_type(&operator_node, &operator_type))
    {
        print_error("scp-operator interpreting", "Can't resolve operator type");
        return SC_RESULT_ERROR;
    }

    //print case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_print))
    {
        scp_operand operands[1], operand_values[1];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("print");

        resolve_operands_modifiers(&operator_node, operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operator_node, operands, operand_values, 1))
        {
            return SC_RESULT_ERROR;
        }

        //Operator body
        print(operand_values);
        goto_unconditional(&operator_node);

        return SC_RESULT_ERROR;
    }
    //printNl case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_printNl))
    {
        scp_operand operands[1], operand_values[1];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("printNl");

        resolve_operands_modifiers(&operator_node, operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operator_node, operands, operand_values, 1))
        {
            return SC_RESULT_ERROR;
        }

        //Operator body
        printNl(operand_values);
        goto_unconditional(&operator_node);

        return SC_RESULT_ERROR;
    }
    //printEl case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_printEl))
    {
        scp_operand operands[1], operand_values[1];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("printEl");

        resolve_operands_modifiers(&operator_node, operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operator_node, operands, operand_values, 1))
        {
            return SC_RESULT_ERROR;
        }

        //Operator body
        printEl(operand_values);
        goto_unconditional(&operator_node);

        return SC_RESULT_ERROR;
    }

    return SC_RESULT_ERROR;
}

sc_result interpreting_question_finished_successfully(sc_event *event, sc_addr arg)
{
    scp_operand input_arc, node1, quest;

    MAKE_DEFAULT_OPERAND_FIXED(input_arc);
    input_arc.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(quest);
    if (SCP_RESULT_TRUE != ifVarAssign(&input_arc))
    {
        return SC_RESULT_ERROR;
    }
    searchElStr3(&node1, &input_arc, &quest);
    quest.param_type = SCP_FIXED;
    MAKE_DEFAULT_ARC_ASSIGN(input_arc);
    if (SCP_RESULT_TRUE == searchElStr3(&question_scp_interpretation_request, &input_arc, &quest))
    {
        //printf("INTERPRETATION FINISHED SUCCESSFULLY\n");
    }
    return SC_RESULT_OK;
}

scp_result scp_operator_interpreter_agents_init()
{
    event_interpreting_finished_succesfully = sc_event_new(question_finished_successfully.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreting_question_finished_successfully, 0);
    if (event_interpreting_finished_succesfully == nullptr)
        return SCP_RESULT_ERROR;

    event_search_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_search_operators, 0);
    if (event_search_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_print_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_print_operators, 0);
    if (event_print_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_return_operator_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_return_operator, 0);
    if (event_return_operator_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_operator_interpreter_agents_shutdown()
{
    sc_event_destroy(event_interpreting_finished_succesfully);

    sc_event_destroy(event_search_operators_interpreter);
    sc_event_destroy(event_return_operator_interpreter);
    sc_event_destroy(event_print_operators_interpreter);
    return SCP_RESULT_TRUE;
}

