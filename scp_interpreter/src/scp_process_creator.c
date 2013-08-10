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
#include "scp_process_creator.h"
#include "scp_interpreter_utils.h"
#include "scp_operators_copiers.h"
#include "scp_keynodes.h"

#include <stdio.h>

sc_event *event_program_iterpretation;
sc_event *event_ordinary_operator_copying;
sc_event *event_call_operator_copying;
sc_event *event_return_operator_copying;
sc_event *event_sys_operator_copying;
sc_event *event_operator_copying_finished_successfully;
sc_event *event_operator_copying_finished_unsuccessfully;
sc_event *event_operators_set_copying_completed;

scp_result copy_consts_set(scp_operand *source, scp_operand *dest, scp_operand *copies)
{
    scp_operand arc1, node, arc2;
    scp_iterator3 *it;
    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(node);
    it = scp_iterator3_new(source, &arc2, &node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, source, &arc2, &node))
    {
        node.param_type = SCP_FIXED;
        genElStr3(dest, &arc2, &node);
        genElStr5(&node, &arc1, &node, &arc2, copies);
        node.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result copy_vars_set(scp_operand *source, scp_operand *dest, scp_operand *copies)
{
    scp_operand arc1, node1, node2, arc2;
    scp_iterator3 *it;
    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(node1);
    MAKE_DEFAULT_OPERAND_ASSIGN(node2);

    it = scp_iterator3_new(source, &arc2, &node1);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, source, &arc2, &node1))
    {
        node1.param_type = SCP_FIXED;
        node2.param_type = SCP_ASSIGN;
        node2.element_type = node1.element_type;
        if (SCP_RESULT_TRUE == searchElStr5(&node1, &arc1, &node2, &arc2, copies))
        {
            node1.param_type = SCP_ASSIGN;
            continue;
        }
        genElStr3(dest, &arc2, &node2);
        node2.param_type = SCP_FIXED;
        genElStr5(&node1, &arc1, &node2, &arc2, copies);
        node1.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result copy_operator_set(scp_operand *source, scp_operand *dest, scp_operand *copies)
{
    scp_operand arc1, node1, node2, arc2, type;
    scp_iterator3 *it;
    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(node2);
    MAKE_DEFAULT_NODE_ASSIGN(type);

    //!TODO Check operators count and return existence

    it = scp_iterator3_new(source, &arc2, &node1);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, source, &arc2, &node1))
    {
        node1.param_type = SCP_FIXED;
        node2.param_type = SCP_ASSIGN;
        genElStr3(dest, &arc2, &node2);
        node2.param_type = SCP_FIXED;
        genElStr5(&node1, &arc1, &node2, &arc2, copies);
        type.param_type = SCP_ASSIGN;
        if (SCP_RESULT_TRUE != resolve_operator_type(&node1, &type))
        {
            printEl(&node1);
            scp_iterator3_free(it);
            return print_error("Illegal operator", "Can't resolve operator type");
        }
        type.param_type = SCP_FIXED;
        genElStr3(&type, &arc2, &node2);
        node1.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result copy_parameters_set(scp_operand *call_parameters, scp_operand *scp_procedure_vars, scp_operand *scp_procedure_params, scp_operand *scp_process_vars, scp_operand *scp_process_consts, scp_operand *scp_process_copies, scp_operand *scp_process_values)
{
    scp_operand arc1, arc2, arc3, elem1, source_var, dest_var, dest_value;
    scp_result is_out;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem1);
    MAKE_COMMON_ARC_ASSIGN(arc3);
    MAKE_DEFAULT_OPERAND_ASSIGN(source_var);
    MAKE_DEFAULT_OPERAND_ASSIGN(dest_var);
    MAKE_DEFAULT_OPERAND_ASSIGN(dest_value);

    it = scp_iterator3_new(call_parameters, &arc1, &elem1);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, call_parameters, &arc1, &elem1))
    {
        elem1.param_type = SCP_FIXED;
        searchElStr3(&source_var, &elem1, &dest_value);

        source_var.param_type = SCP_FIXED;
        dest_value.param_type = SCP_FIXED;

        if (SCP_RESULT_TRUE != searchElStr5(scp_procedure_params, &arc1, &source_var, &arc2, &rrel_in))
        {
            printEl(scp_procedure_params);
            printEl(&source_var);
            return print_error("Illegal parameter", "Call parameter is not scp-procedure in-parameter");
        }
        if (SCP_RESULT_TRUE != searchElStr3(scp_procedure_vars, &arc1, &source_var))
        {
            printEl(scp_procedure_vars);
            printEl(&source_var);
            return print_error("Illegal parameter", "Call parameter is not scp-procedure variable");
        }

        is_out = searchElStr5(scp_procedure_params, &arc1, &source_var, &arc2, &rrel_out);
        if (is_out == SCP_RESULT_ERROR)
        {
            return SCP_RESULT_ERROR;
        }
        if (is_out == SCP_RESULT_TRUE)
        {
            dest_var.param_type = SCP_ASSIGN;
            dest_var.element_type = source_var.element_type;
            genElStr3(scp_process_vars, &arc2, &dest_var);
            dest_var.param_type = SCP_FIXED;
            genElStr5(&source_var, &arc3, &dest_var, &arc2, scp_process_copies);
            genElStr5(&dest_var, &arc3, &dest_value, &arc2, scp_process_values);
        }
        else
        {
            genElStr3(scp_process_consts, &arc1, &dest_value);
            genElStr5(&source_var, &arc3, &dest_value, &arc2, scp_process_copies);
        }

        elem1.param_type = SCP_ASSIGN;
        source_var.param_type = SCP_ASSIGN;
        dest_value.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result create_operator_copying_request(scp_operand *operator_copy, scp_operand *scp_process_node, scp_operand *scp_operators_copying_request_set)
{
    scp_operand quest, arc1, arc2;
    MAKE_DEFAULT_NODE_ASSIGN(quest);
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    genElStr5(&quest, &arc1, operator_copy, &arc2, &rrel_1);
    quest.param_type = SCP_FIXED;
    genElStr5(&quest, &arc1, scp_process_node, &arc2, &rrel_2);
    genElStr3(scp_operators_copying_request_set, &arc1, &quest);
    genElStr3(&question_scp_operator_copying_request, &arc1, &quest);
    //genElStr3(&question_initiated, &arc1, &quest);
    return SCP_RESULT_TRUE;
}

sc_result create_scp_process(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, scp_procedure_node, scp_process_node, node1, node2, question_node, call_parameters,
                scp_process_consts, scp_process_vars, scp_process_copies, scp_process_values, scp_process_operators,
                scp_operators_copying_request_set;
    scp_iterator3 *it;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_consts);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_vars);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_copies);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_values);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_operators);
    MAKE_DEFAULT_OPERAND_ASSIGN(scp_procedure_node);
    MAKE_DEFAULT_OPERAND_FIXED(scp_process_node);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    MAKE_DEFAULT_NODE_ASSIGN(call_parameters);
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-process creating", "Can't find interpreting request node");
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_procedure_node, &arc2, &rrel_1))
    {
        print_error("scp-process creating", "Can't find scp-procedure");
        return SC_RESULT_ERROR;
    }
    scp_procedure_node.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &call_parameters, &arc2, &rrel_2))
    {
        print_error("scp-process creating", "Can't find call parameters");
        return SC_RESULT_ERROR;
    }
    call_parameters.param_type = SCP_FIXED;

    //scp-procedure search
    if (SCP_RESULT_TRUE != searchElStr3(&scp_procedure, &arc1, &scp_procedure_node))
    {
        return SC_RESULT_OK;
    }

    //Genering scp-process
    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    scp_procedure_node.param_type = SCP_FIXED;
    genElStr5(&scp_procedure_node, &arc1, &scp_process_node, &arc2, &nrel_scp_process);

    //printEl(&scp_process_node);
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    //Gen scp-process elements
    scp_process_node.param_type = SCP_FIXED;
    genElStr5(&scp_process_node, &arc1, &scp_process_consts, &arc2, &rrel_consts);
    scp_process_consts.param_type = SCP_FIXED;
    genElStr5(&scp_process_node, &arc1, &scp_process_vars, &arc2, &rrel_vars);
    scp_process_vars.param_type = SCP_FIXED;
    genElStr5(&scp_process_node, &arc1, &scp_process_operators, &arc2, &rrel_operators);
    scp_process_operators.param_type = SCP_FIXED;
    genElStr5(&scp_process_node, &arc1, &scp_process_copies, &arc2, &rrel_copies);
    scp_process_copies.param_type = SCP_FIXED;
    genElStr5(&scp_process_node, &arc1, &scp_process_values, &arc2, &rrel_values);
    scp_process_values.param_type = SCP_FIXED;

    //Const set copying
    MAKE_DEFAULT_NODE_ASSIGN(node1);
    if (SCP_RESULT_TRUE == searchElStr5(&scp_procedure_node, &arc1, &node1, &arc2, &rrel_consts))
    {
        node1.param_type = SCP_FIXED;
        copy_consts_set(&node1, &scp_process_consts, &scp_process_copies);
    }
    else
    {
        print_error("scp-process creating", "Can't find scp-procedure's constant set");
        return SC_RESULT_ERROR;
    }

    //Parameters set processing
    node1.param_type = SCP_ASSIGN;
    if (SCP_RESULT_TRUE == searchElStr5(&scp_procedure_node, &arc1, &node1, &arc2, &rrel_params))
    {
        node1.param_type = SCP_FIXED;
    }
    else
    {
        print_error("scp-process creating", "Can't find scp-procedure's parameter set");
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_NODE_ASSIGN(node2);
    if (SCP_RESULT_TRUE == searchElStr5(&scp_procedure_node, &arc1, &node2, &arc2, &rrel_vars))
    {
        node2.param_type = SCP_FIXED;
    }
    else
    {
        print_error("scp-process creating", "Can't find scp-procedure's variable set");
        return SC_RESULT_ERROR;
    }
    //Parameters set copying
    if (SCP_RESULT_ERROR == copy_parameters_set(&call_parameters, &node2, &node1, &scp_process_vars, &scp_process_consts, &scp_process_copies, &scp_process_values))
    {
        return SC_RESULT_ERROR;
    }

    //Vars set copying
    copy_vars_set(&node2, &scp_process_vars, &scp_process_copies);

    //Operators set copying
    node1.param_type = SCP_ASSIGN;
    if (SCP_RESULT_TRUE == searchElStr5(&scp_procedure_node, &arc1, &node1, &arc2, &rrel_operators))
    {
        node1.param_type = SCP_FIXED;
    }
    else
    {
        print_error("scp-process creating", "Can't find scp-procedure's operator set");
    }
    if (SCP_RESULT_ERROR == copy_operator_set(&node1, &scp_process_operators, &scp_process_copies))
    {
        return SC_RESULT_ERROR;
    }

    /*printEl(&scp_procedure_node);
    printEl(&scp_process_node);
    printEl(&scp_process_consts);
    printEl(&scp_process_values);
    printEl(&scp_process_vars);
    printEl(&scp_process_operators);*/


    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_NODE_ASSIGN(scp_operators_copying_request_set);
    genElStr5(&scp_process_node, &arc1, &scp_operators_copying_request_set, &arc2, &nrel_scp_process_operator_copying_requests);
    scp_operators_copying_request_set.param_type = SCP_FIXED;

    node1.param_type = SCP_ASSIGN;
    it = scp_iterator3_new(&scp_process_operators, &arc2, &node1);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &scp_process_operators, &arc2, &node1))
    {
        node1.param_type = SCP_FIXED;
        create_operator_copying_request(&node1, &scp_process_node, &scp_operators_copying_request_set);
        node1.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);

    it = scp_iterator3_new(&scp_operators_copying_request_set, &arc2, &node1);
    while (SCP_RESULT_TRUE == ifVarAssign(&scp_operators_copying_request_set) && SCP_RESULT_TRUE == scp_iterator3_next(it, &scp_operators_copying_request_set, &arc2, &node1))
    {
        node1.param_type = SCP_FIXED;
        genElStr3(&question_initiated, &arc2, &node1);
        node1.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);

    return SC_RESULT_OK;
}

