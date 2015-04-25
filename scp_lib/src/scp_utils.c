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

//sc_addr format_numeric;

#define NUMBER_PRECISE 8

scp_result check_type(sc_memory_context *context, sc_addr element, sc_type input_type)
{
    sc_type type;
    if (SC_RESULT_OK != sc_memory_get_element_type(context, element, &type))
    {
        return SCP_RESULT_ERROR;
    }
    if ((input_type & type) == input_type)
    {
        return SCP_RESULT_TRUE;
    }
    else
    {
        return SCP_RESULT_FALSE;
    }
    return SCP_RESULT_ERROR;
}

scp_result print_error(const char *operator_name, const char *text)
{
    printf("\nSCP LIBRARY ERROR: %s : %s\n", operator_name, text);
    return SCP_RESULT_ERROR;
}

#ifdef SCP_MATH
scp_result check_numeric_type(sc_memory_context *context, sc_addr param)
{
    //! TODO Add check for numeric type
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_MATH
scp_result resolve_numbers_1_2(sc_memory_context *context, const sc_char *operator_name, scp_operand *param1, scp_operand *param2, double *num1, double *num2)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1, *data2;
    if (SCP_ASSIGN == param1->param_type || SCP_ASSIGN == param2->param_type)
    {
        return print_error(operator_name, "Both parameters must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(context, param1->addr))
    {
        return print_error(operator_name, "Parameter 1 has not value");
    }
    if (SC_FALSE == sc_memory_is_element(context, param2->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (check_type(context, param1->addr, scp_type_link) == SCP_RESULT_FALSE || check_type(context, param2->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error(operator_name, "Both parameters must have link type");
    }
    if (SCP_RESULT_FALSE == check_numeric_type(context, param1->addr) || SCP_RESULT_FALSE == check_numeric_type(context, param2->addr))
    {
        return print_error(operator_name, "Both parameters must have numeric format");
    }

    if (sc_memory_get_link_content(context, param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 1 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    if (sc_memory_get_link_content(context, param2->addr, &stream) != SC_RESULT_OK)
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
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_MATH
scp_result resolve_numbers_2_3(sc_memory_context *context, const sc_char *operator_name, scp_operand *param1, scp_operand *param2, double *num1, double *num2)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1, *data2;
    if (SCP_ASSIGN == param1->param_type || SCP_ASSIGN == param2->param_type)
    {
        return print_error(operator_name, "Parameters 2 and 3 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(context, param1->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (SC_FALSE == sc_memory_is_element(context, param2->addr))
    {
        return print_error(operator_name, "Parameter 3 has not value");
    }
    if (check_type(context, param1->addr, scp_type_link) == SCP_RESULT_FALSE || check_type(context, param2->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error(operator_name, "Parameters 2 and 3 must have link type");
    }
    if (SCP_RESULT_FALSE == check_numeric_type(context, param1->addr) || SCP_RESULT_FALSE == check_numeric_type(context, param2->addr))
    {
        return print_error(operator_name, "Parameters 2 and 3 must have numeric format");
    }

    if (sc_memory_get_link_content(context, param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    if (sc_memory_get_link_content(context, param2->addr, &stream) != SC_RESULT_OK)
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
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_MATH
scp_result resolve_number_2(sc_memory_context *context, const sc_char *operator_name, scp_operand *param1, double *num1)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1;
    if (SCP_ASSIGN == param1->param_type)
    {
        return print_error(operator_name, "Parameter 2 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(context, param1->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (check_type(context, param1->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error(operator_name, "Parameter 2 must have link type");
    }
    if (SCP_RESULT_FALSE == check_numeric_type(context, param1->addr))
    {
        return print_error(operator_name, "Parameter 2 must have numeric format");
    }

    if (sc_memory_get_link_content(context, param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    (*num1) = atof(data1);
    free(data1);
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_MATH
scp_result write_link_content_number(sc_memory_context *context, double data, sc_addr link)
{
    sc_stream *stream;
    char *content = calloc(NUMBER_PRECISE, sizeof(sc_char));
    snprintf(content, NUMBER_PRECISE, "%lf", data);
    stream = sc_stream_memory_new(content, strlen(content), SC_STREAM_READ, SC_FALSE);
    if (SC_RESULT_OK != sc_memory_set_link_content(context, link, stream))
    {
        free(content);
        sc_stream_free(stream);
        return SCP_RESULT_ERROR;
    }
    free(content);
    sc_stream_free(stream);
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_STRING
scp_result check_string_type(sc_memory_context *context, sc_addr param)
{
    //! TODO Add check for string type
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_STRING
scp_result write_link_content_string(sc_memory_context *context, char* data, sc_addr link)
{
    sc_stream *stream;
    size_t data_len = strlen(data) + 1;
    char *content = calloc(data_len, sizeof(sc_char));
    snprintf(content, data_len, "%s", data);
    stream = sc_stream_memory_new(content, strlen(content), SC_STREAM_READ, SC_FALSE);
    if (SC_RESULT_OK != sc_memory_set_link_content(context, link, stream))
    {
        free(content);
        sc_stream_free(stream);
        return SCP_RESULT_ERROR;
    }
    free(content);
    sc_stream_free(stream);
    return SCP_RESULT_TRUE;
}
#endif

#ifdef SCP_STRING
scp_result resolve_strings_2_3(sc_memory_context *context, const sc_char *operator_name, scp_operand *param1, scp_operand *param2, char *str1, char *str2)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1, *data2;
    if (SCP_ASSIGN == param1->param_type || SCP_ASSIGN == param2->param_type)
    {
        return print_error(operator_name, "Parameters 2 and 3 must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(context, param1->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (SC_FALSE == sc_memory_is_element(context, param2->addr))
    {
        return print_error(operator_name, "Parameter 3 has not value");
    }
    if (check_type(context, param1->addr, scp_type_link) == SCP_RESULT_FALSE || check_type(context, param2->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error(operator_name, "Parameters 2 and 3 must have link type");
    }
    if (SCP_RESULT_FALSE == check_numeric_type(context, param1->addr) || SCP_RESULT_FALSE == check_numeric_type(context, param2->addr))
    {
        return print_error(operator_name, "Parameters 2 and 3 must have numeric format");
    }

    if (sc_memory_get_link_content(context, param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    if (sc_memory_get_link_content(context, param2->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 3 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data2 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data2, length, &read_length);
    sc_stream_free(stream);

    size_t len_data1 = strlen(data1) + 1, len_data2 = strlen(data2) + 1;
    str1 = realloc(str1, len_data1);
    memcpy(str1, data1, len_data1);
    str2 = realloc(str2, len_data2);
    memcpy(str2, data2, len_data2);
    free(data1);
    free(data2);
    return SCP_RESULT_TRUE;
}
#endif

scp_result check_link_parameter_1(sc_memory_context *context, const sc_char *operator_name, scp_operand *param1)
{
    if (SCP_ASSIGN == param1->param_type)
    {
        param1->addr = sc_memory_link_new(context);
        //! TODO Add numeric class for link
    }
    else
    {
        if (SC_FALSE == sc_memory_is_element(context, param1->addr))
        {
            return print_error(operator_name, "Parameter 1 has not value");
        }
        if (check_type(context, param1->addr, scp_type_link) == SCP_RESULT_FALSE)
        {
            return print_error(operator_name, "Parameter 1 must have link type");
        }
    }
    return SCP_RESULT_TRUE;
}

#ifdef SCP_STRING
scp_result resolve_strings_1_2(sc_memory_context *context, const sc_char *operator_name, scp_operand *param1,
                               scp_operand *param2, char *str1, char *str2) {
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data1, *data2;
    if (SCP_ASSIGN == param1->param_type || SCP_ASSIGN == param2->param_type)
    {
        return print_error(operator_name, "Both parameters must have FIXED modifier");
    }
    if (SC_FALSE == sc_memory_is_element(context, param1->addr))
    {
        return print_error(operator_name, "Parameter 1 has not value");
    }
    if (SC_FALSE == sc_memory_is_element(context, param2->addr))
    {
        return print_error(operator_name, "Parameter 2 has not value");
    }
    if (check_type(context, param1->addr, scp_type_link) == SCP_RESULT_FALSE || check_type(context, param2->addr, scp_type_link) == SCP_RESULT_FALSE)
    {
        return print_error(operator_name, "Both parameters must have link type");
    }
    if (SCP_RESULT_FALSE == check_string_type(context, param1->addr) || SCP_RESULT_FALSE == check_string_type(context, param2->addr))
    {
        return print_error(operator_name, "Both parameters must have string format");
    }

    if (sc_memory_get_link_content(context, param1->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 1 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data1 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data1, length, &read_length);
    sc_stream_free(stream);
    if (sc_memory_get_link_content(context, param2->addr, &stream) != SC_RESULT_OK)
    {
        return print_error(operator_name, "Parameter 2 content reading error");
    }
    sc_stream_get_length(stream, &length);
    data2 = calloc(length, sizeof(sc_char));
    sc_stream_read_data(stream, data2, length, &read_length);
    sc_stream_free(stream);

    size_t len_data1 = strlen(data1) + 1, len_data2 = strlen(data2) + 1;
    str1 = realloc(str1, len_data1);
    memcpy(str1, data1, len_data1);
    str2 = realloc(str2, len_data2);
    memcpy(str2, data2, len_data2);

    free(data1);
    free(data2);
    return SCP_RESULT_TRUE;
}

#endif
