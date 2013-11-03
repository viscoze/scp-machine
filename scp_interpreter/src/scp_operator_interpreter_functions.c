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

#include <stdio.h>

scp_uint32 check_ordinal_rrel(scp_operand *node, scp_uint32 count)
{
    scp_uint32 i = 0;
    for (i = 1; i <= count; i++)
    {
        if (SCP_RESULT_TRUE == ifCoin(node, ordinal_rrels + i))
        {
            return i;
        }
    }
    return 0;
}

scp_uint32 check_ordinal_set_rrel(scp_operand *node, scp_uint32 count)
{
    scp_uint32 i = 0;
    for (i = 1; i <= count; i++)
    {
        if (SCP_RESULT_TRUE == ifCoin(node, ordinal_set_rrels + i))
        {
            return i;
        }
    }
    return 0;
}

scp_result resolve_operands_modifiers(scp_operand *scp_operator_node, scp_operand *operands, scp_uint32 count)
{
    scp_operand arc1, arc2, modifier, operand_node, operand;
    scp_iterator3 *it, *it0;
    scp_uint32 rrel_number = 0;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(operand);
    MAKE_DEFAULT_OPERAND_ASSIGN(operand_node);
    MAKE_DEFAULT_NODE_ASSIGN(modifier);
    scp_operator_node->param_type = SCP_FIXED;
    it0 = scp_iterator3_new(scp_operator_node, &arc1, &operand_node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it0, scp_operator_node, &arc1, &operand_node))
    {
        arc1.param_type = SCP_FIXED;
        operand_node.param_type = SCP_FIXED;
        rrel_number = 0;
        MAKE_DEFAULT_OPERAND_ASSIGN(operand);
        it = scp_iterator3_new(&modifier, &arc2, &arc1);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &modifier, &arc2, &arc1))
        {
            if (rrel_number == 0)
            {
                rrel_number = check_ordinal_rrel(&modifier, count);
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

            // Element type
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_node))
            {
                operand.element_type = operand.element_type | scp_type_node;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_arc))
            {
                operand.element_type = operand.element_type | scp_type_arc;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_temp))
            {
                operand.element_type = operand.element_type | scp_type_arc_temp;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_perm))
            {
                operand.element_type = operand.element_type | scp_type_arc_perm;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_access))
            {
                operand.element_type = operand.element_type | scp_type_arc_access;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_pos))
            {
                operand.element_type = operand.element_type | scp_type_arc_pos;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_neg))
            {
                operand.element_type = operand.element_type | scp_type_arc_neg;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_fuz))
            {
                operand.element_type = operand.element_type | scp_type_arc_fuz;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_var))
            {
                operand.element_type = operand.element_type | scp_type_var;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_const))
            {
                operand.element_type = operand.element_type | scp_type_const;
                continue;
            }

            // Set
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_set))
            {
                operand.set = SCP_TRUE;
                continue;
            }

            // Erase
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_erase))
            {
                operand.erase = SCP_TRUE;
                continue;
            }
        }
        scp_iterator3_free(it);

        if (rrel_number > 0)
        {
            operands[rrel_number - 1] = operand;
            operands[rrel_number - 1].addr = operand_node.addr;
        }
        arc1.param_type = SCP_ASSIGN;
        operand_node.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it0);
    return SCP_RESULT_TRUE;
}

