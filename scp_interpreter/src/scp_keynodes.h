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

#include "scp_lib.h"
#include "scp_operator_keynodes.h"

extern scp_operand scp_procedure;
extern scp_operand question_scp_interpretation_request;
extern scp_operand question_scp_procedure_preprocessing_request;
extern scp_operand question_scp_operator_copying_request;

extern scp_operand question_initiated;
extern scp_operand question_finished_successfully;
extern scp_operand question_finished_unsuccessfully;
extern scp_operand successfully_finished_scp_operator_copying_request_set;
extern scp_operand unsuccessfully_finished_scp_operator_copying_request_set;
extern scp_operand completed_scp_operator_copying_request_set;

extern scp_operand scp_process;
extern scp_operand useless_scp_process;
extern scp_operand nrel_scp_process;
extern scp_operand nrel_value;
extern scp_operand nrel_scp_process_operator_copying_requests;

extern scp_operand active_scp_operator;

// rrels
extern scp_operand rrel_then;
extern scp_operand rrel_else;
extern scp_operand rrel_goto;
extern scp_operand rrel_error;

extern scp_operand rrel_vars;
extern scp_operand rrel_consts;
extern scp_operand rrel_operators_copying_pattern;
extern scp_operand rrel_params;
extern scp_operand rrel_operators;
extern scp_operand rrel_copies;
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
extern scp_operand rrel_arc;
extern scp_operand rrel_pos;
extern scp_operand rrel_neg;
extern scp_operand rrel_fuz;
extern scp_operand rrel_temp;
extern scp_operand rrel_perm;

// Ordinals
/*extern scp_operand rrel_1;
extern scp_operand rrel_2;
extern scp_operand rrel_3;
extern scp_operand rrel_4;
extern scp_operand rrel_5;
extern scp_operand rrel_6;
extern scp_operand rrel_7;
extern scp_operand rrel_8;
extern scp_operand rrel_9;
extern scp_operand rrel_10;*/
extern scp_operand ordinal_rrel;
extern scp_operand ordinal_rrels[ORDINAL_RRELS_COUNT + 1]; // 0 element reserved

scp_result scp_keynodes_init();

#endif // SCP_KEYNODES_H
