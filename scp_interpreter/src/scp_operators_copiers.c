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
#include "scp_operators_copiers.h"
#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"

#include <stdio.h>

scp_result copy_arc_modifiers(scp_operand *source_arc, scp_operand *dest_arc)
{
    scp_operand modifier, arc;
    MAKE_DEFAULT_NODE_ASSIGN(modifier);
    MAKE_DEFAULT_ARC_ASSIGN(arc);

    scp_iterator3 *it1 = scp_iterator3_new(&modifier, &arc, source_arc);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &modifier, &arc, source_arc))
    {
        modifier.param_type = SCP_FIXED;
        genElStr3(&modifier, &arc, dest_arc);
        modifier.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it1);
    return SCP_RESULT_TRUE;
}

scp_result copy_operand_set_with_modifiers(scp_operand *source, scp_operand *dest, scp_operand *copies)
{
    scp_operand current_operand, current_operand_copy, arc1, arc2, arc3;
    scp_iterator3 *it1;
    MAKE_DEFAULT_OPERAND_ASSIGN(current_operand);
    MAKE_DEFAULT_OPERAND_ASSIGN(current_operand_copy);
    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_ARC_ASSIGN(arc3);
    it1 = scp_iterator3_new(source, &arc2, &current_operand);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it1, source, &arc2, &current_operand))
    {
        current_operand.param_type = SCP_FIXED;
        current_operand_copy.param_type = SCP_ASSIGN;
        if (SCP_RESULT_TRUE != searchElStr5(&current_operand, &arc1, &current_operand_copy, &arc3, copies))
        {
            printEl(&current_operand);
            print_error("scp-operator copying", "Undefined operand");
            return SCP_RESULT_ERROR;
        }
        current_operand_copy.param_type = SCP_FIXED;
        genElStr3(dest, &arc3, &current_operand_copy);
        arc2.param_type = SCP_FIXED;
        arc3.param_type = SCP_FIXED;
        copy_arc_modifiers(&arc2, &arc3);
        arc2.param_type = SCP_ASSIGN;
        arc3.param_type = SCP_ASSIGN;
        current_operand.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it1);
    return SCP_RESULT_TRUE;
}

scp_result copy_operand_set_with_modifiers_system_pair(scp_operand *source, scp_operand *dest, scp_operand *copies)
{
    scp_operand arc1, arc2, arc3, first_operand, second_operand, second_operand_copy;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_COMMON_ARC_ASSIGN(arc3);

    MAKE_DEFAULT_OPERAND_ASSIGN(first_operand);
    if (SCP_RESULT_TRUE != searchElStr5(source, &arc1, &first_operand, &arc2, &(ordinal_rrels[1])))
    {
        print_error("scp-operator copying", "First element of pair not found");
        return SCP_RESULT_ERROR;
    }
    arc1.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&rrel_fixed, &arc2, &arc1))
    {
        print_error("scp-operator copying", "First element of pair must have FIXED modifier");
        return SC_RESULT_ERROR;
    }
    arc1.param_type = SCP_ASSIGN;
    first_operand.param_type = SCP_FIXED;
    genElStr3(dest, &arc1, &first_operand);
    arc1.param_type = SCP_FIXED;
    genElStr3(&(ordinal_rrels[1]), &arc2, &arc1);
    genElStr3(&rrel_fixed, &arc2, &arc1);

    arc1.param_type = SCP_ASSIGN;
    MAKE_DEFAULT_OPERAND_ASSIGN(second_operand);
    MAKE_DEFAULT_OPERAND_ASSIGN(second_operand_copy);
    if (SCP_RESULT_TRUE != searchElStr5(source, &arc1, &second_operand, &arc2, &(ordinal_rrels[2])))
    {
        print_error("scp-operator copying", "Second element of pair not found");
        return SCP_RESULT_ERROR;
    }
    arc1.param_type = SCP_FIXED;
    second_operand.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&second_operand, &arc3, &second_operand_copy, &arc2, copies))
    {
        printEl(&second_operand);
        print_error("scp-operator copying", "Undefined operand");
        return SCP_RESULT_ERROR;
    }
    second_operand_copy.param_type = SCP_FIXED;
    genElStr3(dest, &arc2, &second_operand_copy);
    arc2.param_type = SCP_FIXED;
    copy_arc_modifiers(&arc1, &arc2);

    return SCP_RESULT_TRUE;
}

