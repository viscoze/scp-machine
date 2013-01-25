/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2012 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS. If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
 */

#include "sc_helper.h"
#include "sc_search_basic.h"
#include "sc_search_functions.h"
#include <stdio.h>

sc_result operation_search_all_const_pos_output_arc(sc_event *event, sc_addr arg) {
    sc_addr quest, param, answer;

    if (!sc_memory_get_arc_end(arg, &quest)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    if (!get_question_single_param(class_question_all_output_const_pos_arc, quest, &param)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };

    answer = sc_memory_node_new(sc_type_node);
    search_all_const_pos_output_arc(param, answer);

    sc_addr arc = sc_memory_arc_new(sc_type_arc_common | sc_type_const, quest, answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, nrel_answer, arc);

    printf("KPM: operation_search_all_const_pos_output_arc worked succesfully\n");

    return SC_RESULT_OK;
}

sc_result operation_search_all_const_pos_input_arc(sc_event *event, sc_addr arg) {
    sc_addr quest, param, answer;
    if (!sc_memory_get_arc_end(arg, &quest)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    if (!get_question_single_param(class_question_all_input_const_pos_arc, quest, &param)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    answer = sc_memory_node_new(sc_type_node);
    search_all_const_pos_input_arc(param, answer);

    sc_addr arc = sc_memory_arc_new(sc_type_arc_common | sc_type_const, quest, answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, nrel_answer, arc);

    printf("KPM: operation_search_all_const_pos_input_arc worked succesfully\n");

    return SC_RESULT_OK;
}

sc_result operation_search_all_const_pos_output_arc_with_rel(sc_event *event, sc_addr arg) {
    sc_addr quest, param, answer;
    if (!sc_memory_get_arc_end(arg, &quest)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    if (!get_question_single_param(class_question_all_output_const_pos_arc_with_rel, quest, &param)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    answer = sc_memory_node_new(sc_type_node);
    search_all_const_pos_output_arc_with_rel(param, answer);

    sc_addr arc = sc_memory_arc_new(sc_type_arc_common | sc_type_const, quest, answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, nrel_answer, arc);

    printf("KPM: operation_search_all_const_pos_output_arc_with_rel worked succesfully\n");

    return SC_RESULT_OK;
}

sc_result operation_search_all_const_pos_input_arc_with_rel(sc_event *event, sc_addr arg) {
    sc_addr quest, param, answer;
    if (!sc_memory_get_arc_end(arg, &quest)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    if (!get_question_single_param(class_question_all_input_const_pos_arc_with_rel, quest, &param)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    answer = sc_memory_node_new(sc_type_node);
    search_all_const_pos_input_arc_with_rel(param, answer);

    sc_addr arc = sc_memory_arc_new(sc_type_arc_common | sc_type_const, quest, answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, nrel_answer, arc);

    printf("KPM: operation_search_all_const_pos_input_arc_with_rel worked succesfully\n");

    return SC_RESULT_OK;
}

sc_result operation_search_full_semantic_neighbourhood(sc_event *event, sc_addr arg) {
    sc_addr quest, param, answer;
    if (!sc_memory_get_arc_end(arg, &quest)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };
    if (!get_question_single_param(class_question_full_semantic_neighbourhood, quest, &param)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };

    answer = sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(param, answer);

    sc_addr arc = sc_memory_arc_new(sc_type_arc_common | sc_type_const, quest, answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, nrel_answer, arc);

    printf("KPM: operation_search_full_semantic_neighbourhood worked succesfully\n");

    return SC_RESULT_OK;
}
