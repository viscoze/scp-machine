//#include <stdio.h>
#include <conio.h>
#include "sc_memory.h"
#include "sc_iterator.h"
#include "sc_stream_memory.h"

#include "search.h"
#include "system.h"

sc_addr gen_temp_data(){

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

int main(int argc, char *argv[])
{
    sc_memory_initialize("repo");

    sc_addr node=gen_temp_data();
    print_element(node);
    sc_addr answer=sc_memory_node_new(sc_type_node);
    /*search_all_const_pos_output_arc(node,answer);
    print_element(answer);
    sc_memory_element_free(answer);
    answer=sc_memory_node_new(sc_type_node);
    search_all_const_pos_input_arc(node,answer);
    print_element(answer);*/
    search_full_semantic_neighbourhood(node,answer);
    print_element(answer);

    //sc_memory_shutdown();
    getch();

    return 0;
}