sc_result process_completed_operator_copying_request_set(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, node1, request_set, scp_process_node;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(request_set);
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &request_set))
    {
        print_error("scp-process creating", "Can't find interpreting request node");
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    request_set.param_type = SCP_FIXED;

    MAKE_COMMON_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc2, &request_set, &arc1, &nrel_scp_process_operator_copying_requests))
    {
        return SC_RESULT_ERROR;
    }

    if (SCP_RESULT_TRUE == searchElStr3(&successfully_finished_scp_operator_copying_request_set, &arc1, &request_set))
    {
        //!TODO Start process interpreting
        printf("PROCESS INTERPRETING\n");
    }
    else
    {
        if (SCP_RESULT_TRUE == searchElStr3(&unsuccessfully_finished_scp_operator_copying_request_set, &arc1, &request_set))
        {
            //!TODO Start process destroying
            printf("PROCESS DESTROYING\n");
        }
    }

    request_set.erase = SCP_TRUE;
    eraseEl(&request_set);

    return SC_RESULT_OK;
}

scp_result scp_process_creator_init()
{
    event_program_iterpretation = sc_event_new(question_scp_interpretation_request.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, create_scp_process, 0);
    if (event_program_iterpretation == nullptr)
        return SCP_RESULT_ERROR;
    event_ordinary_operator_copying = sc_event_new(question_initiated.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, copy_ordinary_operator, 0);
    if (event_ordinary_operator_copying == nullptr)
        return SCP_RESULT_ERROR;
    event_call_operator_copying = sc_event_new(question_initiated.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, copy_call_operator, 0);
    if (event_call_operator_copying == nullptr)
        return SCP_RESULT_ERROR;
    event_return_operator_copying = sc_event_new(question_initiated.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, copy_return_operator, 0);
    if (event_return_operator_copying == nullptr)
        return SCP_RESULT_ERROR;
    event_sys_operator_copying = sc_event_new(question_initiated.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, copy_sys_operator, 0);
    if (event_sys_operator_copying == nullptr)
        return SCP_RESULT_ERROR;
    event_operator_copying_finished_successfully = sc_event_new(question_finished_successfully.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, process_successfully_finished_operator_copying_request, 0);
    if (event_operator_copying_finished_successfully == nullptr)
        return SCP_RESULT_ERROR;
    event_operator_copying_finished_unsuccessfully = sc_event_new(question_finished_unsuccessfully.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, process_unsuccessfully_finished_operator_copying_request, 0);
    if (event_operator_copying_finished_unsuccessfully == nullptr)
        return SCP_RESULT_ERROR;
    event_operators_set_copying_completed = sc_event_new(completed_scp_operator_copying_request_set.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, process_completed_operator_copying_request_set, 0);
    if (event_operators_set_copying_completed == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_process_creator_shutdown()
{
    sc_event_destroy(event_program_iterpretation);
    sc_event_destroy(event_ordinary_operator_copying);
    sc_event_destroy(event_call_operator_copying);
    sc_event_destroy(event_return_operator_copying);
    sc_event_destroy(event_sys_operator_copying);
    sc_event_destroy(event_operator_copying_finished_successfully);
    sc_event_destroy(event_operator_copying_finished_unsuccessfully);
    sc_event_destroy(event_operators_set_copying_completed);
    return SCP_RESULT_TRUE;
}