sc_result copy_sys_operator(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, scp_operator_copy, scp_process_node, node1, question_node, sys_pattern, pattern_params, pattern_results,
                pattern_params_copy, pattern_results_copy, all_result_param, all_result_param_copy, scp_operator_source, scp_process_copies, operator_type, current_pair, current_pair_copy;
    scp_iterator3 *it;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_copy);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_copies);
    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    if (SCP_RESULT_TRUE != ifVarAssign(&arc1))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-operator copying", "Can't find copying request node");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != ifVarAssign(&question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_operator_copying_request, &arc1, &question_node))
    {
        return SC_RESULT_ERROR;
    }

    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_operator_copy, &arc2, &(ordinal_rrels[1])))
    {
        print_error("scp-operator copying", "Can't find scp-operator for copying");
        return SC_RESULT_ERROR;
    }

    resolve_operator_type(&scp_operator_copy, &operator_type);
    operator_type.param_type = SCP_FIXED;

    if (!(SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_gen) ||
          SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_search)))
    {
        return SC_RESULT_ERROR;
    }

    scp_operator_copy.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_process_node, &arc2, &(ordinal_rrels[2])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-process node");
        return SC_RESULT_ERROR;
    }
    scp_process_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &scp_process_copies, &arc2, &rrel_copies))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-process copies element");
        return SC_RESULT_ERROR;
    }
    scp_process_copies.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_source);
    MAKE_COMMON_ARC_ASSIGN(arc1);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &scp_operator_copy, &arc2, &scp_process_copies))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-operator for given copy");
        return SC_RESULT_ERROR;
    }
    scp_operator_source.param_type = SCP_FIXED;

    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_NODE_ASSIGN(sys_pattern);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &sys_pattern, &arc2, &(ordinal_rrels[1])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find system operator pattern");
        return SC_RESULT_ERROR;
    }
    sys_pattern.param_type = SCP_FIXED;
    arc1.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&rrel_fixed, &arc2, &arc1))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "System operator pattern must have FIXED modifier");
        return SC_RESULT_ERROR;
    }
    arc1.param_type = SCP_ASSIGN;
    genElStr3(&scp_operator_copy, &arc1, &sys_pattern);
    arc1.param_type = SCP_FIXED;
    genElStr3(&(ordinal_rrels[1]), &arc2, &arc1);
    genElStr3(&rrel_fixed, &arc2, &arc1);
    arc1.param_type = SCP_ASSIGN;

    MAKE_DEFAULT_NODE_ASSIGN(pattern_results);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &pattern_results, &arc2, &(ordinal_rrels[2])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find result variables set");
        return SC_RESULT_ERROR;
    }
    pattern_results.param_type = SCP_FIXED;
    arc1.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&rrel_fixed, &arc2, &arc1))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Result variables set must have FIXED modifier");
        return SC_RESULT_ERROR;
    }
    arc1.param_type = SCP_ASSIGN;
    MAKE_DEFAULT_NODE_ASSIGN(pattern_results_copy);
    genElStr3(&scp_operator_copy, &arc1, &pattern_results_copy);
    arc1.param_type = SCP_FIXED;
    genElStr3(&(ordinal_rrels[2]), &arc2, &arc1);
    genElStr3(&rrel_fixed, &arc2, &arc1);
    arc1.param_type = SCP_ASSIGN;

    MAKE_DEFAULT_NODE_ASSIGN(pattern_params);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &pattern_params, &arc2, &(ordinal_rrels[3])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find params set for sys operator");
        return SC_RESULT_ERROR;
    }
    pattern_params.param_type = SCP_FIXED;
    arc1.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&rrel_fixed, &arc2, &arc1))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Params set must have FIXED modifier");
        return SC_RESULT_ERROR;
    }
    arc1.param_type = SCP_ASSIGN;
    MAKE_DEFAULT_NODE_ASSIGN(pattern_params_copy);
    genElStr3(&scp_operator_copy, &arc1, &pattern_params_copy);
    arc1.param_type = SCP_FIXED;
    genElStr3(&(ordinal_rrels[3]), &arc2, &arc1);
    genElStr3(&rrel_fixed, &arc2, &arc1);
    arc1.param_type = SCP_ASSIGN;

    MAKE_DEFAULT_NODE_ASSIGN(all_result_param);
    if (SCP_RESULT_TRUE == searchElStr5(&scp_operator_source, &arc1, &all_result_param, &arc2, &(ordinal_rrels[4])))
    {
        all_result_param.param_type = SCP_FIXED;
        MAKE_DEFAULT_NODE_ASSIGN(all_result_param_copy);
        genElStr3(&scp_operator_copy, &arc2, &all_result_param_copy);
        arc1.param_type = SCP_FIXED;
        arc2.param_type = SCP_FIXED;
        copy_arc_modifiers(&arc1, &arc2);
        arc1.param_type = SCP_ASSIGN;
        arc2.param_type = SCP_ASSIGN;
    }

    MAKE_DEFAULT_NODE_ASSIGN(current_pair);
    MAKE_DEFAULT_NODE_ASSIGN(current_pair_copy);
    it = scp_iterator3_new(&pattern_params, &arc1, &current_pair);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &pattern_params, &arc1, &current_pair))
    {
        current_pair.param_type = SCP_FIXED;
        current_pair_copy.param_type = SCP_ASSIGN;
        genElStr3(&pattern_params_copy, &arc2, &current_pair_copy);
        current_pair_copy.param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE != copy_operand_set_with_modifiers_system_pair(&current_pair, &current_pair_copy, &scp_process_copies))
        {
            finish_question_unsuccessfully(&question_node);
            scp_iterator3_free(it);
            return SC_RESULT_ERROR;
        }
        current_pair.param_type = SCP_ASSIGN;
        current_pair_copy.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);

    MAKE_DEFAULT_NODE_ASSIGN(current_pair);
    MAKE_DEFAULT_NODE_ASSIGN(current_pair_copy);
    it = scp_iterator3_new(&pattern_results, &arc1, &current_pair);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &pattern_results, &arc1, &current_pair))
    {
        current_pair.param_type = SCP_FIXED;
        current_pair_copy.param_type = SCP_ASSIGN;
        genElStr3(&pattern_results_copy, &arc2, &current_pair_copy);
        current_pair_copy.param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE != copy_operand_set_with_modifiers_system_pair(&current_pair, &current_pair_copy, &scp_process_copies))
        {
            finish_question_unsuccessfully(&question_node);
            scp_iterator3_free(it);
            return SC_RESULT_ERROR;
        }
        current_pair.param_type = SCP_ASSIGN;
        current_pair_copy.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);

    //printf("SYSTEM\n");
    finish_question_successfully(&question_node);
    return SC_RESULT_OK;
}

