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
#include "malloc.h"

#include <stdio.h>

sc_event *event_interpreting_finished_succesfully;

sc_event *event_gen_operators_interpreter;
sc_event *event_search_operators_interpreter;
sc_event *event_erase_operators_interpreter;
sc_event *event_return_operator_interpreter;
sc_event *event_call_operator_interpreter;
sc_event *event_waitReturn_operator_interpreter;
sc_event *event_print_operators_interpreter;
sc_event *event_content_arithmetic_operators_interpreter;
sc_event *event_content_trig_operators_interpreter;
sc_event *event_if_operators_interpreter;
sc_event *event_other_operators_interpreter;
sc_event *event_system_operators_interpreter;

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

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
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

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 5))
        {
            operator_interpreting_crash(&operator_node);
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

sc_result interpreter_agent_gen_operators(sc_event *event, sc_addr arg)
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

    //genEl case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_genEl))
    {
        scp_operand operand, operand_value;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("genEl");

        resolve_operands_modifiers(&operator_node, &operand, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operand, &operand_value, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = genEl(&operand_value);
        if (res == SCP_RESULT_TRUE)
        {
            set_operands_values(&operand, &operand_value, 1);
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    //genElStr3 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_genElStr3))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("genElStr3");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = genElStr3(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            set_operands_values(operands, operand_values, 3);
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    //genElStr5 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_genElStr5))
    {
        scp_operand operands[5], operand_values[5];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("genElStr5");

        resolve_operands_modifiers(&operator_node, operands, 5);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 5))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = genElStr5(operand_values, operand_values + 1, operand_values + 2, operand_values + 3, operand_values + 4);
        if (res == SCP_RESULT_TRUE)
        {
            set_operands_values(operands, operand_values, 5);
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    return SC_RESULT_ERROR;
}

sc_result interpreter_agent_erase_operators(sc_event *event, sc_addr arg)
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

    //eraseEl case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_eraseEl))
    {
        scp_operand operand, operand_value;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("eraseEl");

        resolve_operands_modifiers(&operator_node, &operand, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operand, &operand_value, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = eraseEl(&operand_value);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    //eraseElStr3 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_eraseElStr3))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("eraseElStr3");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = eraseElStr3(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    //eraseElStr5 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_eraseElStr5))
    {
        scp_operand operands[5], operand_values[5];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("eraseElStr5");

        resolve_operands_modifiers(&operator_node, operands, 5);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 5))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = eraseElStr5(operand_values, operand_values + 1, operand_values + 2, operand_values + 3, operand_values + 4);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    //eraseSetStr3 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_eraseSetStr3))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("eraseSetStr3");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = eraseSetStr3(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    //eraseSetStr5 case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_eraseSetStr5))
    {
        scp_operand operands[5], operand_values[5];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("eraseSetStr5");

        resolve_operands_modifiers(&operator_node, operands, 5);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 5))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = eraseSetStr5(operand_values, operand_values + 1, operand_values + 2, operand_values + 3, operand_values + 4);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    return SC_RESULT_ERROR;
}

sc_result interpreter_agent_content_arithmetic_operators(sc_event *event, sc_addr arg)
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

    //contAdd case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contAdd))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contAdd");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contAdd(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contSub case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contSub))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contSub");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contSub(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contMult case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contMult))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contMult");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contMult(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contDiv case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contDiv))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contDiv");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contDiv(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contPow case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contPow))
    {
        scp_operand operands[3], operand_values[3];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contPow");

        resolve_operands_modifiers(&operator_node, operands, 3);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 3))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contPow(operand_values, operand_values + 1, operand_values + 2);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contLn case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contLn))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contLn");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contLn(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    return SC_RESULT_ERROR;
}

sc_result interpreter_agent_content_trig_operators(sc_event *event, sc_addr arg)
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

    //contSin case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contSin))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contSin");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contSin(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contCos case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contCos))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contCos");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contCos(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contTg case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contTg))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contTg");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contTg(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contASin case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contASin))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contASin");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contASin(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contACos case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contACos))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contACos");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contACos(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contATg case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contATg))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contATg");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contATg(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }

    return SC_RESULT_ERROR;
}

