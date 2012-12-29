#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>

#include "sc_memory.h"
#include "sc_event.h"
#include "sc_iterator.h"
#include "sc_iterator5.h"
#include "sc_stream_memory.h"
#include "identification.h"
#include "question.h"
#include "search.h"
#include "search_operations.h"
#include "system.h"
#include "system_pattern.h"

sc_addr gen_input_output_arcs(){

    sc_addr node;
    sc_addr end_node;
    node=sc_memory_node_new(sc_type_node);
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        i++;
    }
    return node;
}

sc_addr gen_input_output_arcs_with_attr(){

    sc_addr node;
    sc_addr end_node,attr_node,arc_addr;
    node=sc_memory_node_new(sc_type_node);
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        attr_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        attr_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    return node;
}

sc_addr gen_input_output_arcs_with_given_attr(sc_addr attr_node){

    sc_addr node;
    sc_addr end_node,arc_addr;
    node=sc_memory_node_new(sc_type_node);
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    return node;
}

void gen_input_output_arcs_with_given_attr_and_given_node(sc_addr attr_node,sc_addr node){

    sc_addr end_node,arc_addr;
    int i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
    i=0;
    while(i<10){
        end_node=sc_memory_node_new(sc_type_node);
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr_node,arc_addr);
        i++;
    }
}

void test_simple_search(){
    sc_addr node=gen_input_output_arcs();
    print_element(node);
    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_output_arc(node,answer);
    print_element(answer);
    sc_memory_element_free(answer);
    answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_input_arc(node,answer);
    print_element(answer);
    search_full_semantic_neighbourhood(node,answer);
    print_element(answer);
}

void test_attr_search(){
    sc_addr node=gen_input_output_arcs_with_attr();
    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(node,answer);
    print_element(answer);
}

