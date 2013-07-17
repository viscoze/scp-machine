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

#include "scp_types.h"

#include "sc_memory_headers.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

sc_addr format_numeric;

#define NUMBER_PRECISE 8

scp_result check_type(sc_addr element, sc_type input_type)
{
    sc_type type;
    if (SC_RESULT_OK != sc_memory_get_element_type(element, &type))
    {
        return SCP_ERROR;
    }
    if ((input_type & type) == input_type)
    {
        return SCP_TRUE;
    }
    else
    {
        return SCP_FALSE;
    }
    return SCP_ERROR;
}

scp_result print_error(const char *operator_name, const char *text)
{
    printf("\nSCP LIBRARY ERROR: %s : %s\n", operator_name, text);
    return SCP_ERROR;
}

scp_result check_numeric_type(sc_addr param)
{
    sc_iterator3 *it = sc_iterator3_a_a_f_new(sc_type_node | scp_type_const, sc_type_arc_pos_const_perm, param);
    while (SC_TRUE == sc_iterator3_next(it))
    {
        if (SC_ADDR_IS_EQUAL(format_numeric, sc_iterator3_value(it, 0)))
        {
            sc_iterator3_free(it);
            return SCP_TRUE;
        }
    }
    sc_iterator3_free(it);
    return SCP_FALSE;
}

scp_result resolve_numbers_1_2(const sc_char *operator_name, scp_operand *param1, scp_operand *param2, double *num1, double *num2)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1, *data2;
    if (SCP_ASSIGN == param1->param_type || SCP_ASSIGN == param2->param_type)
    {
        return print_error(operator_name, "Both parameters must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error(operator_name, "Parameter 1 has not value");
    }
    if (SC_FALSE == sc_memory_is_element(param2->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (check_type(param1->addr, scp_type_link) == SCP_FALSE || check_type(param2->addr, scp_type_link) == SCP_FALSE)
    {
        return print_error(operator_name, "Both parameters must have link type");
    }
    if (SCP_FALSE == check_numeric_type(param1->addr) || SCP_FALSE == check_numeric_type(param2->addr))
    {
        return print_error(operator_name, "Both parameters must have numeric format");
    }

    if (sc_memory_get_link_content(param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 1 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    if (sc_memory_get_link_content(param2->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data2 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data2, length, &read_length);
    sc_stream_free(stream);

    (*num1) = atof(data1);
    (*num2) = atof(data2);
    free(data1);
    free(data2);
    return SCP_TRUE;
}

scp_result resolve_numbers_2_3(const sc_char *operator_name, scp_operand *param1, scp_operand *param2, double *num1, double *num2)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1, *data2;
    if (SCP_ASSIGN == param1->param_type || SCP_ASSIGN == param2->param_type)
    {
        return print_error(operator_name, "Parameters 2 and 3 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (SC_FALSE == sc_memory_is_element(param2->addr))
    {
        return print_error(operator_name, "Parameter 3 has not value");
    }
    if (check_type(param1->addr, scp_type_link) == SCP_FALSE || check_type(param2->addr, scp_type_link) == SCP_FALSE)
    {
        return print_error(operator_name, "Parameters 2 and 3 must have link type");
    }
    if (SCP_FALSE == check_numeric_type(param1->addr) || SCP_FALSE == check_numeric_type(param2->addr))
    {
        return print_error(operator_name, "Parameters 2 and 3 must have numeric format");
    }

    if (sc_memory_get_link_content(param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    if (sc_memory_get_link_content(param2->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 3 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data2 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data2, length, &read_length);
    sc_stream_free(stream);

    (*num1) = atof(data1);
    (*num2) = atof(data2);
    free(data1);
    free(data2);
    return SCP_TRUE;
}

scp_result resolve_number_2(const sc_char *operator_name, scp_operand *param1, double *num1)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1;
    if (SCP_ASSIGN == param1->param_type)
    {
        return print_error(operator_name, "Parameter 2 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(param1->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (check_type(param1->addr, scp_type_link) == SCP_FALSE)
    {
        return print_error(operator_name, "Parameter 2 must have link type");
    }
    if (SCP_FALSE == check_numeric_type(param1->addr))
    {
        return print_error(operator_name, "Parameter 2 must have numeric format");
    }

    if (sc_memory_get_link_content(param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    (*num1) = atof(data1);
    free(data1);
    return SCP_TRUE;
}

scp_result check_link_parameter_1(const sc_char *operator_name, scp_operand *param1)
{
    if (SCP_ASSIGN == param1->param_type)
    {
        param1->addr = sc_memory_link_new();
        sc_memory_arc_new(sc_type_arc_pos_const_perm, format_numeric, param1->addr);
    }
    else
    {
        if (SC_FALSE == sc_memory_is_element(param1->addr))
        {
            return print_error(operator_name, "Parameter 1 has not value");
        }
        if (check_type(param1->addr, scp_type_link) == SCP_FALSE)
        {
            return print_error(operator_name, "Parameter 1 must have link type");
        }
    }
    return SCP_TRUE;
}

scp_result write_link_content_number(double data, sc_addr link)
{
    sc_stream *stream;
    char *content = calloc(NUMBER_PRECISE, sizeof(sc_char));
    snprintf(content, NUMBER_PRECISE, "%lf", data);
    stream = sc_stream_memory_new(content, strlen(content), SC_STREAM_READ, SC_FALSE);
    if (SC_RESULT_OK != sc_memory_set_link_content(link, stream))
    {
        free(content);
        sc_stream_free(stream);
        return SCP_ERROR;
    }
    free(content);
    sc_stream_free(stream);
    return SCP_TRUE;
}
