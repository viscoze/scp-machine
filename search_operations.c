#include "search.h"
#include "question.h"
#include "system.h"

sc_result operation_search_all_const_pos_output_arc(sc_event *event, sc_addr arg)
{
    sc_addr quest,param,answer;
    if (!sc_memory_get_arc_end(arg,&quest)){return SC_RESULT_ERROR_INVALID_PARAMS;};
    if (!get_question_single_param(CLASS_QUESTION_ALL_OUTPUT_CONST_POS_ARC,quest,&param)){return SC_RESULT_ERROR_INVALID_PARAMS;};

    answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_output_arc(param,answer);
    print_element(answer);

    sc_addr arc=sc_memory_arc_new(sc_type_arc_common|sc_type_const,quest,answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,NREL_ANSWER,arc);

    return SC_RESULT_OK;
}

sc_result operation_search_all_const_pos_input_arc(sc_event *event, sc_addr arg)
{
    sc_addr quest,param,answer;
    if (!sc_memory_get_arc_end(arg,&quest)){return SC_RESULT_ERROR_INVALID_PARAMS;};
    if (!get_question_single_param(CLASS_QUESTION_ALL_INPUT_CONST_POS_ARC,quest,&param)){return SC_RESULT_ERROR_INVALID_PARAMS;};
    answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_input_arc(param,answer);
    print_element(answer);

    sc_addr arc=sc_memory_arc_new(sc_type_arc_common|sc_type_const,quest,answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,NREL_ANSWER,arc);

    return SC_RESULT_OK;
}

sc_result operation_search_full_semantic_neighbourhood(sc_event *event, sc_addr arg)
{
    sc_addr quest,param,answer;
    if (!sc_memory_get_arc_end(arg,&quest)){return SC_RESULT_ERROR_INVALID_PARAMS;};
    if (!get_question_single_param(CLASS_QUESTION_FULL_SEMANTIC_NEIGHBOURHOOD,quest,&param)){return SC_RESULT_ERROR_INVALID_PARAMS;};

    answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(param,answer);
    print_element(answer);

    sc_addr arc=sc_memory_arc_new(sc_type_arc_common|sc_type_const,quest,answer);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,NREL_ANSWER,arc);

    return SC_RESULT_OK;
}
