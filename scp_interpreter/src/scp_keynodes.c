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

scp_operand scp_procedure;

scp_operand question_initiated;
scp_operand question_finished_successfully;
scp_operand question_finished_unsuccessfully;

scp_operand question_scp_interpretation_request;
scp_operand question_scp_procedure_preprocessing_request;
scp_operand scp_process;
scp_operand useless_scp_process;
scp_operand nrel_scp_process;
scp_operand nrel_value;

scp_operand active_scp_operator;

// rrels

scp_operand rrel_then;
scp_operand rrel_else;
scp_operand rrel_goto;
scp_operand rrel_error;

scp_operand rrel_vars;
scp_operand rrel_consts;
scp_operand rrel_operators_copying_pattern;
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
scp_operand rrel_pos;
scp_operand rrel_neg;
scp_operand rrel_fuz;
scp_operand rrel_temp;
scp_operand rrel_perm;

// Ordinals
scp_operand ordinal_rrel;
scp_operand ordinal_set_rrel;
scp_operand ordinal_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved
scp_operand ordinal_set_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved

scp_result scp_keynodes_init()
{
    scp_uint32 i = 0;
    char name[12];
    MAKE_DEFAULT_OPERAND_FIXED(scp_procedure);
    MAKE_DEFAULT_OPERAND_FIXED(question_scp_interpretation_request);
    MAKE_DEFAULT_OPERAND_FIXED(question_scp_procedure_preprocessing_request);
    MAKE_DEFAULT_OPERAND_FIXED(question_initiated);
    MAKE_DEFAULT_OPERAND_FIXED(question_finished_successfully);
    MAKE_DEFAULT_OPERAND_FIXED(question_finished_unsuccessfully);
    MAKE_DEFAULT_OPERAND_FIXED(useless_scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(active_scp_operator);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_then);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_else);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_goto);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_error);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_vars);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_consts);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_operators_copying_pattern);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_params);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_operators);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_value);
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
    MAKE_DEFAULT_OPERAND_FIXED(rrel_arc);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_pos);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_neg);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_fuz);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_temp);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_perm);
    MAKE_DEFAULT_OPERAND_FIXED(ordinal_rrel);
    MAKE_DEFAULT_OPERAND_FIXED(ordinal_set_rrel);
    for (i = 1; i <= ORDINAL_RRELS_COUNT; i++)
    {
        MAKE_DEFAULT_OPERAND_FIXED(ordinal_rrels[i]);
    }
    for (i = 1; i <= ORDINAL_SET_RRELS_COUNT; i++)
    {
        MAKE_DEFAULT_OPERAND_FIXED(ordinal_set_rrels[i]);
    }

    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("scp_procedure", &scp_procedure))
    {
        return print_error("Keynode not found", "scp_procedure");
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
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("active_scp_operator", &active_scp_operator))
    {
        return print_error("Keynode not found", "active_scp_operator");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_then", &rrel_then))
    {
        return print_error("Keynode not found", "rrel_then");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_else", &rrel_else))
    {
        return print_error("Keynode not found", "rrel_else");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_goto", &rrel_goto))
    {
        return print_error("Keynode not found", "rrel_goto");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_error", &rrel_error))
    {
        return print_error("Keynode not found", "rrel_error");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_vars", &rrel_vars))
    {
        return print_error("Keynode not found", "rrel_vars");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_consts", &rrel_consts))
    {
        return print_error("Keynode not found", "rrel_consts");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("rrel_operators_copying_pattern", &rrel_operators_copying_pattern))
    {
        return print_error("Keynode not found", "rrel_operators_copying_pattern");
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

    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ordinal_rrel", &ordinal_rrel))
    {
        return print_error("Keynode not found", "ordinal_rrel");
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
