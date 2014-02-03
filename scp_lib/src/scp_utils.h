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

#ifndef SCP_UTILS_H
#define SCP_UTILS_H
#include "scp_types.h"

//extern sc_addr format_numeric;

scp_result check_type(sc_addr element, sc_type input_type);
scp_result print_error(const char *operator_name, const char *text);
scp_result check_numeric_type(sc_addr param);
scp_result check_link_parameter_1(const sc_char *operator_name, scp_operand *param1);
scp_result resolve_numbers_1_2(const sc_char *operator_name, scp_operand *param1, scp_operand *param2, double *num1, double *num2);
scp_result resolve_numbers_2_3(const sc_char *operator_name, scp_operand *param1, scp_operand *param2, double *num1, double *num2);
scp_result resolve_number_2(const sc_char *operator_name, scp_operand *param1, double *num1);
scp_result write_link_content_number(double data, sc_addr link);

#endif // SCP_UTILS_H