scp_result resolve_operands_modifiers_with_set(scp_operand *scp_operator_node, scp_operand *operands, scp_operand *sets, scp_uint32 count)
{
    scp_operand arc1, arc2, modifier, operand_node, operand;
    scp_iterator3 *it, *it0;
    scp_uint32 rrel_number = 0, set_number = 0;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(operand);
    MAKE_DEFAULT_OPERAND_ASSIGN(operand_node);
    MAKE_DEFAULT_NODE_ASSIGN(modifier);
    scp_operator_node->param_type = SCP_FIXED;
    it0 = scp_iterator3_new(scp_operator_node, &arc1, &operand_node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it0, scp_operator_node, &arc1, &operand_node))
    {
        arc1.param_type = SCP_FIXED;
        operand_node.param_type = SCP_FIXED;
        rrel_number = 0;
        set_number = 0;
        MAKE_DEFAULT_OPERAND_ASSIGN(operand);
        it = scp_iterator3_new(&modifier, &arc2, &arc1);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &modifier, &arc2, &arc1))
        {
            if (rrel_number == 0)
            {
                rrel_number = check_ordinal_rrel(&modifier, count);
                if (rrel_number > 0)
                {
                    continue;
                }
            }

            if (set_number == 0)
            {
                set_number = check_ordinal_set_rrel(&modifier, count);
                if (set_number > 0)
                {
                    operand.set = SC_TRUE;
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

            // Element type
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_node))
            {
                operand.element_type = operand.element_type | scp_type_node;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_arc))
            {
                operand.element_type = operand.element_type | (~scp_type_node);
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_temp))
            {
                operand.element_type = operand.element_type | scp_type_arc_temp;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_perm))
            {
                operand.element_type = operand.element_type | scp_type_arc_perm;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_pos))
            {
                operand.element_type = operand.element_type | scp_type_arc_pos;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_neg))
            {
                operand.element_type = operand.element_type | scp_type_arc_neg;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_fuz))
            {
                operand.element_type = operand.element_type | scp_type_arc_fuz;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_var))
            {
                operand.element_type = operand.element_type | scp_type_var;
                continue;
            }
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_const))
            {
                operand.element_type = operand.element_type | scp_type_const;
                continue;
            }

            // Set
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_set))
            {
                operand.set = SCP_TRUE;
                continue;
            }

            // Erase
            if (SCP_RESULT_TRUE == ifCoin(&modifier, &rrel_erase))
            {
                operand.erase = SCP_TRUE;
                continue;
            }
        }
        scp_iterator3_free(it);

        if (rrel_number > 0)
        {
            operands[rrel_number - 1] = operand;
            operands[rrel_number - 1].addr = operand_node.addr;
        }
        else if (set_number > 0)
        {
            sets[set_number - 1] = operand;
            sets[set_number - 1].addr = operand_node.addr;
        }
        arc1.param_type = SCP_ASSIGN;
        operand_node.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it0);
    return SCP_RESULT_TRUE;
}

scp_result find_scp_process_for_scp_operator(scp_operand *scp_operator_node, scp_operand *scp_process_node)
{
    scp_operand arc1;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_NODE_ASSIGN((*scp_process_node));
    it = scp_iterator3_new(scp_process_node, &arc1, scp_operator_node);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, scp_process_node, &arc1, scp_operator_node))
    {
        scp_process_node->param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr3(&scp_process, &arc1, scp_process_node))
        {
            scp_process_node->param_type = SCP_FIXED;
            scp_iterator3_free(it);
            return SCP_RESULT_TRUE;
        }
        scp_process_node->param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_FALSE;
}

scp_result get_operand_value(scp_operand *operand, scp_operand *operand_value)
{
    scp_operand var_value, operand_node, arc1, arc3;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_COMMON_ARC_ASSIGN(arc3);
    arc3.erase = SCP_TRUE;
    MAKE_DEFAULT_OPERAND_ASSIGN(var_value);
    MAKE_DEFAULT_OPERAND_FIXED(operand_node);
    var_value.param_type = SCP_ASSIGN;
    (*operand_value) = (*operand);
    operand_node.addr = operand->addr;
    if (operand->param_type == SCP_FIXED)
    {
        if (SCP_VAR == operand->operand_type)
        {
            if (SCP_RESULT_TRUE == searchElStr5(&operand_node, &arc3, &var_value, &arc1, &nrel_value))
            {
                operand_value->addr = var_value.addr;
            }
            else
            {
                printEl(operand);
                print_error("scp-operator interpreting", "Variable has FIXED modifier, but has no value");
                return SCP_RESULT_ERROR;
            }
        }
    }
    else
    {
        if (SCP_CONST == operand->operand_type)
        {
            printEl(operand);
            print_error("scp-operator interpreting", "Constant has ASSIGN modifier");
            return SCP_RESULT_ERROR;
        }
        else
        {
            eraseElStr5(&operand_node, &arc3, &var_value, &arc1, &nrel_value);
        }
    }
    return SCP_RESULT_TRUE;
}