sc_result interpreter_agent_if_operators(sc_event *event, sc_addr arg)
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

    //ifVarAssign case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_ifVarAssign))
    {
        scp_operand operands, operand_values;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("ifVarAssign");

        resolve_operands_modifiers(&operator_node, &operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operands, &operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = ifVarAssign(&operand_values);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
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
        return SC_RESULT_OK;
    }
    //ifFormCont case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_ifFormCont))
    {
        scp_operand operands, operand_values;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("ifFormCont");

        resolve_operands_modifiers(&operator_node, &operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operands, &operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = ifFormCont(&operand_values);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
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
        return SC_RESULT_OK;
    }
    //ifType case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_ifType))
    {
        scp_operand operands, operand_values;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("ifType");

        resolve_operands_modifiers(&operator_node, &operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operands, &operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = ifType(&operand_values);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
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
        return SC_RESULT_OK;
    }
    //ifCoin case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_ifCoin))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("ifCoin");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = ifCoin(operand_values, operand_values + 1);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
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
    //ifEq case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_ifEq))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("ifEq");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = ifEq(operand_values, operand_values + 1);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
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
    //ifGr case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_ifGr))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("ifGr");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = ifGr(operand_values, operand_values + 1);
        switch (res)
        {
            case SCP_RESULT_TRUE:
            {
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

sc_result interpreter_agent_other_operators(sc_event *event, sc_addr arg)
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

    //varAssign case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_varAssign))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("varAssign");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = varAssign(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contAssign case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contAssign))
    {
        scp_operand operands[2], operand_values[2];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contAssign");

        resolve_operands_modifiers(&operator_node, operands, 2);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 2))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contAssign(operand_values, operand_values + 1);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
    }
    //contErase case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_contErase))
    {
        scp_operand operands, operand_values;
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("contErase");

        resolve_operands_modifiers(&operator_node, &operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(&operands, &operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        res = contErase(&operand_values);
        if (res == SCP_RESULT_TRUE)
        {
            goto_unconditional(&operator_node);
        }
        return SC_RESULT_OK;
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

        genElStr3(&question_scp_interpretation_request, &arc1, &quest);
        genElStr3(&question_initiated, &arc1, &quest);

        goto_unconditional(&operator_node);
    }

    return SC_RESULT_OK;
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
        return SC_RESULT_OK;
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

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        print(operand_values);
        goto_unconditional(&operator_node);

        return SC_RESULT_OK;
    }
    //printNl case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_printNl))
    {
        scp_operand operands[1], operand_values[1];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("printNl");

        resolve_operands_modifiers(&operator_node, operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        printNl(operand_values);
        goto_unconditional(&operator_node);

        return SC_RESULT_OK;
    }
    //printEl case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_printEl))
    {
        scp_operand operands[1], operand_values[1];
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("printEl");

        resolve_operands_modifiers(&operator_node, operands, 1);

        if (SCP_RESULT_TRUE != get_operands_values(operands, operand_values, 1))
        {
            operator_interpreting_crash(&operator_node);
            return SC_RESULT_ERROR;
        }

        //Operator body
        printEl(operand_values);
        goto_unconditional(&operator_node);

        return SC_RESULT_OK;
    }

    return SC_RESULT_ERROR;
}

sc_result sys_search_agent_body(scp_operand *operator_node)
{
    scp_operand param1, param2, param2_node, param4, param4_node, operand, modifier, arc1, arc2, operand_elem;
    scp_operand **pair_elems2 = nullptr, **pair_values2 = nullptr, **pair_elems3 = nullptr, **pair_values3 = nullptr;
    scp_operand_pair *params = nullptr, *results = nullptr;
    scp_iterator3 *it0, *it, *it1;
    scp_uint32 rrel_number = 0, size2 = 0, size3 = 0, i = 0;
    scp_bool is4 = SCP_FALSE, isresult = SCP_FALSE;
    scp_result res;
    sc_result fun_result = SC_RESULT_OK;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(operand);
    MAKE_DEFAULT_NODE_ASSIGN(modifier);

    it0 = scp_iterator3_new(operator_node, &arc1, &operand);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it0, operator_node, &arc1, &operand))
    {
        arc1.param_type = SCP_FIXED;
        rrel_number = 0;
        it = scp_iterator3_new(&modifier, &arc2, &arc1);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &modifier, &arc2, &arc1))
        {
            if (rrel_number == 0)
            {
                rrel_number = check_ordinal_rrel(&modifier, 4);
                if (rrel_number > 0)
                {
                    continue;
                }
            }

            // Operand type
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_scp_const))
            {
                operand.operand_type = SCP_CONST;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_scp_var))
            {
                operand.operand_type = SCP_VAR;
                continue;
            }

            // Param type
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_assign))
            {
                operand.param_type = SCP_ASSIGN;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_fixed))
            {
                operand.param_type = SCP_FIXED;
                continue;
            }
        }
        scp_iterator3_free(it);

        if (rrel_number == 1)
        {
            if (SCP_RESULT_TRUE != get_operand_value(&operand, &param1))
            {
                operator_interpreting_crash(operator_node);
                fun_result = SC_RESULT_ERROR;
                goto exit;
            }
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }
        if (rrel_number == 2)
        {
            if (operand.param_type == SCP_ASSIGN)
            {
                param2_node = operand;
                if (SCP_RESULT_TRUE != get_operand_value(&param2_node, &param2))
                {
                    operator_interpreting_crash(operator_node);
                    fun_result = SC_RESULT_ERROR;
                    goto exit;
                }
                arc1.param_type = SCP_ASSIGN;
                MAKE_DEFAULT_OPERAND_ASSIGN(operand);
                continue;
            }
            isresult = SCP_TRUE;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand_elem);
            get_set_power(&operand, &size2);
            if (size2 == 0)
                continue;
            results = (scp_operand_pair *)calloc(sizeof(scp_operand_pair), size2);
            pair_elems2 = (scp_operand **)calloc(sizeof(scp_operand), size2);
            pair_values2 = (scp_operand **)calloc(sizeof(scp_operand), size2);
            for (i = 0; i < size2; i++)
            {
                pair_elems2[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
                pair_values2[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
            }
            i = 0;
            it1 = scp_iterator3_new(&operand, &arc2, &operand_elem);
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &operand, &arc2, &operand_elem))
            {
                operand_elem.param_type = SCP_FIXED;
                resolve_operands_modifiers(&operand_elem, pair_elems2[i], 2);
                if (SCP_RESULT_TRUE != get_operands_values(pair_elems2[i], pair_values2[i], 2))
                {
                    operator_interpreting_crash(operator_node);
                    fun_result = SC_RESULT_ERROR;
                    goto exit;
                }
                results[i].operand1 = pair_values2[i];
                results[i].operand2 = pair_values2[i] + 1;
                operand_elem.param_type = SCP_ASSIGN;
                i++;
            }
            scp_iterator3_free(it1);
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }
        if (rrel_number == 3)
        {
            MAKE_DEFAULT_OPERAND_ASSIGN(operand_elem);
            get_set_power(&operand, &size3);
            if (size3 == 0)
                continue;
            params = (scp_operand_pair *)calloc(sizeof(scp_operand_pair), size3);
            pair_elems3 = (scp_operand **)calloc(sizeof(scp_operand), size3);
            pair_values3 = (scp_operand **)calloc(sizeof(scp_operand), size3);
            for (i = 0; i < size3; i++)
            {
                pair_elems3[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
                pair_values3[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
            }
            i = 0;
            it1 = scp_iterator3_new(&operand, &arc2, &operand_elem);
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &operand, &arc2, &operand_elem))
            {
                operand_elem.param_type = SCP_FIXED;
                resolve_operands_modifiers(&operand_elem, pair_elems3[i], 2);
                if (SCP_RESULT_TRUE != get_operands_values(pair_elems3[i], pair_values3[i], 2))
                {
                    operator_interpreting_crash(operator_node);
                    fun_result = SC_RESULT_ERROR;
                    goto exit;
                }
                params[i].operand1 = pair_values3[i];
                params[i].operand2 = pair_values3[i] + 1;
                operand_elem.param_type = SCP_ASSIGN;
                i++;
            }
            scp_iterator3_free(it1);
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }
        if (rrel_number == 4)
        {
            is4 = SCP_TRUE;
            param4_node = operand;
            if (SCP_RESULT_TRUE != get_operand_value(&operand, &param4))
            {
                operator_interpreting_crash(operator_node);
                fun_result = SC_RESULT_ERROR;
                goto exit;
            }
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }

        arc1.param_type = SCP_ASSIGN;
        MAKE_DEFAULT_OPERAND_ASSIGN(operand);
    }
    scp_iterator3_free(it0);
    if (isresult == SCP_TRUE)
    {
        if (is4 == SCP_TRUE)
        {
            res = scp_sys_search_for_variables(&param1, results, size2, params, size3, &param4);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    for (i = 0; i < size2; i++)
                    {
                        set_operands_values(pair_elems2[i], pair_values2[i], 2);
                    }
                    set_operands_values(&param4_node, &param4, 1);
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
        else
        {
            res = scp_sys_search_for_variables(&param1, results, size2, params, size3, nullptr);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    for (i = 0; i < size2; i++)
                    {
                        set_operands_values(pair_elems2[i], pair_values2[i], 2);
                    }
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
    }
    else
    {
        if (is4 == SCP_TRUE)
        {
            res = scp_sys_search(&param1, &param2, params, size3, &param4, SCP_TRUE);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    set_operands_values(&param2_node, &param2, 1);
                    set_operands_values(&param4_node, &param4, 1);
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
        else
        {
            res = scp_sys_search(&param1, &param2, params, size3, nullptr, SCP_TRUE);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    set_operands_values(&param2_node, &param2, 1);
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
    }
exit:
    //Memory deallocating
    for (i = 0; i < size2; i++)
    {
        free(pair_elems2[i]);
        free(pair_values2[i]);
    }
    for (i = 0; i < size3; i++)
    {
        free(pair_elems3[i]);
        free(pair_values3[i]);
    }
    free(pair_elems2);
    free(pair_values2);
    free(pair_elems3);
    free(pair_values3);
    free(results);
    free(params);
    return fun_result;
}

sc_result sys_gen_agent_body(scp_operand *operator_node)
{
    scp_operand param1, param2, param2_node, param4, param4_node, operand, modifier, arc1, arc2, operand_elem;
    scp_operand **pair_elems2 = nullptr, **pair_values2 = nullptr, **pair_elems3 = nullptr, **pair_values3 = nullptr;
    scp_operand_pair *params = nullptr, *results = nullptr;
    scp_iterator3 *it0, *it, *it1;
    scp_uint32 rrel_number = 0, size2 = 0, size3 = 0, i = 0;
    scp_bool is4 = SCP_FALSE, isresult = SCP_FALSE;
    scp_result res;
    sc_result fun_result = SC_RESULT_OK;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(operand);
    MAKE_DEFAULT_NODE_ASSIGN(modifier);

    it0 = scp_iterator3_new(operator_node, &arc1, &operand);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it0, operator_node, &arc1, &operand))
    {
        arc1.param_type = SCP_FIXED;
        rrel_number = 0;
        it = scp_iterator3_new(&modifier, &arc2, &arc1);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &modifier, &arc2, &arc1))
        {
            if (rrel_number == 0)
            {
                rrel_number = check_ordinal_rrel(&modifier, 4);
                if (rrel_number > 0)
                {
                    continue;
                }
            }

            // Operand type
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_scp_const))
            {
                operand.operand_type = SCP_CONST;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_scp_var))
            {
                operand.operand_type = SCP_VAR;
                continue;
            }

            // Param type
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_assign))
            {
                operand.param_type = SCP_ASSIGN;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_fixed))
            {
                operand.param_type = SCP_FIXED;
                continue;
            }
        }
        scp_iterator3_free(it);

        if (rrel_number == 1)
        {
            if (SCP_RESULT_TRUE != get_operand_value(&operand, &param1))
            {
                operator_interpreting_crash(operator_node);
                fun_result = SC_RESULT_ERROR;
                goto exit;
            }
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }
        if (rrel_number == 2)
        {
            if (operand.param_type == SCP_ASSIGN)
            {
                param2_node = operand;
                if (SCP_RESULT_TRUE != get_operand_value(&param2_node, &param2))
                {
                    operator_interpreting_crash(operator_node);
                    fun_result = SC_RESULT_ERROR;
                    goto exit;
                }
                arc1.param_type = SCP_ASSIGN;
                MAKE_DEFAULT_OPERAND_ASSIGN(operand);
                continue;
            }
            isresult = SCP_TRUE;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand_elem);
            get_set_power(&operand, &size2);
            if (size2 == 0)
                continue;
            results = (scp_operand_pair *)calloc(sizeof(scp_operand_pair), size2);
            pair_elems2 = (scp_operand **)calloc(sizeof(scp_operand), size2);
            pair_values2 = (scp_operand **)calloc(sizeof(scp_operand), size2);
            for (i = 0; i < size2; i++)
            {
                pair_elems2[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
                pair_values2[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
            }
            i = 0;
            it1 = scp_iterator3_new(&operand, &arc2, &operand_elem);
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &operand, &arc2, &operand_elem))
            {
                operand_elem.param_type = SCP_FIXED;
                resolve_operands_modifiers(&operand_elem, pair_elems2[i], 2);
                if (SCP_RESULT_TRUE != get_operands_values(pair_elems2[i], pair_values2[i], 2))
                {
                    operator_interpreting_crash(operator_node);
                    fun_result = SC_RESULT_ERROR;
                    goto exit;
                }
                results[i].operand1 = pair_values2[i];
                results[i].operand2 = pair_values2[i] + 1;
                operand_elem.param_type = SCP_ASSIGN;
                i++;
            }
            scp_iterator3_free(it1);
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }
        if (rrel_number == 3)
        {
            MAKE_DEFAULT_OPERAND_ASSIGN(operand_elem);
            get_set_power(&operand, &size3);
            if (size3 == 0)
                continue;
            params = (scp_operand_pair *)calloc(sizeof(scp_operand_pair), size3);
            pair_elems3 = (scp_operand **)calloc(sizeof(scp_operand), size3);
            pair_values3 = (scp_operand **)calloc(sizeof(scp_operand), size3);
            for (i = 0; i < size3; i++)
            {
                pair_elems3[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
                pair_values3[i] = (scp_operand *)calloc(sizeof(scp_operand), 2);
            }
            i = 0;
            it1 = scp_iterator3_new(&operand, &arc2, &operand_elem);
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &operand, &arc2, &operand_elem))
            {
                operand_elem.param_type = SCP_FIXED;
                resolve_operands_modifiers(&operand_elem, pair_elems3[i], 2);
                if (SCP_RESULT_TRUE != get_operands_values(pair_elems3[i], pair_values3[i], 2))
                {
                    operator_interpreting_crash(operator_node);
                    fun_result = SC_RESULT_ERROR;
                    goto exit;
                }
                params[i].operand1 = pair_values3[i];
                params[i].operand2 = pair_values3[i] + 1;
                operand_elem.param_type = SCP_ASSIGN;
                i++;
            }
            scp_iterator3_free(it1);
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }
        if (rrel_number == 4)
        {
            is4 = SCP_TRUE;
            param4_node = operand;
            if (SCP_RESULT_TRUE != get_operand_value(&operand, &param4))
            {
                operator_interpreting_crash(operator_node);
                fun_result = SC_RESULT_ERROR;
                goto exit;
            }
            arc1.param_type = SCP_ASSIGN;
            MAKE_DEFAULT_OPERAND_ASSIGN(operand);
            continue;
        }

        arc1.param_type = SCP_ASSIGN;
        MAKE_DEFAULT_OPERAND_ASSIGN(operand);
    }
    scp_iterator3_free(it0);
    if (isresult == SCP_TRUE)
    {
        if (is4 == SCP_TRUE)
        {
            res = scp_sys_gen_for_variables(&param1, results, size2, params, size3, &param4);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    for (i = 0; i < size2; i++)
                    {
                        set_operands_values(pair_elems2[i], pair_values2[i], 2);
                    }
                    set_operands_values(&param4_node, &param4, 1);
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
        else
        {
            res = scp_sys_gen_for_variables(&param1, results, size2, params, size3, nullptr);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    for (i = 0; i < size2; i++)
                    {
                        set_operands_values(pair_elems2[i], pair_values2[i], 2);
                    }
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
    }
    else
    {
        if (is4 == SCP_TRUE)
        {
            res = scp_sys_gen(&param1, &param2, params, size3, &param4);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    set_operands_values(&param2_node, &param2, 1);
                    set_operands_values(&param4_node, &param4, 1);
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
        else
        {
            res = scp_sys_gen(&param1, &param2, params, size3, nullptr);
            switch (res)
            {
                case SCP_RESULT_TRUE:
                {
                    set_operands_values(&param2_node, &param2, 1);
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_then))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_FALSE:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_else))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
                case SCP_RESULT_ERROR:
                {
                    if (SCP_RESULT_TRUE != goto_conditional(operator_node, &rrel_error))
                    {
                        fun_result = SC_RESULT_ERROR;
                        goto exit;
                    }
                    fun_result = SC_RESULT_OK;
                    goto exit;
                }
            }
        }
    }