void test_iterator5_inp(){
    sc_addr attr=sc_memory_node_new(sc_type_node);
    sc_addr node=gen_input_output_arcs_with_given_attr(attr);

    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(node,answer);

    printf("\n\n");

    sc_iterator5 *it=sc_iterator5_a_a_f_a_f_new(0,0,node,0,attr);
    sc_addr addr0,addr1,addr3;
    while(sc_iterator5_next(it)){
        addr0=it->results[0];
        addr1=it->results[1];
        addr3=it->results[3];
        printf("\n0:%u|%u 1:%u|%u 3:%u|%u",addr0.seg,addr0.offset,addr1.seg,addr1.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void test_iterator5_outp(){
    sc_addr attr=sc_memory_node_new(sc_type_node);
    sc_addr node=gen_input_output_arcs_with_given_attr(attr);

    sc_addr answer=sc_memory_node_new(sc_type_node);
    search_full_semantic_neighbourhood(node,answer);

    printf("\n\n");

    sc_iterator5 *it=sc_iterator5_f_a_a_a_f_new(node,0,0,0,attr);
    sc_addr addr1,addr2,addr3;
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[2];
        addr3=it->results[3];
        printf("\n1:%u|%u 2:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void test_iterator5_arcs_only(){
    sc_addr attr1=sc_memory_node_new(sc_type_node);
    sc_addr attr2=sc_memory_node_new(sc_type_node);
    sc_addr node=sc_memory_node_new(sc_type_node);
    sc_addr end_node=sc_memory_node_new(sc_type_node);
    sc_addr arc_addr;

    int i=0;
    while(i<10){
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr1,arc_addr);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr2,arc_addr);
        i++;
    }
    /*i=0;
    while(i<10){
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,end_node,node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr1,arc_addr);
        i++;
    }*/

    //sc_addr answer=sc_memory_node_new(sc_type_node);
    //search_full_semantic_neighbourhood(node,answer);

    printf("\nnode1: %u|%u",node.seg,node.offset);
    printf("\nnode3: %u|%u",end_node.seg,end_node.offset);
    printf("\nattr: %u|%u",attr1.seg,attr1.offset);

    sc_iterator5 *it=sc_iterator5_f_a_a_a_f_new(node,0,0,0,attr1);
    sc_addr addr1,addr2,addr3;
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[2];
        addr3=it->results[3];
        printf("\n1:%u|%u 2:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf("\n\n");

    it=sc_iterator5_a_a_f_a_f_new(0,0,end_node,0,attr1);
    while(sc_iterator5_next(it)){
        addr1=it->results[0];
        addr2=it->results[1];
        addr3=it->results[3];
        printf("\n0:%u|%u 1:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf("\n\n");

    it=sc_iterator5_f_a_f_a_f_new(node,0,end_node,0,attr1);
    while(sc_iterator5_next(it)){
        addr2=it->results[1];
        addr3=it->results[3];
        printf("\n1:%u|%u 3:%u|%u",addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf("\n\n");

    it=sc_iterator5_f_a_f_a_a_new(node,0,end_node,0,0);
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[3];
        addr3=it->results[4];
        printf("\n1:%u|%u 3:%u|%u 4:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf("\n\n");

    it=sc_iterator5_a_a_f_a_a_new(0,0,end_node,0,0);
    while(sc_iterator5_next(it)){
        addr1=it->results[1];
        addr2=it->results[3];
        addr3=it->results[4];
        printf("\n1:%u|%u 3:%u|%u 4:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void gen_temp_identification(){
    sc_char* sys_idtf="nrel_system_identifier";
    sc_stream *stream = sc_stream_memory_new(sys_idtf, sizeof(sc_char)*strlen(sys_idtf), SC_STREAM_READ, SC_FALSE);
    sc_addr node1=sc_memory_node_new(sc_type_const|sc_type_node_norole);
    sc_addr node2=sc_memory_link_new();
    sc_memory_set_link_content(node2,stream);
    sc_stream_free(stream);
    sc_addr arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node1,node2);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,node1,arc_addr);
}

void gen_temp_identification_quasy(){
    gen_element_with_id("class_quasybinary_relation",0);
}

void create_temp_question1()
{
    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,CLASS_QUESTION_FULL_SEMANTIC_NEIGHBOURHOOD,quest);
    sc_addr node=gen_input_output_arcs();
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,CLASS_QUESTION_INITIATED,quest);
}

sc_addr gen_temporary_sys_search_pattern(){
    sc_addr pattern=sc_memory_node_new(sc_type_const|sc_type_node);
    sc_addr start_node=sc_memory_node_new(sc_type_const|sc_type_node_class);
    set_element_system_id(start_node,"triangle");
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,start_node);

    sc_addr* var_nodes=calloc(6,sizeof(sc_addr));
    int i=0;
    for (i=0;i<6;i++){
        var_nodes[i]=sc_memory_node_new(sc_type_node|sc_type_var);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,var_nodes[i]);
    }
    sc_addr arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,var_nodes[0]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start_node,var_nodes[1]);
    //print_element(var_nodes[1]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[0],var_nodes[2]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[0],var_nodes[3]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[1],var_nodes[4]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
    arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,var_nodes[1],var_nodes[5]);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);

    return pattern;
}

void gen_temporary_sys_search_const_data(){
    sc_addr start_node=find_element_by_id("triangle");

    sc_addr* const_nodes=calloc(6,sizeof(sc_addr));
    int i=0;
    for (i=0;i<6;i++){
        const_nodes[i]=sc_memory_node_new(sc_type_node|sc_type_const);
    }
    sc_addr arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[0]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,start_node,const_nodes[1]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[0],const_nodes[2]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[0],const_nodes[3]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[1],const_nodes[4]);
    arc=sc_memory_arc_new(sc_type_arc_pos_const_perm,const_nodes[1],const_nodes[5]);
}

int main(int argc, char *argv[])
{
    sc_memory_initialize("repo");

    gen_temp_identification();
    init_identification();
    gen_temp_identification_quasy();
    init_questions();

    /*sc_event *event1 = sc_event_new(CLASS_QUESTION_INITIATED, SC_EVENT_ADD_OUTPUT_ARC, 0, &operation_search_all_const_pos_output_arc, 0);
    sc_event *event2 = sc_event_new(CLASS_QUESTION_INITIATED, SC_EVENT_ADD_OUTPUT_ARC, 0, &operation_search_all_const_pos_input_arc, 0);
    sc_event *event3 = sc_event_new(CLASS_QUESTION_INITIATED, SC_EVENT_ADD_OUTPUT_ARC, 0, &operation_search_full_semantic_neighbourhood, 0);
    create_temp_question1();
    sc_event_destroy(event1);
    sc_event_destroy(event2);
    sc_event_destroy(event3);*/

    sc_addr node=gen_temporary_sys_search_pattern();
    print_element(node);

    gen_temporary_sys_search_const_data();

    system_sys_search(node);

    //sc_memory_shutdown();
    getch();

    return 0;
}