scp_result get_operands_values(scp_operand *operands, scp_operand *operands_values, scp_uint32 count)
{
    scp_operand arc1, arc3, var_value, operand_node;
    scp_uint32 i;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_COMMON_ARC_ASSIGN(arc3);
    arc3.erase = SCP_TRUE;
    MAKE_DEFAULT_OPERAND_ASSIGN(var_value);
    MAKE_DEFAULT_OPERAND_FIXED(operand_node);
    var_value.param_type = SCP_ASSIGN;
    for (i = 0; i < count; i++)
    {
        operands_values[i] = operands[i];
        operand_node.addr = operands[i].addr;
        if (operands[i].param_type == SCP_FIXED)
        {
            if (SCP_VAR == operands[i].operand_type)
            {
                if (SCP_RESULT_TRUE == searchElStr5(&operand_node, &arc3, &var_value, &arc1, &nrel_value))
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
            if (SCP_CONST == operands[i].operand_type)
            {
                printEl(operands + i);
                print_error("scp-operator interpreting", "Constant has ASSIGN modifier");
                return SCP_RESULT_ERROR;
            }
            else
            {
                eraseElStr5(&operand_node, &arc3, &var_value, &arc1, &nrel_value);
            }
        }
    }
    return SCP_RESULT_TRUE;
}

scp_result get_set_operands_values(scp_operand *operands, scp_operand *operands_values, scp_uint32 count)
{
    scp_operand arc1, arc3, var_value, operand_node;
    scp_uint32 i;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_COMMON_ARC_ASSIGN(arc3);
    arc3.erase = SCP_TRUE;
    MAKE_DEFAULT_OPERAND_ASSIGN(var_value);
    MAKE_DEFAULT_OPERAND_FIXED(operand_node);
    var_value.param_type = SCP_ASSIGN;
    for (i = 0; i < count; i++)
    {
        if (operands[i].set != SCP_TRUE)
            continue;
        operands_values[i] = operands[i];
        operand_node.addr = operands[i].addr;
        if (operands[i].param_type == SCP_FIXED)
        {
            if (SCP_VAR == operands[i].operand_type)
            {
                if (SCP_RESULT_TRUE == searchElStr5(&operand_node, &arc3, &var_value, &arc1, &nrel_value))
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
            if (SCP_CONST == operands[i].operand_type)
            {
                printEl(operands + i);
                print_error("scp-operator interpreting", "Constant has ASSIGN modifier");
                return SCP_RESULT_ERROR;
            }
            else
            {
                eraseElStr5(&operand_node, &arc3, &var_value, &arc1, &nrel_value);
            }
        }
    }
    return SCP_RESULT_TRUE;
}

scp_result set_operands_values(scp_operand *operands, scp_operand *operands_values, scp_uint32 count)
{
    scp_operand arc2, arc3, operand_node;
    scp_uint32 i;
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_COMMON_ARC_ASSIGN(arc3);
    MAKE_DEFAULT_OPERAND_FIXED(operand_node);
    for (i = 0; i < count; i++)
    {
        if (operands[i].param_type == SCP_ASSIGN)
        {
            operand_node.addr = operands[i].addr;
            operands_values[i].param_type = SCP_FIXED;
            genElStr5(&operand_node, &arc3, operands_values + i, &arc2, &nrel_value);
        }
    }
    return SCP_RESULT_TRUE;
}

scp_result set_set_operands_values(scp_operand *operands, scp_operand *operands_values, scp_uint32 count)
{
    scp_operand arc2, arc3, operand_node;
    scp_uint32 i;
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_COMMON_ARC_ASSIGN(arc3);
    MAKE_DEFAULT_OPERAND_FIXED(operand_node);
    for (i = 0; i < count; i++)
    {
        if (operands[i].set == SCP_TRUE && operands[i].param_type == SCP_ASSIGN)
        {
            operand_node.addr = operands[i].addr;
            operands_values[i].param_type = SCP_FIXED;
            genElStr5(&operand_node, &arc3, operands_values + i, &arc2, &nrel_value);
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
        operator_interpreting_crash(scp_operator_node);
        return SCP_RESULT_ERROR;
    }
}

void operator_interpreting_crash(scp_operand *operator_node)
{
    scp_operand scp_process_node;
    find_scp_process_for_scp_operator(operator_node, &scp_process_node);
    mark_scp_process_as_useless(&scp_process_node);
}