exit:
    //Memory deallocating
    for (i = 0; i < size2; i++)
    {
        free(pair_elems2[i]);
        free(pair_values2[i]);
    }
    for (i = 0; i < size3; i++)
    {
        free(pair_elems3[i]);
        free(pair_values3[i]);
    }
    free(pair_elems2);
    free(pair_values2);
    free(pair_elems3);
    free(pair_values3);
    free(results);
    free(params);
    return fun_result;
}

sc_result interpreter_agent_system_operators(sc_event *event, sc_addr arg)
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

    //sys_search case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_search))
    {
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("sys_search");
        return sys_search_agent_body(&operator_node);
    }
    //sys_gen case
    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_gen))
    {
        input_arc.erase = SCP_TRUE;
        eraseEl(&input_arc);
        print_debug_info("sys_gen");
        return sys_gen_agent_body(&operator_node);
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

    event_gen_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_gen_operators, 0);
    if (event_gen_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_erase_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_erase_operators, 0);
    if (event_erase_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_content_arithmetic_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_content_arithmetic_operators, 0);
    if (event_content_arithmetic_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_content_trig_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_content_trig_operators, 0);
    if (event_content_trig_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_if_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_if_operators, 0);
    if (event_if_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_other_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_other_operators, 0);
    if (event_other_operators_interpreter == nullptr)
        return SCP_RESULT_ERROR;
    event_system_operators_interpreter = sc_event_new(active_scp_operator.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, interpreter_agent_system_operators, 0);
    if (event_system_operators_interpreter == nullptr)
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
    sc_event_destroy(event_gen_operators_interpreter);
    sc_event_destroy(event_erase_operators_interpreter);
    sc_event_destroy(event_return_operator_interpreter);
    sc_event_destroy(event_print_operators_interpreter);
    sc_event_destroy(event_content_arithmetic_operators_interpreter);
    sc_event_destroy(event_content_trig_operators_interpreter);
    sc_event_destroy(event_if_operators_interpreter);
    sc_event_destroy(event_other_operators_interpreter);
    sc_event_destroy(event_system_operators_interpreter);
    sc_event_destroy(event_call_operator_interpreter);
    sc_event_destroy(event_waitReturn_operator_interpreter);
    return SCP_RESULT_TRUE;
}
