extern "C"
{
#include "system.h"
#include "system_pattern.h"
#include "identification.h"
}
#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>

//if ((sc_type_var & ~pattern_arc_type)|sc_type_const){continue;}

using namespace std;

struct sc_addr_comparator
{
  bool operator()(const sc_addr s1, const sc_addr s2) const
  {
    return SC_ADDR_LOCAL_TO_INT(s1) < SC_ADDR_LOCAL_TO_INT(s2);
  }
};

typedef map<sc_addr,sc_addr,sc_addr_comparator> sc_type_result;
typedef map<int,sc_addr> sc_type_hash;

void print_hash(sc_type_hash table){
    sc_type_hash::iterator it;
    printf("HASHMAP:\n");
    for ( it=table.begin() ; it != table.end(); it++ ){
        sc_addr addr=(*it).second;
        cout << addr.seg << "|" << addr.offset << endl;
    }
}

void print_result(sc_type_result table){
    sc_type_result::iterator it;
    printf("RESULT:\n");
    for ( it=table.begin() ; it != table.end(); it++ ){
        sc_addr addr1=(*it).first;
        sc_addr addr2=(*it).second;
        cout << addr1.seg << "|" << addr1.offset << "=>" << addr2.seg << "|" << addr2.offset <<endl;
    }
}

void print_result_set(vector<sc_type_result> table){
    printf("RESULT COUNT:%d\n",table.size());
    for (sc_uint i=0; i<table.size();i++){
        print_result(table[i]);
    }
}

sc_bool copy_set_into_hash(sc_addr set,sc_type arc_type, sc_type end_type, sc_type_hash* table){
    sc_addr addr3;
    sc_iterator3 *it=sc_iterator3_f_a_a_new(set,arc_type,end_type);
    if (it==0){
        return SC_FALSE;
    }
    while (sc_iterator3_next(it))
    {
        addr3=sc_iterator3_value(it, 2);
        table->insert(pair<int,sc_addr>(SC_ADDR_LOCAL_TO_INT(addr3),addr3));
    }
    sc_iterator3_free(it);
    return SC_TRUE;
}


sc_bool system_sys_search_recurse(sc_addr sc_pattern, sc_type_hash pattern, sc_addr curr_const_element, sc_addr curr_pattern_element, sc_type_result *inp_result, vector<sc_type_result> *out_common_result)
{
    // sc_addr* addr2;
    sc_addr addr1,addr2;
    int out_arc_count=0;

    vector<sc_type_result> common_result;
    sc_type_result inp_result_copy=*inp_result;
    common_result.push_back(*inp_result);

    //Pattern arcs list
    vector<sc_addr> pattern_arc_set;

    sc_iterator3* it_pattern_arc=sc_iterator3_f_a_a_new(curr_pattern_element,0,0);
    if (it_pattern_arc==NULLPTR){return SC_FALSE;}
    while(sc_iterator3_next(it_pattern_arc)){
        addr2=sc_iterator3_value(it_pattern_arc, 1);
        if (pattern.find(SC_ADDR_LOCAL_TO_INT(addr2))!=pattern.end()){
            out_arc_count++;
            pattern_arc_set.push_back(addr2);
        }
    }
    sc_iterator3_free(it_pattern_arc);

    it_pattern_arc=sc_iterator3_a_a_f_new(0,0,curr_pattern_element);
    if (it_pattern_arc==NULLPTR){return SC_FALSE;}
    while(sc_iterator3_next(it_pattern_arc)){
        addr1=sc_iterator3_value(it_pattern_arc, 0);
        if (SC_ADDR_IS_EQUAL(addr1,sc_pattern)) continue;
        addr2=sc_iterator3_value(it_pattern_arc, 1);
        if (pattern.find(SC_ADDR_LOCAL_TO_INT(addr2))!=pattern.end()){
            pattern_arc_set.push_back(addr2);
        }
    }
    sc_iterator3_free(it_pattern_arc);

    //Pattern arcs loop
    for (sc_uint i=0;i<pattern_arc_set.size();i++){
        sc_addr pattern_arc=pattern_arc_set[i];
        sc_addr next_pattern_element;
        sc_addr next_const_element;

        if (out_arc_count>0){
            if (SC_OK!=sc_memory_get_arc_end(pattern_arc,&next_pattern_element)){continue;}
            printf("ARC IS OUT\nELEMENT: %u|%u\n",next_pattern_element.seg,next_pattern_element.offset);
            out_arc_count--;
        }else{
            if (SC_OK!=sc_memory_get_arc_begin(pattern_arc,&next_pattern_element)){continue;}
            printf("ARC IS OUT\nELEMENT: %u|%u\n",next_pattern_element.seg,next_pattern_element.offset);
        }

        if (pattern.find(SC_ADDR_LOCAL_TO_INT(next_pattern_element))==pattern.end()){continue;}

        //!check pattern_arc type
        sc_type pattern_arc_type;
        if (sc_memory_get_element_type(pattern_arc,&pattern_arc_type)!=SC_OK){continue;}
        if ((sc_type_const & pattern_arc_type) == sc_type_const){continue;}

        if (inp_result_copy.find(pattern_arc)!=inp_result_copy.end()){continue;}

        //!check next_pattern_element type
        sc_type next_pattern_element_type;
        sc_bool pattern_is_const_or_has_value=SC_FALSE;
        if (sc_memory_get_element_type(next_pattern_element,&next_pattern_element_type)!=SC_OK){continue;}
        if ((sc_type_const & next_pattern_element_type) == sc_type_const){
            next_const_element=next_pattern_element;
            pattern_is_const_or_has_value=SC_TRUE;
        }else{
            sc_type_result::iterator it=inp_result_copy.find(pattern_arc);
            if (it!=inp_result_copy.end()){
                next_const_element=(*it).first;
            }
        }

        pattern.erase(SC_ADDR_LOCAL_TO_INT(next_pattern_element));

    }

    return SC_TRUE;
}

void system_sys_search(sc_addr pattern){
    sc_addr start_node=find_element_by_id((sc_char*)"triangle");
    vector<sc_type_result> result_set;
    sc_type_result result;
    sc_type_hash pattern_hash;
    copy_set_into_hash(pattern,sc_type_arc_pos_const_perm,0,&pattern_hash);
    print_element(start_node);
    system_sys_search_recurse(pattern,pattern_hash,start_node,start_node,&result,&result_set);

    //!TODO Clear containers
}
