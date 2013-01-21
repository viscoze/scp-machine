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

#include "sc_search_basic.h"
#include "sc_helper.h"

const char class_question_all_output_const_pos_arc_str[] = "class_question_all_output_const_pos_arc";
const char class_question_all_input_const_pos_arc_str[] = "class_question_all_input_const_pos_arc";
const char class_question_all_output_const_pos_arc_with_attr_str[] = "class_question_all_output_const_pos_arc_with_attr";
const char class_question_all_input_const_pos_arc_with_attr_str[] = "class_question_all_input_const_pos_arc_with_attr";
const char class_question_full_semantic_neighbourhood_str[] = "class_question_full_semantic_neighbourhood";
const char nrel_answer_str[] = "nrel_answer";

// --------------------- Module ------------------------
sc_result initialize()
{

    if (sc_helper_resolve_system_identifier(class_question_all_output_const_pos_arc_str, &class_question_all_output_const_pos_arc) == SC_FALSE)
        return SC_RESULT_ERROR;

    if (sc_helper_resolve_system_identifier(class_question_all_input_const_pos_arc_str, &class_question_all_input_const_pos_arc) == SC_FALSE)
        return SC_RESULT_ERROR;

    if (sc_helper_resolve_system_identifier(class_question_all_output_const_pos_arc_with_attr_str, &class_question_all_output_const_pos_arc_with_attr) == SC_FALSE)
        return SC_RESULT_ERROR;

    if (sc_helper_resolve_system_identifier(class_question_all_input_const_pos_arc_with_attr_str, &class_question_all_input_const_pos_arc_with_attr) == SC_FALSE)
        return SC_RESULT_ERROR;

    if (sc_helper_resolve_system_identifier(nrel_answer_str, &nrel_answer) == SC_FALSE)
        return SC_RESULT_ERROR;

    if (sc_helper_resolve_system_identifier(class_question_full_semantic_neighbourhood_str, &class_question_full_semantic_neighbourhood) == SC_FALSE)
        return SC_RESULT_ERROR;

    /*event_question_search_all_output_arcs = sc_event_new(keynode_question_initiated, SC_EVENT_ADD_OUTPUT_ARC, 0, question_search_all_output_arcs, 0);
    if (event_question_search_all_output_arcs == nullptr)
        return SC_RESULT_ERROR;*/

    return SC_RESULT_OK;
}

sc_result shutdown()
{
    //sc_event_destroy(event_question_search_all_output_arcs);

    return SC_RESULT_OK;
}
