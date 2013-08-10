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

#ifndef SCP_INTERPRETER_UTILS_H
#define SCP_INTERPRETER_UTILS_H

#include "scp_lib.h"

scp_result print_error(const char *error_type, const char *text);
scp_result resolve_operator_type(scp_operand *oper, scp_operand *type);
scp_result resolve_ordinal_rrel(scp_operand *arc_param, scp_operand *result);

void finish_question_successfully(scp_operand *param);
void finish_question_unsuccessfully(scp_operand *param);

#endif // SCP_INTERPRETER_UTILS_H
