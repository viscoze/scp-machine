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

#ifndef SCP_KEYNODES_H
#define SCP_KEYNODES_H

#define ORDINAL_RRELS_COUNT 10
#define ORDINAL_SET_RRELS_COUNT 5

#include "scp_lib.h"
#include "scp_operator_keynodes.h"

extern scp_operand scp_program;
extern scp_operand agent_scp_program;
extern scp_operand question_scp_interpretation_request;
extern scp_operand question_scp_procedure_preprocessing_request;

extern scp_operand question_initiated;
extern scp_operand question_finished_successfully;
extern scp_operand question_finished_unsuccessfully;

extern scp_operand scp_process;
extern scp_operand abstract_scp_machine;
extern scp_operand useless_scp_process;
extern scp_operand nrel_scp_process;
//extern scp_operand nrel_parent_scp_operator;
extern scp_operand nrel_value;
extern scp_operand nrel_authors;
extern scp_operand nrel_init_program;
extern scp_operand nrel_system_identifier;

extern scp_operand active_scp_operator;

// rrels
extern scp_operand nrel_then;
extern scp_operand nrel_else;
extern scp_operand nrel_goto;
extern scp_operand nrel_error;

extern scp_operand nrel_scp_program_var;
extern scp_operand nrel_scp_program_const;
extern scp_operand nrel_scp_program_copied_const;
extern scp_operand nrel_template_of_scp_process_creation;
extern scp_operand rrel_params;
extern scp_operand rrel_operators;
extern scp_operand rrel_init;

extern scp_operand rrel_in;
extern scp_operand rrel_out;

extern scp_operand rrel_fixed;
extern scp_operand rrel_assign;
extern scp_operand rrel_set;
extern scp_operand rrel_erase;

extern scp_operand rrel_const;
extern scp_operand rrel_var;
extern scp_operand rrel_scp_const;
extern scp_operand rrel_scp_var;
extern scp_operand rrel_node;
extern scp_operand rrel_link;
extern scp_operand rrel_arc;
extern scp_operand rrel_pos;
extern scp_operand rrel_neg;
extern scp_operand rrel_fuz;
extern scp_operand rrel_temp;
extern scp_operand rrel_perm;
extern scp_operand rrel_access;
extern scp_operand rrel_common;
extern scp_operand rrel_pos_const_perm;

// Events

extern scp_operand sc_event_elem;
extern scp_operand sc_event_add_output_arc;
extern scp_operand sc_event_add_input_arc;
extern scp_operand sc_event_remove_output_arc;
extern scp_operand sc_event_remove_input_arc;
extern scp_operand sc_event_change_link_content;

extern scp_operand rrel_sc_event_type;
extern scp_operand rrel_sc_event_procedure;
extern scp_operand rrel_sc_event_processing_element;

// Ordinals
extern scp_operand order_role_relation;
extern scp_operand ordinal_set_rrel;
extern scp_operand ordinal_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved
extern scp_operand ordinal_set_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved

scp_result scp_keynodes_init();

#endif // SCP_KEYNODES_H
