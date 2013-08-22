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

#include "scp_operator_interpreter_functions.h"

#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"

scp_result resolve_operand_modifiers(scp_operand *scp_operator_node, scp_operand *operand, scp_operand *attr)
{
    scp_operand arc1, arc2, modifier;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN((*operand));
    if (SCP_RESULT_TRUE != searchElStr5(scp_operator_node, &arc1, operand, &arc2, attr))
    {
        printEl(scp_operator_node);
        print_error("scp-operator interpreting", "Can't find required operand");
        return SCP_RESULT_ERROR;
    }
    arc1.param_type = SCP_FIXED;

    MAKE_DEFAULT_NODE_ASSIGN(modifier);
    it = scp_iterator3_new(&modifier, &arc2, &arc1);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &modifier, &arc2, &arc1))
    {
        // Param type
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_assign))
        {
            operand->param_type = SCP_ASSIGN;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_fixed))
        {
            operand->param_type = SCP_FIXED;
            continue;
        }

        // Element type
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_node))
        {
            operand->element_type = operand->element_type | scp_type_node;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_arc))
        {
            operand->element_type = operand->element_type | (~scp_type_node);
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_temp))
        {
            operand->element_type = operand->element_type | scp_type_arc_temp;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_perm))
        {
            operand->element_type = operand->element_type | scp_type_arc_perm;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_pos))
        {
            operand->element_type = operand->element_type | scp_type_arc_pos;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_neg))
        {
            operand->element_type = operand->element_type | scp_type_arc_neg;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_fuz))
        {
            operand->element_type = operand->element_type | scp_type_arc_fuz;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_var))
        {
            operand->element_type = operand->element_type | scp_type_var;
            continue;
        }
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_const))
        {
            operand->element_type = operand->element_type | scp_type_const;
            continue;
        }

        // Set
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_set))
        {
            operand->set = SCP_TRUE;
            continue;
        }

        // Erase
        if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_erase))
        {
            operand->erase = SCP_TRUE;
            continue;
        }
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result find_scp_process_for_scp_operator(scp_operand *scp_operator_node, scp_operand *scp_process_node)
{
    scp_operand arc1, arc2, operator_set;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(operator_set);
    MAKE_DEFAULT_NODE_ASSIGN((*scp_process_node));
    it = scp_iterator3_new(&operator_set, &arc1, scp_operator_node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &operator_set, &arc1, scp_operator_node))
    {
        operator_set.param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr5(scp_process_node, &arc1, &operator_set, &arc2, &rrel_operators))
        {
            scp_process_node->param_type = SCP_FIXED;
            scp_iterator3_free(it);
            return SCP_RESULT_TRUE;
        }
        operator_set.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_FALSE;
}