sc_result copy_call_operator(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, scp_operator_copy, scp_process_node, node1, question_node, call_procedure, call_procedure_params,
                call_procedure_params_copy, scp_operator_source, scp_process_copies, operator_type;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_copy);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_copies);
    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    if (SCP_RESULT_TRUE != ifVarAssign(&arc1))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-operator copying", "Can't find copying request node");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != ifVarAssign(&question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_operator_copying_request, &arc1, &question_node))
    {
        return SC_RESULT_ERROR;
    }

    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_operator_copy, &arc2, &(ordinal_rrels[1])))
    {
        print_error("scp-operator copying", "Can't find scp-operator for copying");
        return SC_RESULT_ERROR;
    }

    resolve_operator_type(&scp_operator_copy, &operator_type);
    operator_type.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != ifCoin(&operator_type, &op_call))
    {
        return SC_RESULT_ERROR;
    }

    scp_operator_copy.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_process_node, &arc2, &(ordinal_rrels[2])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-process node");
        return SC_RESULT_ERROR;
    }
    scp_process_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &scp_process_copies, &arc2, &rrel_copies))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-process copies element");
        return SC_RESULT_ERROR;
    }
    scp_process_copies.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_source);
    MAKE_COMMON_ARC_ASSIGN(arc1);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &scp_operator_copy, &arc2, &scp_process_copies))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-operator for given copy");
        return SC_RESULT_ERROR;
    }
    scp_operator_source.param_type = SCP_FIXED;

    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_NODE_ASSIGN(call_procedure);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &call_procedure, &arc2, &(ordinal_rrels[1])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-procedure for call");
        return SC_RESULT_ERROR;
    }
    call_procedure.param_type = SCP_FIXED;
    arc1.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&rrel_fixed, &arc2, &arc1))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "scp-procedure must have FIXED modifier");
        return SC_RESULT_ERROR;
    }
    arc1.param_type = SCP_ASSIGN;
    genElStr3(&scp_operator_copy, &arc1, &call_procedure);
    arc1.param_type = SCP_FIXED;
    genElStr3(&(ordinal_rrels[1]), &arc2, &arc1);
    genElStr3(&rrel_fixed, &arc2, &arc1);
    arc1.param_type = SCP_ASSIGN;

    MAKE_DEFAULT_NODE_ASSIGN(call_procedure_params);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &call_procedure_params, &arc2, &(ordinal_rrels[2])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find params for call");
        return SC_RESULT_ERROR;
    }
    call_procedure_params.param_type = SCP_FIXED;
    arc1.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&rrel_fixed, &arc2, &arc1))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Params set must have FIXED modifier");
        return SC_RESULT_ERROR;
    }
    arc1.param_type = SCP_ASSIGN;
    MAKE_DEFAULT_NODE_ASSIGN(call_procedure_params_copy);
    genElStr3(&scp_operator_copy, &arc1, &call_procedure_params_copy);
    arc1.param_type = SCP_FIXED;
    genElStr3(&(ordinal_rrels[2]), &arc2, &arc1);
    genElStr3(&rrel_fixed, &arc2, &arc1);
    arc1.param_type = SCP_ASSIGN;

    if (SCP_RESULT_TRUE != copy_operand_set_with_modifiers(&call_procedure_params, &call_procedure_params_copy, &scp_process_copies))
    {
        finish_question_unsuccessfully(&question_node);
        return SC_RESULT_ERROR;
    }


    //! TODO Copy third parameter

    //printf("CALL\n");
    finish_question_successfully(&question_node);
    return SC_RESULT_OK;
}

