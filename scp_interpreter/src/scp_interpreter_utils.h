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
#include <glib.h>

#define MAKE_SC_ADDR_HASH(elem) GINT_TO_POINTER(SC_ADDR_LOCAL_TO_INT(elem))
#define MAKE_HASH(elem) GINT_TO_POINTER(SC_ADDR_LOCAL_TO_INT((elem).addr))
#define MAKE_PHASH(elem) GINT_TO_POINTER(SC_ADDR_LOCAL_TO_INT((elem)->addr))

scp_result print_error(const char *error_type, const char *text);
scp_result resolve_operator_type(scp_operand *oper, scp_operand *type);
scp_result resolve_ordinal_rrel(scp_operand *arc_param, scp_operand *result);
scp_result get_set_power(scp_operand *set, scp_uint32 *result);

void finish_question_successfully(scp_operand *param);
void finish_question_unsuccessfully(scp_operand *param);

void mark_scp_process_as_useless(scp_operand *param);

void set_active_operator(scp_operand *scp_operator_node);

void cantorize_set(scp_operand *set);
void erase_var_set_values(scp_operand *set);
void load_set_to_hash(scp_operand *set, GHashTable *table);
sc_addr resolve_sc_addr_from_pointer(gpointer data);
#endif // SCP_INTERPRETER_UTILS_H
