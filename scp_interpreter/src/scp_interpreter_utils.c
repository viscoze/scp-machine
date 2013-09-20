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

#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"
#include "stdio.h"

scp_result print_error(const char *error_type, const char *text)
{
    printf("\nSCP INTERPRETER ERROR: %s : %s\n", error_type, text);
    return SCP_RESULT_ERROR;
}

scp_result resolve_operator_type(scp_operand *oper, scp_operand *type)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    MAKE_DEFAULT_NODE_ASSIGN((*type));

    oper->param_type = SCP_FIXED;
    scp_iterator3 *it = scp_iterator3_new(type, &arc, oper);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, type, &arc, oper))
    {
        //! TODO Remove temporary check
        if (SCP_RESULT_TRUE != ifVarAssign(type))
        {
            continue;
        }
        type->param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr3(&scp_operator, &arc, type))
        {
            scp_iterator3_free(it);
            return SCP_RESULT_TRUE;
        }
        type->param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_FALSE;
}

scp_result resolve_ordinal_rrel(scp_operand *arc_param, scp_operand *result)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    MAKE_DEFAULT_NODE_ASSIGN((*result));

    arc_param->param_type = SCP_FIXED;
    scp_iterator3 *it = scp_iterator3_new(result, &arc, arc_param);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, result, &arc, arc_param))
    {
        result->param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr3(&ordinal_rrel, &arc, result))
        {
            scp_iterator3_free(it);
            return SCP_RESULT_TRUE;
        }
        result->param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_FALSE;
}

void finish_question_successfully(scp_operand *param)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    genElStr3(&question_finished_successfully, &arc, param);
}

void finish_question_unsuccessfully(scp_operand *param)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    genElStr3(&question_finished_unsuccessfully, &arc, param);
}

void mark_scp_process_as_useless(scp_operand *param)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    genElStr3(&useless_scp_process, &arc, param);
    //printf("PROCESS DESTROYING...\n");
}

void set_active_operator(scp_operand *scp_operator_node)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    genElStr3(&active_scp_operator, &arc, scp_operator_node);
}

void load_set_to_hash(scp_operand *set, GHashTable *table)
{
    scp_operand arc1, elem;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem);
    it = scp_iterator3_new(set, &arc1, &elem);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, set, &arc1, &elem))
    {
        g_hash_table_add(table, MAKE_HASH(elem));
    }
    scp_iterator3_free(it);
}

void cantorize_set(scp_operand *set)
{
    GHashTable *table;
    GHashTableIter iter;
    gpointer key, value;
    scp_operand elem, arc1;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem);
    table = g_hash_table_new(NULL, NULL);
    load_set_to_hash(set, table);
    g_hash_table_iter_init(&iter, table);
    arc1.erase = SCP_TRUE;
    eraseSetStr3(set, &arc1, &elem);
    elem.param_type = SCP_FIXED;
    while (TRUE == g_hash_table_iter_next(&iter, &key, &value))
    {
        elem.addr = resolve_sc_addr_from_pointer(key);
        genElStr3(set, &arc1, &elem);
    }
    g_hash_table_destroy(table);
}

void erase_var_set_values(scp_operand *set)
{
    scp_operand arc1, arc2, elem, value;
    scp_iterator5 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    arc1.erase = SCP_TRUE;
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem);
    MAKE_DEFAULT_OPERAND_ASSIGN(value);
    it = scp_iterator5_new(set, &arc1, &elem, &arc2, &rrel_assign);
    while (SCP_RESULT_TRUE == scp_iterator5_next(it, set, &arc1, &elem, &arc2, &rrel_assign))
    {
        elem.param_type = SCP_FIXED;
        arc1.param_type = SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr3(&rrel_scp_var, &arc2, &arc1))
        {
            arc1.param_type = SCP_ASSIGN;
            eraseSetStr5(&elem, &arc1, &value, &arc2, &nrel_value);
        }
        arc1.param_type = SCP_ASSIGN;
        elem.param_type = SCP_ASSIGN;
    }
    scp_iterator5_free(it);
}

sc_addr resolve_sc_addr_from_pointer(gpointer data)
{
    sc_addr elem;
    elem.offset = SC_ADDR_LOCAL_OFFSET_FROM_INT(GPOINTER_TO_INT(data));
    elem.seg = SC_ADDR_LOCAL_SEG_FROM_INT(GPOINTER_TO_INT(data));
    return elem;
}
