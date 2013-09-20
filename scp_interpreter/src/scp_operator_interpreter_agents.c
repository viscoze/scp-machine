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
sc_event *event_call_operator_interpreter;
sc_event *event_waitReturn_operator_interpreter;
sc_event *event_print_operators_interpreter;

scp_bool debug_mode = SCP_TRUE;

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
        printEl(&operator_node);
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
        printEl(&operator_node);
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

sc_result interpreter_agent_call_operator(sc_event *event, sc_addr arg)
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
        printEl(&operator_node);
        print_error("scp-operator interpreting", "Can't resolve operator type");
        operator_interpreting_crash(&operator_node);
        return SC_RESULT_ERROR;
    }

    //return case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_call))
    {
        scp_operand arc1, arc2, arc3, quest, prog_node, params_node, modifier, new_params_node,
                    prog_params_node, descr_node, param, curr_ordinal, value;
        scp_iterator3 *it, *it1;
        scp_operand_type operand_type = SCP_CONST;
        sc_char in_out_params[ORDINAL_RRELS_COUNT + 1];
        sc_char in_out_value = 0;
        scp_uint32 ordinal_index = 0;

        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("call");

        MAKE_DEFAULT_ARC_ASSIGN(arc1);
        MAKE_DEFAULT_ARC_ASSIGN(arc2);
        MAKE_COMMON_ARC_ASSIGN(arc3);
        MAKE_DEFAULT_OPERAND_ASSIGN(prog_node);
        MAKE_DEFAULT_OPERAND_ASSIGN(prog_params_node);
        MAKE_DEFAULT_OPERAND_ASSIGN(params_node);
        MAKE_DEFAULT_OPERAND_ASSIGN(param);
        MAKE_DEFAULT_OPERAND_ASSIGN(value);
        MAKE_DEFAULT_OPERAND_ASSIGN(descr_node);
        MAKE_DEFAULT_OPERAND_ASSIGN(curr_ordinal);
        MAKE_DEFAULT_OPERAND_ASSIGN(modifier);

        searchElStr5(&operator_node, &arc1, &prog_node, &arc2, &ordinal_rrels[1]);
        prog_node.param_type = SCP_FIXED;
        searchElStr5(&prog_node, &arc1, &prog_params_node, &arc2, &rrel_params);
        prog_params_node.param_type = SCP_FIXED;
        searchElStr5(&operator_node, &arc1, &params_node, &arc2, &ordinal_rrels[2]);
        params_node.param_type = SCP_FIXED;
        erase_var_set_values(&params_node);
        searchElStr5(&operator_node, &arc1, &descr_node, &arc2, &ordinal_rrels[3]);
        descr_node.param_type = SCP_FIXED;

        it = scp_iterator3_new(&prog_params_node, &arc1, &param);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &prog_params_node, &arc1, &param))
        {
            arc1.param_type = SCP_FIXED;
            in_out_value = 0;
            ordinal_index = 0;
            it1 = scp_iterator3_new(&modifier, &arc2, &arc1);
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &modifier, &arc2, &arc1))
            {
                if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_in))
                {
                    in_out_value++;
                    continue;
                }
                if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_out))
                {
                    in_out_value += 2;
                    continue;
                }

                // Ordinal
                if (ordinal_index == 0)
                {
                    modifier.param_type = SCP_FIXED;
                    ordinal_index = check_ordinal_rrel(&modifier, ORDINAL_RRELS_COUNT);
                    modifier.param_type = SCP_ASSIGN;
                }
            }
            scp_iterator3_free(it1);
            in_out_params[ordinal_index] = in_out_value;
            arc1.param_type = SCP_ASSIGN;
        }
        scp_iterator3_free(it);

        MAKE_DEFAULT_NODE_ASSIGN(quest);
        MAKE_DEFAULT_NODE_ASSIGN(new_params_node);
        arc1.erase = SCP_TRUE;
        eraseSetStr5(&descr_node, &arc3, &quest, &arc2, &nrel_value);
        genElStr5(&quest, &arc1, &prog_node, &arc2, &ordinal_rrels[1]);
        quest.param_type = SCP_FIXED;
        genElStr5(&descr_node, &arc3, &quest, &arc2, &nrel_value);
        genElStr5(&quest, &arc1, &new_params_node, &arc2, &ordinal_rrels[2]);
        new_params_node.param_type = SCP_FIXED;

        param.param_type = SCP_ASSIGN;
        it = scp_iterator3_new(&params_node, &arc1, &param);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &params_node, &arc1, &param))
        {
            param.param_type = SCP_FIXED;
            arc1.param_type = SCP_FIXED;
            operand_type = SCP_CONST;
            ordinal_rrel.param_type = SCP_ASSIGN;
            it1 = scp_iterator3_new(&modifier, &arc2, &arc1);
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &modifier, &arc2, &arc1))
            {
                // Param type
                if (SCP_RESULT_TRUE == ifCoin(&rrel_scp_const, &modifier))
                {
                    operand_type = SCP_CONST;
                    continue;
                }
                if (SCP_RESULT_TRUE == ifCoin(&rrel_scp_var, &modifier))
                {
                    operand_type = SCP_VAR;
                    continue;
                }

                // Ordinal
                modifier.param_type = SCP_FIXED;
                if (SCP_RESULT_TRUE == searchElStr3(&ordinal_rrel, &arc2, &modifier))
                {
                    curr_ordinal.param_type = SCP_ASSIGN;
                    varAssign(&curr_ordinal, &modifier);
                    curr_ordinal.param_type = SCP_FIXED;
                }
                modifier.param_type = SCP_ASSIGN;
            }
            scp_iterator3_free(it1);
            arc1.param_type = SCP_ASSIGN;

            ordinal_index = check_ordinal_rrel(&curr_ordinal, ORDINAL_RRELS_COUNT + 1);
            if (in_out_params[ordinal_index] == 1)
            {
                if (operand_type == SCP_CONST)
                {
                    genElStr5(&new_params_node, &arc1, &param, &arc2, &curr_ordinal);
                }
                else
                {
                    value.param_type = SCP_ASSIGN;
                    searchElStr5(&param, &arc3, &value, &arc2, &nrel_value);
                    value.param_type = SCP_FIXED;
                    genElStr5(&new_params_node, &arc1, &value, &arc2, &curr_ordinal);
                }
            }
            else
            {
                genElStr5(&new_params_node, &arc1, &param, &arc2, &curr_ordinal);
            }

            param.param_type = SCP_ASSIGN;
        }
        scp_iterator3_free(it);

        printf("CALL PARAMS\n");
        printEl(&new_params_node);

        genElStr3(&question_scp_interpretation_request, &arc1, &quest);
        genElStr3(&question_initiated, &arc1, &quest);

        goto_unconditional(&operator_node);
    }

    return SC_RESULT_ERROR;
}

