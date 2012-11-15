#include "system.h"
#include <stdio.h>

sc_bool print_element(sc_addr element){

    sc_addr addr2,addr3;

    printf("\nPrint element: %u|%u =\n", element.seg, element.offset);

    sc_iterator3 *it=sc_iterator3_a_a_f_new(0,0,element);
    if (it==0){
        return SC_FALSE;
    }
    printf("Input arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);
        printf("\t%u|%u <- %u|%u;\n", addr3.seg, addr3.offset, addr2.seg, addr2.offset);
    }
    sc_iterator3_free(it);

    it=sc_iterator3_f_a_a_new(element,0,0);
    if (it==0){
        return SC_FALSE;
    }
    printf("Output arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);
        printf("\t%u|%u -> %u|%u;\n", addr2.seg, addr2.offset, addr3.seg, addr3.offset);
    }
    sc_iterator3_free(it);

    return SC_TRUE;
}


sc_bool get_question_single_param(sc_addr question_class,sc_addr question_node, sc_addr *param)
{
    sc_iterator3 *it=sc_iterator3_f_a_f_new(question_class,sc_type_arc_pos_const_perm,question_node);
    if (!sc_iterator3_next(it)){
        return SC_FALSE;
    }
    sc_iterator3_free(it);

    it=sc_iterator3_f_a_a_new(question_node,sc_type_arc_pos_const_perm,0);
    if (!sc_iterator3_next(it)){
        return SC_FALSE;
    }else{
        *param=it->results[2];
        return SC_TRUE;
    }
}