sc_result copy_return_operator(sc_event *event, sc_addr arg)
{

    scp_operand arc1, arc2, scp_operator_copy, node1, question_node, operator_type;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_copy);
    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    if (SCP_RESULT_TRUE != ifVarAssign(&arc1))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-operator copying", "Can't find copying request node");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != ifVarAssign(&question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_operator_copying_request, &arc1, &question_node))
    {
        return SC_RESULT_ERROR;
    }

    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_operator_copy, &arc2, &(ordinal_rrels[1])))
    {
        print_error("scp-operator copying", "Can't find scp-operator for copying");
        return SC_RESULT_ERROR;
    }

    resolve_operator_type(&scp_operator_copy, &operator_type);
    operator_type.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != ifCoin(&operator_type, &op_return))
    {
        return SC_RESULT_ERROR;
    }

    //printf("RETURN\n");
    finish_question_successfully(&question_node);
    return SC_RESULT_OK;
}

sc_result copy_ordinary_operator(sc_event *event, sc_addr arg)
{

    scp_operand arc1, arc2, scp_operator_copy, scp_process_node, node1, question_node,
                scp_operator_source, scp_process_copies, operator_type;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_copy);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_copies);
    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    if (SCP_RESULT_TRUE != ifVarAssign(&arc1))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-operator copying", "Can't find copying request node");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != ifVarAssign(&question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_operator_copying_request, &arc1, &question_node))
    {
        return SC_RESULT_ERROR;
    }

    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_operator_copy, &arc2, &(ordinal_rrels[1])))
    {
        print_error("scp-operator copying", "Can't find scp-operator for copying");
        return SC_RESULT_ERROR;
    }

    resolve_operator_type(&scp_operator_copy, &operator_type);
    operator_type.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_call) ||
        SCP_RESULT_TRUE == ifCoin(&operator_type, &op_return) ||
        SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_gen) ||
        SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_search))
    {
        return SC_RESULT_ERROR;
    }

    scp_operator_copy.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_process_node, &arc2, &(ordinal_rrels[2])))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-process node");
        return SC_RESULT_ERROR;
    }
    scp_process_node.param_type = SCP_FIXED;

    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &scp_process_copies, &arc2, &rrel_copies))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-process copies element");
        return SC_RESULT_ERROR;
    }
    scp_process_copies.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(scp_operator_source);
    MAKE_COMMON_ARC_ASSIGN(arc1);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_operator_source, &arc1, &scp_operator_copy, &arc2, &scp_process_copies))
    {
        finish_question_unsuccessfully(&question_node);
        print_error("scp-operator copying", "Can't find scp-operator for given copy");
        return SC_RESULT_ERROR;
    }
    scp_operator_source.param_type = SCP_FIXED;


    if (SCP_RESULT_TRUE != copy_operand_set_with_modifiers(&scp_operator_source, &scp_operator_copy, &scp_process_copies))
    {
        finish_question_unsuccessfully(&question_node);
        return SC_RESULT_ERROR;
    }

    //printf("ORDINARY\n");
    finish_question_successfully(&question_node);
    return SC_RESULT_OK;
}

