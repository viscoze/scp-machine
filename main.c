#include <stdio.h>
#include <conio.h>
#include "sc_memory.h"
#include "sc_iterator.h"
#include "sc_iterator5.h"
#include "sc_stream_memory.h"

#include "search.h"
#include "system.h"

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
    while(sc_iterator5_a_a_f_a_f_next(it)){
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
    while(sc_iterator5_f_a_a_a_f_next(it)){
        addr1=it->results[1];
        addr2=it->results[2];
        addr3=it->results[3];
        printf("\n1:%u|%u 2:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}

void test_iterator5_arcs_only(){
    sc_addr attr1=sc_memory_node_new(sc_type_node);
    sc_addr node=sc_memory_node_new(sc_type_node);
    sc_addr end_node=sc_memory_node_new(sc_type_node);
    sc_addr arc_addr;

    int i=0;
    while(i<10){
        arc_addr=sc_memory_arc_new(sc_type_arc_pos_const_perm,node,end_node);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,attr1,arc_addr);
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
    while(sc_iterator5_f_a_a_a_f_next(it)){
        addr1=it->results[1];
        addr2=it->results[2];
        addr3=it->results[3];
        printf("\n1:%u|%u 2:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf("\n\n");

    it=sc_iterator5_a_a_f_a_f_new(0,0,end_node,0,attr1);
    while(sc_iterator5_a_a_f_a_f_next(it)){
        addr1=it->results[0];
        addr2=it->results[1];
        addr3=it->results[3];
        printf("\n0:%u|%u 1:%u|%u 3:%u|%u",addr1.seg,addr1.offset,addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);

    printf("\n\n");

    it=sc_iterator5_f_a_f_a_f_new(node,0,end_node,0,attr1);
    while(sc_iterator5_f_a_f_a_f_next(it)){
        addr2=it->results[1];
        addr3=it->results[3];
        printf("\n1:%u|%u 3:%u|%u",addr2.seg,addr2.offset,addr3.seg,addr3.offset);
    }
    sc_iterator5_free(it);
}


int main(int argc, char *argv[])
{
    sc_memory_initialize("repo");

    test_iterator5_arcs_only();

    //sc_memory_shutdown();
    getch();

    return 0;
}
