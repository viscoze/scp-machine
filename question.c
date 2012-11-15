#include "question.h"
#include "identification.h"

//! TODO Remove this
void temp_gen_question_nodes(){
    gen_element_with_id("class_question",sc_type_const|sc_type_node_class);
    gen_element_with_id("class_question_initiated",sc_type_const|sc_type_node_class);
    gen_element_with_id("class_question_all_output_const_pos_arc",sc_type_const|sc_type_node_class);
    gen_element_with_id("class_question_all_input_const_pos_arc",sc_type_const|sc_type_node_class);
    gen_element_with_id("class_question_full_semantic_neighbourhood",sc_type_const|sc_type_node_class);
    gen_element_with_id("nrel_answer",sc_type_const|sc_type_node_class);
}

void init_questions()
{
    temp_gen_question_nodes();

    CLASS_QUESTION=find_element_by_id("class_question");
    CLASS_QUESTION_INITIATED=find_element_by_id("class_question_initiated");
    CLASS_QUESTION_ALL_OUTPUT_CONST_POS_ARC=find_element_by_id("class_question_all_output_const_pos_arc");
    CLASS_QUESTION_ALL_INPUT_CONST_POS_ARC=find_element_by_id("class_question_all_input_const_pos_arc");
    CLASS_QUESTION_FULL_SEMANTIC_NEIGHBOURHOOD=find_element_by_id("class_question_full_semantic_neighbourhood");
    NREL_ANSWER=find_element_by_id("nrel_answer");
}