sc_result process_successfully_finished_operator_copying_request(sc_event *event, sc_addr arg)
{

    scp_operand arc1, arc2, arc3, node1, question_node, request_set;
    scp_iterator3 *it;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_COMMON_ARC_ASSIGN(arc2);
    arc1.addr = arg;
    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-operator copying", "Can't find copying request node");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != ifVarAssign(&question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;
    //Initiation condition check
    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_operator_copying_request, &arc1, &question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_NODE_ASSIGN(request_set);
    MAKE_DEFAULT_ARC_ASSIGN(arc3);
    it = scp_iterator3_new(&request_set, &arc3, &question_node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &request_set, &arc3, &question_node))
    {
        request_set.param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr5(&node1, &arc2, &request_set, &arc1, &nrel_scp_process_operator_copying_requests))
        {
            arc3.param_type = SCP_FIXED;
            arc3.erase = SCP_TRUE;
            eraseEl(&arc3);
            if (SCP_RESULT_TRUE != searchElStr3(&request_set, &arc1, &node1))
            {
                if (SCP_RESULT_TRUE != searchElStr3(&unsuccessfully_finished_scp_operator_copying_request_set, &arc1, &request_set))
                {
                    genElStr3(&successfully_finished_scp_operator_copying_request_set, &arc1, &request_set);
                }
                genElStr3(&completed_scp_operator_copying_request_set, &arc1, &request_set);
            }
            // TODO Remove kostyl
            else
            {
                scp_iterator3 *it1 = scp_iterator3_new(&request_set, &arc1, &node1);
                scp_bool flag = SCP_FALSE;
                while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &request_set, &arc1, &node1))
                {
                    //printf("ARC\n");
                    if (SCP_RESULT_TRUE == ifVarAssign(&arc1))
                    {
                        flag = SCP_TRUE;
                        break;
                    }
                }
                scp_iterator3_free(it1);
                if (flag == SCP_FALSE)
                {
                    if (SCP_RESULT_TRUE != searchElStr3(&unsuccessfully_finished_scp_operator_copying_request_set, &arc1, &request_set))
                    {
                        genElStr3(&successfully_finished_scp_operator_copying_request_set, &arc1, &request_set);
                    }
                    genElStr3(&completed_scp_operator_copying_request_set, &arc1, &request_set);
                }
            }
            // Kostyl END
            break;
        }
        request_set.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    question_node.erase = SCP_TRUE;
    eraseEl(&question_node);
    return SC_RESULT_OK;
}

sc_result process_unsuccessfully_finished_operator_copying_request(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, arc3, node1, question_node, request_set;
    scp_iterator3 *it;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_COMMON_ARC_ASSIGN(arc2);
    arc1.addr = arg;
    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-operator copying", "Can't find copying request node");
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != ifVarAssign(&question_node))
    {
        return SC_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    question_node.param_type = SCP_FIXED;
    //Initiation condition check
    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_operator_copying_request, &arc1, &question_node))
    {
        return SC_RESULT_ERROR;
    }

    MAKE_DEFAULT_NODE_ASSIGN(request_set);
    MAKE_DEFAULT_ARC_ASSIGN(arc3);
    it = scp_iterator3_new(&request_set, &arc3, &question_node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &request_set, &arc3, &question_node))
    {
        request_set.param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr5(&node1, &arc2, &request_set, &arc1, &nrel_scp_process_operator_copying_requests))
        {
            arc3.param_type = SCP_FIXED;
            arc3.erase = SCP_TRUE;
            eraseEl(&arc3);
            genElStr3(&unsuccessfully_finished_scp_operator_copying_request_set, &arc1, &request_set);
            // TODO Remove kostyl
            scp_iterator3 *it1 = scp_iterator3_new(&request_set, &arc1, &node1);
            scp_bool flag = SCP_FALSE;
            while (SCP_RESULT_TRUE == scp_iterator3_next(it1, &request_set, &arc1, &node1))
            {
                //printf("ARC\n");
                if (SCP_RESULT_TRUE == ifVarAssign(&arc1))
                {
                    flag = SCP_TRUE;
                    break;
                }
            }
            scp_iterator3_free(it1);
            if (flag == SCP_FALSE)
            {
                genElStr3(&completed_scp_operator_copying_request_set, &arc1, &request_set);
            }
            // Kostyl END
            break;
        }
        request_set.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    question_node.erase = SCP_TRUE;
    eraseEl(&question_node);
    return SC_RESULT_OK;
}