scp_result get_operands_values(scp_operand *scp_operator_node, scp_operand *operands, scp_operand *operands_values, scp_uint32 count)
{
    scp_operand scp_process_node, var_set, const_set, arc1, arc2, arc3, values_set, var_value;
    scp_uint32 i;
    if (SCP_RESULT_TRUE != find_scp_process_for_scp_operator(scp_operator_node, &scp_process_node))
    {
        print_error("scp-operator interpreting", "Can't find scp-process for given operator");
        return SCP_RESULT_ERROR;
    }
    MAKE_DEFAULT_NODE_ASSIGN(var_set);
    MAKE_DEFAULT_NODE_ASSIGN(const_set);
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &var_set, &arc2, &rrel_vars))
    {
        print_error("scp-operator interpreting", "Can't find scp-process variables set");
        return SCP_RESULT_ERROR;
    }
    var_set.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &const_set, &arc2, &rrel_consts))
    {
        print_error("scp-operator interpreting", "Can't find scp-process constants set");
        return SCP_RESULT_ERROR;
    }
    const_set.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &values_set, &arc2, &rrel_values))
    {
        print_error("scp-operator interpreting", "Can't find scp-process values set");
        return SCP_RESULT_ERROR;
    }
    values_set.param_type = SCP_FIXED;

    MAKE_COMMON_ARC_ASSIGN(arc3);
    MAKE_DEFAULT_OPERAND_ASSIGN(var_value);
    var_value.param_type = SCP_ASSIGN;
    for (i = 0; i < count; i++)
    {
        operands_values[i] = operands[i];
        if (operands[i].param_type == SCP_FIXED)
        {
            if (SCP_RESULT_TRUE == searchElStr3(&var_set, &arc1, operands + i))
            {
                if (SCP_RESULT_TRUE == searchElStr5(operands + i, &arc3, &var_value, &arc1, &values_set))
                {
                    operands_values[i].addr = var_value.addr;
                }
                else
                {
                    printEl(operands + i);
                    print_error("scp-operator interpreting", "Variable has FIXED modifier, but has no value");
                    return SCP_RESULT_ERROR;
                }
            }
        }
        else
        {
            if (SCP_RESULT_TRUE == searchElStr3(&const_set, &arc1, operands + i))
            {
                printEl(operands + i);
                print_error("scp-operator interpreting", "Constant has FIXED modifier");
                return SCP_RESULT_ERROR;
            }
        }
    }
    return SCP_RESULT_TRUE;
}

scp_result set_operands_values(scp_operand *scp_operator_node, scp_operand *operands, scp_operand *operands_values, scp_uint32 count)
{
    scp_operand scp_process_node, arc1, arc2, arc3, values_set, var_value;
    scp_uint32 i;
    if (SCP_RESULT_TRUE != find_scp_process_for_scp_operator(scp_operator_node, &scp_process_node))
    {
        print_error("scp-operator interpreting", "Can't find scp-process for given operator");
        return SCP_RESULT_ERROR;
    }
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    if (SCP_RESULT_TRUE != searchElStr5(&scp_process_node, &arc1, &values_set, &arc2, &rrel_values))
    {
        print_error("scp-operator interpreting", "Can't find scp-process values set");
        return SCP_RESULT_ERROR;
    }
    values_set.param_type = SCP_FIXED;

    MAKE_COMMON_ARC_ASSIGN(arc3);
    MAKE_DEFAULT_OPERAND_ASSIGN(var_value);
    var_value.param_type = SCP_ASSIGN;
    for (i = 0; i < count; i++)
    {
        if (operands[i].param_type == SCP_ASSIGN)
        {
            eraseElStr5(operands + i, &arc3, &var_value, &arc2, &values_set);
            operands_values[i].param_type = SCP_FIXED;
            genElStr5(operands + i, &arc3, operands_values + i, &arc2, &values_set);
        }
    }
    return SCP_RESULT_TRUE;
}

scp_result goto_conditional(scp_operand *scp_operator_node, scp_operand *rrel)
{
    scp_operand arc1, arc2, next_operator;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(next_operator);
    if (SCP_RESULT_TRUE == searchElStr5(scp_operator_node, &arc1, &next_operator, &arc2, rrel))
    {
        next_operator.param_type = SCP_FIXED;
        set_active_operator(&next_operator);
        return SCP_RESULT_TRUE;
    }
    else
    {
        return goto_unconditional(scp_operator_node);
    }
}

scp_result goto_unconditional(scp_operand *scp_operator_node)
{
    scp_operand arc1, arc2, next_operator;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(next_operator);
    if (SCP_RESULT_TRUE == searchElStr5(scp_operator_node, &arc1, &next_operator, &arc2, &rrel_goto))
    {
        next_operator.param_type = SCP_FIXED;
        set_active_operator(&next_operator);
        return SCP_RESULT_TRUE;
    }
    else
    {
        printEl(scp_operator_node);
        print_error("scp-operator interpreting", "Can't find next operator for given");
        return SCP_RESULT_ERROR;
    }
}

void set_active_operator(scp_operand *scp_operator_node)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    genElStr3(&active_scp_operator, &arc, scp_operator_node);
}