sc_result interpreter_agent_waitReturn_operator(sc_event *event, sc_addr arg)
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
        printEl(&operator_node);
        print_error("scp-operator interpreting", "Can't resolve operator type");
        operator_interpreting_crash(&operator_node);
        return SC_RESULT_ERROR;
    }

    //return case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_waitReturn))
    {
        scp_operand arc1, arc2, arc3, quest, descr_node, params;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("waitReturn");

        MAKE_DEFAULT_ARC_ASSIGN(arc1);
        MAKE_DEFAULT_ARC_ASSIGN(arc2);
        MAKE_COMMON_ARC_ASSIGN(arc3);
        MAKE_DEFAULT_OPERAND_ASSIGN(descr_node);
        MAKE_DEFAULT_OPERAND_ASSIGN(quest);

        searchElStr5(&operator_node, &arc1, &descr_node, &arc2, &ordinal_rrels[1]);
        if (SCP_RESULT_TRUE != searchElStr5(&descr_node, &arc3, &quest, &arc2, &nrel_value))
        {
            return SC_RESULT_ERROR;
        }
        if (SCP_RESULT_TRUE == searchElStr3(&question_finished_successfully, &arc1, &quest))
        {
            quest.erase = SCP_TRUE;
            quest.param_type = SCP_FIXED;
            MAKE_DEFAULT_OPERAND_ASSIGN(params);
            params.erase = SCP_TRUE;
            eraseElStr5(&quest, &arc1, &params, &arc2, &ordinal_rrels[2]);
            goto_unconditional(&operator_node);
        }
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
        printEl(&operator_node);
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
    if (SCP_RESULT_TRUE != ifVarAssign(&quest))
    {
        return SC_RESULT_OK;
    }
    if (SCP_RESULT_TRUE == searchElStr3(&question_scp_interpretation_request, &input_arc, &quest))
    {
        scp_operand arc1, arc2, arc3, descr_node, operator_node, params;
        MAKE_DEFAULT_ARC_ASSIGN(arc1);
        MAKE_DEFAULT_ARC_ASSIGN(arc2);
        MAKE_COMMON_ARC_ASSIGN(arc3);
        MAKE_DEFAULT_OPERAND_ASSIGN(descr_node);
        if (SCP_RESULT_TRUE == searchElStr5(&descr_node, &arc3, &quest, &arc2, &nrel_value))
        {
            descr_node.param_type = SCP_FIXED;
            MAKE_DEFAULT_OPERAND_ASSIGN(operator_node);
            if (SCP_RESULT_TRUE == searchElStr5(&operator_node, &arc1, &descr_node, &arc2, &ordinal_rrels[1]))
            {
                operator_node.param_type = SCP_FIXED;
                if (SCP_RESULT_TRUE == searchElStr3(&active_scp_operator, &arc1, &operator_node))
                {
                    quest.erase = SCP_TRUE;
                    MAKE_DEFAULT_OPERAND_ASSIGN(params);
                    params.erase = SCP_TRUE;
                    eraseElStr5(&quest, &arc1, &params, &arc2, &ordinal_rrels[2]);
                    goto_unconditional(&operator_node);
                }
            }
        }
        printf("INTERPRETATION FINISHED SUCCESSFULLY\n");
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
    event_call_operator_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_call_operator, 0);
    if (event_call_operator_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_waitReturn_operator_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_waitReturn_operator, 0);
    if (event_waitReturn_operator_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_operator_interpreter_agents_shutdown()
{
    sc_event_destroy(event_interpreting_finished_succesfully);

    sc_event_destroy(event_search_operators_interpreter);
    sc_event_destroy(event_return_operator_interpreter);
    sc_event_destroy(event_print_operators_interpreter);
    sc_event_destroy(event_call_operator_interpreter);
    sc_event_destroy(event_waitReturn_operator_interpreter);
    return SCP_RESULT_TRUE;
}
