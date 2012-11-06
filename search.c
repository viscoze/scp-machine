#include "search.h"
#include <stdio.h>

sc_bool search_all_const_pos_output_arc(sc_addr node,sc_addr answer){

    sc_iterator3 *it=NULLPTR;

    it=sc_iterator3_f_a_a_new(node,sc_type_arc_pos_const_perm,0);

    if (it==NULLPTR){
        return SC_FALSE;
    }
    sc_addr addr2,addr3;

    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr2);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr3);
    }
    sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,node);

    sc_iterator3_free(it);
    return SC_TRUE;
}

sc_bool search_all_const_pos_input_arc(sc_addr node,sc_addr answer){

    sc_iterator3 *it=NULLPTR;

    it=sc_iterator3_a_a_f_new(sc_type_arc_pos_const_perm,0,node);

    if (it==NULLPTR){
        return SC_FALSE;
    }
    sc_addr addr2,addr3;

    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr2);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr3);
    }
    sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,node);

    sc_iterator3_free(it);
    return SC_TRUE;
}

sc_bool search_all_const_pos_output_arc_with_attr(sc_addr node,sc_addr answer){

    sc_iterator3 *it=NULLPTR;

    it=sc_iterator3_f_a_a_new(node,sc_type_arc_pos_const_perm,0);

    if (it==NULLPTR){
        return SC_FALSE;
    }
    sc_addr addr2,addr3;

    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);
        if (search_all_const_pos_input_arc(addr2,answer)==SC_FALSE){
            continue;
        }
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr3);
    }
    sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,node);

    sc_iterator3_free(it);
    return SC_TRUE;
}

sc_bool search_all_const_pos_input_arc_with_attr(sc_addr node,sc_addr answer){

    sc_iterator3 *it=NULLPTR;

    it=sc_iterator3_a_a_f_new(sc_type_arc_pos_const_perm,0,node);

    if (it==NULLPTR){
        return SC_FALSE;
    }
    sc_addr addr2,addr3;

    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr2);
        if (search_all_const_pos_input_arc(addr2,answer)==SC_FALSE){
            continue;
        }
    }
    sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,node);

    sc_iterator3_free(it);
    return SC_TRUE;
}

sc_bool search_full_semantic_neighbourhood(sc_addr node,sc_addr answer){

    sc_iterator3 *it=NULLPTR;
    sc_addr addr2,addr3;

    //Input arcs iterator
    it=sc_iterator3_a_a_f_new(0,0,node);
    if (it==NULLPTR){
        return SC_FALSE;
    }
    while (sc_iterator3_next(it))
    {
        addr3 = sc_iterator3_value(it, 0);
        addr2 = sc_iterator3_value(it, 1);
        if (SC_ADDR_IS_EQUAL(answer, addr2)){
            continue;
        }
        //printf("\n0:%u|%u 1:%u|%u",addr3.seg,addr3.offset,addr2.seg,addr2.offset);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr2);

        sc_iterator3 *it1=NULLPTR;

        //Attribute arcs iterator
        it1=sc_iterator3_a_a_f_new(0,sc_type_arc_pos_const_perm,addr2);
        if (it==NULLPTR){
            continue;
        }
        sc_addr _addr2,_addr3;
        char flag=0;
        while (sc_iterator3_next(it1))
        {
            _addr2 = sc_iterator3_value(it1, 0);
            _addr3 = sc_iterator3_value(it1, 1);
            if (SC_ADDR_IS_EQUAL(answer, _addr2)){
                continue;
            }
            //printf(" 3:%u|%u",_addr3.seg,_addr3.offset);
            sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,_addr2);
            sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,_addr3);

            /*sc_iterator3 *it2=NULLPTR;
                it2=sc_iterator3_f_a_f_new(***NODE***,sc_type_arc_pos_const_perm,_addr3);
                if (it2==NULLPTR){
                    continue;
                }
                if (sc_iterator3_next(it)){
                    flag=1;
                }*/
        }
        sc_iterator3_free(it1);

        if (SC_ADDR_IS_EQUAL(answer, addr3)){
            continue;
        }
        if (flag){
            search_all_const_pos_output_arc(addr3,answer);
        }else{
            sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr3);
        }
    }
    sc_iterator3_free(it);

    //Output arcs iterator
    it=sc_iterator3_f_a_a_new(node,0,0);
    if (it==NULLPTR){
        return SC_FALSE;
    }
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);

        printf("\n1:%u|%u 2:%u|%u",addr2.seg,addr2.offset,addr3.seg,addr3.offset);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr2);

        sc_iterator3 *it1=NULLPTR;

        //Attribute arcs iterator
        it1=sc_iterator3_a_a_f_new(0,sc_type_arc_pos_const_perm,addr2);
        if (it==NULLPTR){
            continue;
        }
        sc_addr _addr2,_addr3;
        int flag=0;
        while (sc_iterator3_next(it1))
        {
            _addr2 = sc_iterator3_value(it1, 0);
            _addr3 = sc_iterator3_value(it1, 1);
            if (SC_ADDR_IS_EQUAL(answer, _addr2)){
                continue;
            }
            printf(" 3:%u|%u",_addr3.seg,_addr3.offset);
            sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,_addr2);
            sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,_addr3);

            /*sc_iterator3 *it2=NULLPTR;
            it2=sc_iterator3_f_a_f_new(***NODE***,sc_type_arc_pos_const_perm,_addr3);
            if (it2==NULLPTR){
                continue;
            }
            if (sc_iterator3_next(it)){
                flag=1;
            }*/
        }
        sc_iterator3_free(it1);

        if (SC_ADDR_IS_EQUAL(answer, addr3)){
            continue;
        }

        if (flag){
            search_all_const_pos_output_arc(addr3,answer);
        }else{
            sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,addr3);
        }
    }
    sc_iterator3_free(it);

    sc_memory_arc_new(sc_type_arc_pos_const_perm,answer,node);

    return SC_TRUE;
}
