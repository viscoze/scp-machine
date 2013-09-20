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

#ifndef SCP_OPERATOR_INTERPRETER_FUNCTIONS_H
#define SCP_OPERATOR_INTERPRETER_FUNCTIONS_H

#include "scp_lib.h"

//scp_result resolve_operand_modifiers(scp_operand *scp_operator_node, scp_operand *operand, scp_operand *attr);
scp_result resolve_operands_modifiers(scp_operand *scp_operator_node, scp_operand *operands, scp_uint32 count);
scp_result find_scp_process_for_scp_operator(scp_operand *scp_operator_node, scp_operand *scp_process_node);
scp_result get_operands_values(scp_operand *scp_operator_node, scp_operand *operands, scp_operand *operands_values, scp_uint32 count);
scp_result set_operands_values(scp_operand *operands, scp_operand *operands_values, scp_uint32 count);
scp_result goto_conditional(scp_operand *scp_operator_node, scp_operand *rrel);
scp_result goto_unconditional(scp_operand *scp_operator_node);
scp_uint32 check_ordinal_rrel(scp_operand *node, scp_uint32 count);
void set_active_operator(scp_operand *scp_operator_node);
void operator_interpreting_crash(scp_operand *operator_node);


#endif // SCP_OPERATOR_INTERPRETER_FUNCTIONS_H
