extern "C"
{
#include "sc_iterator3.h"
#include "sc_kpm_additional.h"
}
#include "sc_system_gen.h"
#include <stdio.h>
#include <iostream>


sc_addr gen_correspondence_for_var(sc_addr var_elem,sc_type_result *params,sc_type_result *result){
    sc_type_result::iterator pos=params->find(var_elem);
    if(pos != params->end()){
        return (*pos).second;
    }
    sc_type var_type;
    sc_memory_get_element_type(var_elem,&var_type);
    sc_type const_type=((~sc_type_var & var_type)|sc_type_const);
    sc_addr const_elem;
    if ((sc_type_node & var_type) == sc_type_node)
    {
        const_elem=sc_memory_node_new(const_type);
    }
    else
    {
        sc_addr var_begin,var_end;
        sc_memory_get_arc_begin(var_elem,&var_begin);
        sc_memory_get_arc_end(var_elem,&var_end);
        sc_addr const_begin=gen_correspondence_for_var(var_begin,params,result);
        sc_addr const_end=gen_correspondence_for_var(var_end,params,result);
        const_elem=sc_memory_arc_new(const_type,const_begin,const_end);
    }
    params->insert(sc_addr_pair(var_elem,const_elem));
    result->insert(sc_addr_pair(var_elem,const_elem));
    return const_elem;
}

sc_result system_sys_gen(sc_addr pattern, sc_type_result params, sc_type_result *result){
    sc_type_result all_pairs;
    all_pairs.insert(params.begin(),params.end());
    sc_iterator3 *it=sc_iterator3_f_a_a_new(pattern,0,sc_type_node|sc_type_const);
    while(sc_iterator3_next(it)){
        sc_addr node=sc_iterator3_value(it,2);
        all_pairs.insert(sc_addr_pair(node,node));
    }
    sc_iterator3_free(it);

    it=sc_iterator3_f_a_a_new(pattern,0,sc_type_var);
    while(sc_iterator3_next(it)){
        sc_addr node=sc_iterator3_value(it,2);
        gen_correspondence_for_var(node,&all_pairs,result);
    }
    sc_iterator3_free(it);

    //print_result(*result);

    return SC_RESULT_OK;
}

sc_result system_sys_gen_for_variables(sc_addr pattern, sc_type_result params, sc_addr_vector requested_values, sc_type_result *result){
    sc_type_result all_pairs;
    all_pairs.insert(params.begin(),params.end());
    sc_iterator3 *it=sc_iterator3_f_a_a_new(pattern,0,sc_type_node|sc_type_const);
    while(sc_iterator3_next(it)){
        sc_addr node=sc_iterator3_value(it,2);
        all_pairs.insert(sc_addr_pair(node,node));
    }
    sc_iterator3_free(it);

    it=sc_iterator3_f_a_a_new(pattern,0,sc_type_var);
    while(sc_iterator3_next(it)){
        sc_addr node=sc_iterator3_value(it,2);
        gen_correspondence_for_var(node,&all_pairs,result);
    }
    sc_iterator3_free(it);

    filter_result_by_variables(result,&requested_values);

    //print_result(*result);

    return SC_RESULT_OK;
}
