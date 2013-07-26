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

#include "sc_helper.h"
#include "scp_interpreter_utils.h"

#include "scp_keynodes.h"

scp_operand scp_procedure;
scp_operand interpretation_request;
scp_operand scp_process;
scp_operand nrel_scp_process;

// rrels
scp_operand rrel_vars;
scp_operand rrel_consts;
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
scp_operand rrel_node;
scp_operand rrel_arc;
scp_operand rrel_pos;
scp_operand rrel_neg;
scp_operand rrel_fuz;
scp_operand rrel_temp;
scp_operand rrel_perm;

// Ordinals
scp_operand rrel_1;
scp_operand rrel_2;
scp_operand rrel_3;
scp_operand rrel_4;
scp_operand rrel_5;
scp_operand rrel_6;
scp_operand rrel_7;
scp_operand rrel_8;
scp_operand rrel_9;
scp_operand rrel_10;

scp_result scp_keynodes_init()
{
    MAKE_DEFAULT_OPERAND_FIXED(scp_procedure);
    MAKE_DEFAULT_OPERAND_FIXED(interpretation_request);
    MAKE_DEFAULT_OPERAND_FIXED(scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(nrel_scp_process);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_vars);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_consts);
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
    MAKE_DEFAULT_OPERAND_FIXED(rrel_node);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_arc);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_pos);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_neg);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_fuz);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_temp);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_perm);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_1);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_2);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_3);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_4);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_5);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_6);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_7);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_8);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_9);
    MAKE_DEFAULT_OPERAND_FIXED(rrel_10);

    if (SC_TRUE != sc_helper_resolve_system_identifier("scp_procedure", &scp_procedure.addr))
    {
        return print_error("Keynode not found", "scp_procedure");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("question_scp_interpretation_request", &interpretation_request.addr))
    {
        return print_error("Keynode not found", "interpretation_request");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("scp_process", &scp_process.addr))
    {
        return print_error("Keynode not found", "scp_process");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("nrel_scp_process", &nrel_scp_process.addr))
    {
        return print_error("Keynode not found", "nrel_scp_process");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_vars", &rrel_vars.addr))
    {
        return print_error("Keynode not found", "rrel_vars");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_consts", &rrel_consts.addr))
    {
        return print_error("Keynode not found", "rrel_consts");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_params", &rrel_params.addr))
    {
        return print_error("Keynode not found", "rrel_params");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_operators", &rrel_operators.addr))
    {
        return print_error("Keynode not found", "rrel_operators");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_init", &rrel_init.addr))
    {
        return print_error("Keynode not found", "rrel_init");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_in", &rrel_in.addr))
    {
        return print_error("Keynode not found", "rrel_in");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_out", &rrel_out.addr))
    {
        return print_error("Keynode not found", "rrel_out");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_fixed", &rrel_fixed.addr))
    {
        return print_error("Keynode not found", "rrel_fixed");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_assign", &rrel_assign.addr))
    {
        return print_error("Keynode not found", "rrel_assign");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_set", &rrel_set.addr))
    {
        return print_error("Keynode not found", "rrel_set");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_erase", &rrel_erase.addr))
    {
        return print_error("Keynode not found", "rrel_erase");
    }

    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_const", &rrel_const.addr))
    {
        return print_error("Keynode not found", "rrel_const");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_var", &rrel_var.addr))
    {
        return print_error("Keynode not found", "rrel_var");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_node", &rrel_node.addr))
    {
        return print_error("Keynode not found", "rrel_node");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_arc", &rrel_arc.addr))
    {
        return print_error("Keynode not found", "rrel_arc");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_pos", &rrel_pos.addr))
    {
        return print_error("Keynode not found", "rrel_pos");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_neg", &rrel_neg.addr))
    {
        return print_error("Keynode not found", "rrel_neg");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_fuz", &rrel_fuz.addr))
    {
        return print_error("Keynode not found", "rrel_fuz");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_temp", &rrel_temp.addr))
    {
        return print_error("Keynode not found", "rrel_temp");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_perm", &rrel_perm.addr))
    {
        return print_error("Keynode not found", "rrel_perm");
    }

    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_1", &rrel_1.addr))
    {
        return print_error("Keynode not found", "rrel_1");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_2", &rrel_2.addr))
    {
        return print_error("Keynode not found", "rrel_2");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_3", &rrel_3.addr))
    {
        return print_error("Keynode not found", "rrel_3");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_4", &rrel_4.addr))
    {
        return print_error("Keynode not found", "rrel_4");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_5", &rrel_5.addr))
    {
        return print_error("Keynode not found", "rrel_5");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_6", &rrel_6.addr))
    {
        return print_error("Keynode not found", "rrel_6");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_7", &rrel_7.addr))
    {
        return print_error("Keynode not found", "rrel_7");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_8", &rrel_8.addr))
    {
        return print_error("Keynode not found", "rrel_8");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_9", &rrel_9.addr))
    {
        return print_error("Keynode not found", "rrel_9");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("rrel_10", &rrel_10.addr))
    {
        return print_error("Keynode not found", "rrel_10");
    }

    return init_operator_keynodes();
}
