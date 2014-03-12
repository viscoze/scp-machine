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
#include "string.h"
#include "stdio.h"

scp_operand scp_program;
scp_operand agent_scp_program;
scp_operand platform_independent_abstract_sc_agent;
scp_operand abstract_sc_agent;
scp_operand nrel_sc_agent_program;
scp_operand nrel_primary_initiation_condition;

scp_operand question_initiated;
scp_operand question_finished_successfully;
scp_operand question_finished_unsuccessfully;

scp_operand question_scp_interpretation_request;
scp_operand question_scp_procedure_preprocessing_request;
scp_operand scp_process;
scp_operand abstract_scp_machine;
scp_operand useless_scp_process;
scp_operand nrel_scp_process;
scp_operand nrel_value;
scp_operand nrel_authors;
scp_operand nrel_system_identifier;

scp_operand active_scp_operator;
scp_operand active_sc_agent;

// rrels

scp_operand nrel_then;
scp_operand nrel_else;
scp_operand nrel_goto;
scp_operand nrel_error;

scp_operand nrel_scp_program_var;
scp_operand nrel_scp_program_const;
scp_operand nrel_scp_program_copied_const;
scp_operand nrel_template_of_scp_process_creation;
scp_operand nrel_inclusion;
scp_operand rrel_params;
scp_operand rrel_operators;
scp_operand rrel_init;

scp_operand rrel_in;
scp_operand rrel_out;

scp_operand rrel_fixed;
scp_operand rrel_assign;
scp_operand rrel_set;
scp_operand rrel_erase;

scp_operand rrel_const;
scp_operand rrel_var;
scp_operand rrel_scp_const;
scp_operand rrel_scp_var;
scp_operand rrel_node;
scp_operand rrel_arc;
scp_operand rrel_link;
scp_operand rrel_pos;
scp_operand rrel_neg;
scp_operand rrel_fuz;
scp_operand rrel_temp;
scp_operand rrel_perm;
scp_operand rrel_access;
scp_operand rrel_common;
scp_operand rrel_pos_const_perm;

// Events
scp_operand sc_event_elem;
scp_operand sc_event_add_output_arc;
scp_operand sc_event_add_input_arc;
scp_operand sc_event_remove_output_arc;
scp_operand sc_event_remove_input_arc;
scp_operand sc_event_change_link_content;

// Ordinals
scp_operand order_role_relation;
scp_operand ordinal_set_rrel;
scp_operand ordinal_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved
scp_operand ordinal_set_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved

scp_result scp_keynodes_init()
{
    scp_uint32 i = 0;
    char name[12];
    MAKE_DEFAULT_OPERAND_FIXED(scp_program);
    MAKE_DEFAULT_OPERAND_FIXED(agent_scp_program);

    MAKE_DEFAULT_OPERAND_FIXED(platform_independent_abstract_sc_agent);
    MAKE_DEFAULT_OPERAND_FIXED(abstract_sc_agent);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_sc_agent_program);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_primary_initiation_condition);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_inclusion);

    MAKE_DEFAULT_OPERAND_FIXED(question_scp_interpretation_request);
    MAKE_DEFAULT_OPERAND_FIXED(question_scp_procedure_preprocessing_request);
    MAKE_DEFAULT_OPERAND_FIXED(question_initiated);
    MAKE_DEFAULT_OPERAND_FIXED(question_finished_successfully);
    MAKE_DEFAULT_OPERAND_FIXED(question_finished_unsuccessfully);
    MAKE_DEFAULT_OPERAND_FIXED(useless_scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(abstract_scp_machine);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_system_identifier);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_value);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_authors);
    MAKE_DEFAULT_OPERAND_FIXED(active_scp_operator);
    MAKE_DEFAULT_OPERAND_FIXED(active_sc_agent);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_then);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_else);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_goto);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_error);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_scp_program_var);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_scp_program_const);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_scp_program_copied_const);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_template_of_scp_process_creation);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_params);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_operators);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_init);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_in);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_out);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_fixed);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_assign);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_set);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_erase);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_const);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_var);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_scp_const);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_scp_var);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_node);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_link);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_arc);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_pos);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_neg);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_fuz);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_temp);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_perm);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_access);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_common);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_pos_const_perm);
    MAKE_DEFAULT_OPERAND_FIXED(sc_event_elem);
    MAKE_DEFAULT_OPERAND_FIXED(sc_event_add_input_arc);
    MAKE_DEFAULT_OPERAND_FIXED(sc_event_add_output_arc);
    MAKE_DEFAULT_OPERAND_FIXED(sc_event_change_link_content);
    MAKE_DEFAULT_OPERAND_FIXED(sc_event_remove_input_arc);
    MAKE_DEFAULT_OPERAND_FIXED(sc_event_remove_output_arc);
    MAKE_DEFAULT_OPERAND_FIXED(order_role_relation);
    MAKE_DEFAULT_OPERAND_FIXED(ordinal_set_rrel);
    for (i = 1; i <= ORDINAL_RRELS_COUNT; i++)
    {
        MAKE_DEFAULT_OPERAND_FIXED(ordinal_rrels[i]);
    }
    for (i = 1; i <= ORDINAL_SET_RRELS_COUNT; i++)
    {
        MAKE_DEFAULT_OPERAND_FIXED(ordinal_set_rrels[i]);
    }

    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("scp_program", &scp_program))
    {
        return print_error("Keynode not found", "scp_program");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("abstract_scp_machine", &abstract_scp_machine))
    {
        return print_error("Keynode not found", "abstract_scp_machine");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("agent_scp_program", &agent_scp_program))
    {
        return print_error("Keynode not found", "agent_scp_program");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("platform_independent_abstract_sc_agent", &platform_independent_abstract_sc_agent))
    {
        return print_error("Keynode not found", "platform_independent_abstract_sc_agent");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("abstract_sc_agent", &abstract_sc_agent))
    {
        return print_error("Keynode not found", "abstract_sc_agent");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_sc_agent_program", &nrel_sc_agent_program))
    {
        return print_error("Keynode not found", "nrel_sc_agent_program");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_primary_initiation_condition", &nrel_primary_initiation_condition))
    {
        return print_error("Keynode not found", "nrel_primary_initiation_condition");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_inclusion", &nrel_inclusion))
    {
        return print_error("Keynode not found", "nrel_inclusion");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("question_scp_interpretation_request", &question_scp_interpretation_request))
    {
        return print_error("Keynode not found", "question_scp_interpretation_request");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("question_scp_procedure_preprocessing_request", &question_scp_procedure_preprocessing_request))
    {
        return print_error("Keynode not found", "question_scp_procedure_preprocessing_request");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("question_initiated", &question_initiated))
    {
        return print_error("Keynode not found", "question_initiated");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("question_finished_successfully", &question_finished_successfully))
    {
        return print_error("Keynode not found", "question_finished_successfully");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("question_finished_unsuccessfully", &question_finished_unsuccessfully))
    {
        return print_error("Keynode not found", "question_finished_unsuccessfully");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("useless_scp_process", &useless_scp_process))
    {
        return print_error("Keynode not found", "useless_scp_process");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("scp_process", &scp_process))
    {
        return print_error("Keynode not found", "scp_process");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_scp_process", &nrel_scp_process))
    {
        return print_error("Keynode not found", "nrel_scp_process");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_authors", &nrel_authors))
    {
        return print_error("Keynode not found", "nrel_authors");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_system_identifier", &nrel_system_identifier))
    {
        return print_error("Keynode not found", "nrel_system_identifier");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("active_scp_operator", &active_scp_operator))
    {
        return print_error("Keynode not found", "active_scp_operator");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("active_sc_agent", &active_sc_agent))
    {
        return print_error("Keynode not found", "active_sc_agent");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_then", &nrel_then))
    {
        return print_error("Keynode not found", "nrel_then");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_else", &nrel_else))
    {
        return print_error("Keynode not found", "nrel_else");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_goto", &nrel_goto))
    {
        return print_error("Keynode not found", "nrel_goto");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_error", &nrel_error))
    {
        return print_error("Keynode not found", "nrel_error");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_scp_program_var", &nrel_scp_program_var))
    {
        return print_error("Keynode not found", "nrel_scp_program_var");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_scp_program_const", &nrel_scp_program_const))
    {
        return print_error("Keynode not found", "nrel_scp_program_const");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_scp_program_copied_const", &nrel_scp_program_copied_const))
    {
        return print_error("Keynode not found", "nrel_scp_program_copied_const");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_template_of_scp_process_creation", &nrel_template_of_scp_process_creation))
    {
        return print_error("Keynode not found", "nrel_template_of_scp_process_creation");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_params", &rrel_params))
    {
        return print_error("Keynode not found", "rrel_params");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_operators", &rrel_operators))
    {
        return print_error("Keynode not found", "rrel_operators");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("nrel_scp_var_value", &nrel_value))
    {
        return print_error("Keynode not found", "nrel_scp_var_value");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_init", &rrel_init))
    {
        return print_error("Keynode not found", "rrel_init");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_in", &rrel_in))
    {
        return print_error("Keynode not found", "rrel_in");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_out", &rrel_out))
    {
        return print_error("Keynode not found", "rrel_out");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_fixed", &rrel_fixed))
    {
        return print_error("Keynode not found", "rrel_fixed");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_assign", &rrel_assign))
    {
        return print_error("Keynode not found", "rrel_assign");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_set", &rrel_set))
    {
        return print_error("Keynode not found", "rrel_set");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_erase", &rrel_erase))
    {
        return print_error("Keynode not found", "rrel_erase");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_const", &rrel_const))
    {
        return print_error("Keynode not found", "rrel_const");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_var", &rrel_var))
    {
        return print_error("Keynode not found", "rrel_var");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_scp_const", &rrel_scp_const))
    {
        return print_error("Keynode not found", "rrel_scp_const");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_scp_var", &rrel_scp_var))
    {
        return print_error("Keynode not found", "rrel_scp_var");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_node", &rrel_node))
    {
        return print_error("Keynode not found", "rrel_node");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_arc", &rrel_arc))
    {
        return print_error("Keynode not found", "rrel_arc");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_link", &rrel_link))
    {
        return print_error("Keynode not found", "rrel_link");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_pos", &rrel_pos))
    {
        return print_error("Keynode not found", "rrel_pos");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_neg", &rrel_neg))
    {
        return print_error("Keynode not found", "rrel_neg");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_fuz", &rrel_fuz))
    {
        return print_error("Keynode not found", "rrel_fuz");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_temp", &rrel_temp))
    {
        return print_error("Keynode not found", "rrel_temp");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_perm", &rrel_perm))
    {
        return print_error("Keynode not found", "rrel_perm");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_access", &rrel_access))
    {
        return print_error("Keynode not found", "rrel_access");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_common", &rrel_common))
    {
        return print_error("Keynode not found", "rrel_common");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_pos_const_perm", &rrel_pos_const_perm))
    {
        return print_error("Keynode not found", "rrel_pos_const_perm");
    }

    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sc_event", &sc_event_elem))
    {
        return print_error("Keynode not found", "sc_event");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sc_event_add_input_arc", &sc_event_add_input_arc))
    {
        return print_error("Keynode not found", "sc_event_add_input_arc");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sc_event_add_output_arc", &sc_event_add_output_arc))
    {
        return print_error("Keynode not found", "sc_event_add_output_arc");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sc_event_remove_input_arc", &sc_event_remove_input_arc))
    {
        return print_error("Keynode not found", "sc_event_remove_input_arc");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sc_event_remove_output_arc", &sc_event_remove_output_arc))
    {
        return print_error("Keynode not found", "sc_event_remove_output_arc");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sc_event_change_link_content", &sc_event_change_link_content))
    {
        return print_error("Keynode not found", "sc_event_change_link_content");
    }

    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("order_role_relation", &order_role_relation))
    {
        return print_error("Keynode not found", "order_role_relation");
    }

    for (i = 1; i <= ORDINAL_RRELS_COUNT; i++)
    {
        snprintf(name, 8, "rrel_%d", i);
        if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier(name, &ordinal_rrels[i]))
        {
            return print_error("Keynode not found", name);
        }
    }
    for (i = 1; i <= ORDINAL_SET_RRELS_COUNT; i++)
    {
        snprintf(name, 12, "rrel_set_%d", i);
        if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier(name, &ordinal_set_rrels[i]))
        {
            return print_error("Keynode not found", name);
        }
    }

    return init_operator_keynodes();
}
