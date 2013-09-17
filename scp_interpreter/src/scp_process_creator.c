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
#include "scp_keynodes.h"

#include <stdio.h>
#include <glib.h>

sc_event *event_procedure_iterpretation;

scp_result copy_parameter_set(scp_operand *set, scp_operand *call_params, GHashTable *table, GHashTable *pattern_hash)
{
    scp_operand arc1, arc2, elem, new_elem, ordinal;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem);
    MAKE_DEFAULT_OPERAND_ASSIGN(new_elem);
    it = scp_iterator3_new(set, &arc1, &elem);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, set, &arc1, &elem))
    {
        arc1.param_type = SCP_FIXED;
        ordinal.param_type = SCP_ASSIGN;
        resolve_ordinal_rrel(&arc1, &ordinal);
        ordinal.param_type = SCP_FIXED;
        arc1.param_type = SCP_ASSIGN;
        new_elem.param_type = SCP_ASSIGN;
        if (SCP_RESULT_TRUE != searchElStr5(call_params, &arc1, &new_elem, &arc2, &ordinal))
        {
            scp_iterator3_free(it);
            return print_error("Illegal procedure parameter", "Call parameter missed");;
        }
        new_elem.param_type = SCP_FIXED;
        g_hash_table_insert(table, MAKE_HASH(elem), MAKE_HASH(new_elem));
        g_hash_table_steal(pattern_hash, MAKE_HASH(elem));
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result copy_const_set(scp_operand *set, GHashTable *table, GHashTable *pattern_hash)
{
    scp_operand arc1, elem;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem);
    it = scp_iterator3_new(set, &arc1, &elem);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, set, &arc1, &elem))
    {
        if (TRUE == g_hash_table_contains(table, MAKE_HASH(elem)))
        {
            continue;
        }
        g_hash_table_insert(table, MAKE_HASH(elem), MAKE_HASH(elem));
        g_hash_table_steal(pattern_hash, MAKE_HASH(elem));
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result copy_var_set(scp_operand *set, GHashTable *table, GHashTable *pattern_hash)
{
    scp_operand arc1, elem, new_elem;
    scp_iterator3 *it;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_OPERAND_ASSIGN(elem);
    MAKE_DEFAULT_NODE_ASSIGN(new_elem);
    new_elem.element_type = new_elem.element_type | scp_type_var;
    it = scp_iterator3_new(set, &arc1, &elem);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, set, &arc1, &elem))
    {
        if (TRUE == g_hash_table_contains(table, MAKE_HASH(elem)))
        {
            continue;
        }
        genEl(&new_elem);
        g_hash_table_insert(table, MAKE_HASH(elem), MAKE_HASH(new_elem));
        g_hash_table_steal(pattern_hash, MAKE_HASH(elem));
    }
    scp_iterator3_free(it);
    return SCP_RESULT_TRUE;
}

scp_result check_type(sc_addr element, sc_type input_type)
{
    sc_type type;
    if (SC_RESULT_OK != sc_memory_get_element_type(element, &type))
    {
        return SCP_RESULT_ERROR;
    }
    if ((input_type & type) == input_type)
    {
        return SCP_RESULT_TRUE;
    }
    else
    {
        return SCP_RESULT_FALSE;
    }
    return SCP_RESULT_ERROR;
}

gboolean compare_keys(gpointer key, gpointer value, gpointer user_data)
{
    if (key == user_data)
        return TRUE;
    else
        return FALSE;
}

sc_addr gen_copy(sc_addr elem, GHashTable *copies_hash, GHashTable *pattern_hash)
{
    gpointer result;
    result = g_hash_table_find(copies_hash, compare_keys, MAKE_SC_ADDR_HASH(elem));
    if (result != NULL)
    {
        return resolve_sc_addr_from_pointer(result);
        //g_hash_table_steal(pattern_hash, MAKE_SC_ADDR_HASH(elem));
        //return el;
    }
    if (SCP_RESULT_TRUE == check_type(elem, scp_type_node))
    {
        sc_addr node;
        sc_type type;
        if (FALSE == g_hash_table_contains(pattern_hash, MAKE_SC_ADDR_HASH(elem)))
        {
            result = g_hash_table_find(copies_hash, compare_keys, MAKE_SC_ADDR_HASH(elem));
            if (result == NULL)
            {
                return elem;
            }
            else
            {
                return resolve_sc_addr_from_pointer(result);
            }
        }
        sc_memory_get_element_type(elem, &type);
        node = sc_memory_node_new(type);
        g_hash_table_insert(copies_hash, MAKE_SC_ADDR_HASH(elem), MAKE_SC_ADDR_HASH(node));
        //g_hash_table_steal(pattern_hash, MAKE_SC_ADDR_HASH(elem));
        return node;
    }
    else
    {
        sc_addr begin, end, new_begin, new_end, new_arc;
        sc_type type;
        sc_memory_get_arc_begin(elem, &begin);
        sc_memory_get_arc_end(elem, &end);
        new_begin = gen_copy(begin, copies_hash, pattern_hash);
        new_end = gen_copy(end, copies_hash, pattern_hash);
        sc_memory_get_element_type(elem, &type);
        new_arc = sc_memory_arc_new(type, new_begin, new_end);
        g_hash_table_insert(copies_hash, MAKE_SC_ADDR_HASH(elem), MAKE_SC_ADDR_HASH(new_arc));
        //g_hash_table_steal(pattern_hash, MAKE_SC_ADDR_HASH(elem));
        return new_arc;
    }
}


sc_result create_scp_process(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, scp_procedure_node, vars_set, consts_set, params_set, copying_pattern,
                scp_process_node, node1, question_node, call_parameters, init_operator;
    GHashTable *copies_hash, *pattern_hash;
    GHashTableIter iter;
    gpointer key, value;
    copies_hash = g_hash_table_new(NULL, NULL);
    pattern_hash = g_hash_table_new(NULL, NULL);

    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(scp_procedure_node);
    MAKE_DEFAULT_OPERAND_FIXED(scp_process_node);
    arc1.addr = arg;

    MAKE_DEFAULT_NODE_ASSIGN(node1);
    MAKE_DEFAULT_NODE_ASSIGN(question_node);
    MAKE_DEFAULT_NODE_ASSIGN(call_parameters);
    if (SCP_RESULT_TRUE != ifVarAssign(&arc1))
    {
        return SC_RESULT_ERROR;
    }
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &question_node))
    {
        print_error("scp-process creating", "Can't find interpreting request node");
        return SC_RESULT_ERROR;
    }

    question_node.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr3(&question_scp_interpretation_request, &arc2, &question_node))
    {
        return SC_RESULT_ERROR;
    }
    arc1.erase = SCP_TRUE;
    eraseEl(&arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc1);

    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &scp_procedure_node, &arc2, &(ordinal_rrels[1])))
    {
        print_error("scp-process creating", "Can't find scp-procedure");
        return SC_RESULT_ERROR;
    }
    scp_procedure_node.param_type = SCP_FIXED;
    if (SCP_RESULT_TRUE != searchElStr5(&question_node, &arc1, &call_parameters, &arc2, &(ordinal_rrels[2])))
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
    scp_procedure_node.param_type = SCP_FIXED;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);

    MAKE_DEFAULT_OPERAND_ASSIGN(vars_set);
    searchElStr5(&scp_procedure_node, &arc1, &vars_set, &arc2, &rrel_vars);
    vars_set.param_type = SCP_FIXED;
    MAKE_DEFAULT_OPERAND_ASSIGN(consts_set);
    searchElStr5(&scp_procedure_node, &arc1, &consts_set, &arc2, &rrel_consts);
    consts_set.param_type = SCP_FIXED;
    MAKE_DEFAULT_OPERAND_ASSIGN(params_set);
    searchElStr5(&scp_procedure_node, &arc1, &params_set, &arc2, &rrel_params);
    params_set.param_type = SCP_FIXED;
    MAKE_DEFAULT_OPERAND_ASSIGN(copying_pattern);
    searchElStr5(&scp_procedure_node, &arc1, &copying_pattern, &arc2, &rrel_operators_copying_pattern);
    copying_pattern.param_type = SCP_FIXED;

    load_set_to_hash(&copying_pattern, pattern_hash);

    if (SCP_RESULT_TRUE != copy_parameter_set(&params_set, &call_parameters, copies_hash, pattern_hash))
    {
        return SC_RESULT_OK;
    }
    if (SCP_RESULT_TRUE != copy_var_set(&vars_set, copies_hash, pattern_hash))
    {
        return SC_RESULT_OK;
    }
    if (SCP_RESULT_TRUE != copy_const_set(&consts_set, copies_hash, pattern_hash))
    {
        return SC_RESULT_OK;
    }

    MAKE_COMMON_ARC_ASSIGN(arc1);
    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    scp_procedure_node.param_type = SCP_FIXED;
    genElStr5(&question_node, &arc1, &scp_process_node, &arc2, &nrel_scp_process);
    scp_process_node.param_type = SCP_FIXED;
    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    genElStr3(&scp_process, &arc1, &scp_process_node);

    searchElStr5(&scp_procedure_node, &arc1, &node1, &arc2, &rrel_operators);
    g_hash_table_insert(copies_hash, MAKE_HASH(node1), MAKE_HASH(scp_process_node));
    g_hash_table_steal(pattern_hash, MAKE_HASH(node1));

    g_hash_table_iter_init(&iter, pattern_hash);
    while (TRUE == g_hash_table_iter_next(&iter, &key, &value))
    {
        gen_copy(resolve_sc_addr_from_pointer(key), copies_hash, pattern_hash);
    }

    g_hash_table_destroy(copies_hash);
    g_hash_table_destroy(pattern_hash);

    // Start process interpreting
    //printf("PROCESS CREATED. INTERPRETING...\n");

    MAKE_DEFAULT_OPERAND_ASSIGN(init_operator);
    if (SCP_RESULT_TRUE == searchElStr5(&scp_process_node, &arc1, &init_operator, &arc2, &rrel_init))
    {
        init_operator.param_type = SCP_FIXED;
        set_active_operator(&init_operator);
    }
    else
    {
        print_error("scp-process interpreting", "Can't find init operator");
        mark_scp_process_as_useless(&scp_process_node);
    }

    return SC_RESULT_OK;
}

scp_result scp_process_creator_init()
{
    event_procedure_iterpretation = sc_event_new(question_initiated.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, create_scp_process, 0);
    if (event_procedure_iterpretation == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_process_creator_shutdown()
{
    sc_event_destroy(event_procedure_iterpretation);
    return SCP_RESULT_TRUE;
}
