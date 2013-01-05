extern "C"
{
#include "system.h"
#include "system_pattern.h"
#include "identification.h"
}
#include <stdio.h>
#include <malloc.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

//if ((sc_type_var & ~pattern_arc_type)|sc_type_const){continue;}

using namespace std;

int class_count=0;

struct sc_addr_comparator
{
    bool operator()(const sc_addr s1, const sc_addr s2) const
    {
        return (SC_ADDR_LOCAL_TO_INT(s1) < SC_ADDR_LOCAL_TO_INT(s2));
    }
};

typedef map<sc_addr,sc_addr,sc_addr_comparator> sc_type_result;
//typedef map<sc_addr,sc_addr> sc_type_result;
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
    printf("RESULT (%d):\n",table.size());
    for ( it=table.begin() ; it != table.end(); it++ ){
        sc_addr addr1=(*it).first;
        sc_addr addr2=(*it).second;
        cout << addr1.seg << "|" << addr1.offset << "=>" << addr2.seg << "|" << addr2.offset <<endl;
    }
}

void print_result_set(vector<sc_type_result*> table){
    printf("RESULT COUNT:%d\n",table.size());
    for (sc_uint i=0; i<table.size();i++){
        print_result(*(table[i]));
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

sc_bool find_result_pair_for_var(sc_type_result *set,sc_addr var_element,sc_addr* result){
    sc_type_result::iterator it=set->find(var_element);
    if (it==set->end()){
        return SC_FALSE;
    }else{
        *result=(*it).second;
        return SC_TRUE;
    }
}

/*sc_bool find_result_pair_for_var(sc_type_result *set,sc_addr var_element,sc_addr* result){
    sc_type_result::iterator it;
    for ( it=set->begin() ; it != set->end(); it++ ){
        sc_addr var=(*it).first;
        sc_addr cnst=(*it).second;
        if (SC_ADDR_IS_EQUAL(var,var_element)){
            *result=cnst;
            return SC_TRUE;
        }
    }
    return SC_FALSE;
}*/

sc_bool find_result_pair_for_const(sc_type_result *set,sc_addr const_element,sc_addr* result){
    sc_type_result::iterator it;
    for ( it=set->begin() ; it != set->end(); it++ ){
        sc_addr var=(*it).first;
        sc_addr cnst=(*it).second;
        if (SC_ADDR_IS_EQUAL(cnst,const_element)){
            *result=var;
            return SC_TRUE;
        }
    }
    return SC_FALSE;
}

void cantorize_result_vector(vector<sc_type_result*> *result){
    set<sc_type_result*> myset(result->begin(),result->end());
    result->clear();
    result->insert(result->begin(),myset.begin(),myset.end());
}

void remove_all_elements(vector<sc_type_result*> *pattern,vector<sc_type_result*> *source){
    for (sc_uint i=0;i<pattern->size();i++){
        source->erase(std::remove(source->begin(), source->end(), (*pattern)[i]), source->end());
    }
}


void free_single_result(sc_type_result* result){
        delete result;
        class_count--;
}

void free_result_vector(vector<sc_type_result*> *result){
    for (sc_uint i=0;i<result->size();i++){
        free_single_result((*result)[i]);
    }
    result->clear();
}

sc_bool system_sys_search_recurse(sc_addr sc_pattern, sc_type_hash pattern, sc_addr curr_const_element, sc_addr curr_pattern_element, sc_type_result *inp_result, vector<sc_type_result*> *out_common_result)
{
    sc_addr addr1,addr2,temp;
    int out_arc_count=0;

    vector<sc_type_result*> common_result;
    vector<sc_type_result*> del_result;
    sc_type_result inp_result_copy=*inp_result;
    common_result.push_back(inp_result);

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
        sc_bool out_arc_flag=SC_TRUE;
        vector<sc_type_result*> new_common_result;

        vector<sc_type_result*> next_common_result;
        vector<sc_type_result*> next_common_result_arc;
        vector<sc_type_result*> next_common_result1;

        if (out_arc_count>0){
            if (SC_OK!=sc_memory_get_arc_end(pattern_arc,&next_pattern_element)){continue;}
            //printf("ARC IS OUT\nELEMENT: %u|%u\n",next_pattern_element.seg,next_pattern_element.offset);
            out_arc_count--;
        }else{
            if (SC_OK!=sc_memory_get_arc_begin(pattern_arc,&next_pattern_element)){continue;}
            //printf("ARC IS IN\nELEMENT: %u|%u\n",next_pattern_element.seg,next_pattern_element.offset);
            out_arc_flag=SC_FALSE;
        }

        if (pattern.find(SC_ADDR_LOCAL_TO_INT(next_pattern_element))==pattern.end()){continue;}

        //!check pattern_arc type
        sc_type pattern_arc_type;
        if (sc_memory_get_element_type(pattern_arc,&pattern_arc_type)!=SC_OK){continue;}
        if ((sc_type_const & pattern_arc_type) == sc_type_const){continue;}

        if (inp_result_copy.find(pattern_arc)!=inp_result_copy.end()){continue;}
        //if (SC_TRUE==find_result_pair_for_var(&inp_result_copy,pattern_arc,&temp)){continue;}

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
            /*if (find_result_pair_for_var(&inp_result_copy,pattern_arc,&temp)==SC_TRUE){
                next_const_element=temp;
            }*/
        }

        pattern.erase(SC_ADDR_LOCAL_TO_INT(next_pattern_element));

        //!const arc loop
        sc_iterator3* it_const_arc;
        vector<sc_addr> const_arc_set;

        //!TODO CHECK ARC TYPE
        sc_type const_arc_type=((~sc_type_var & pattern_arc_type)|sc_type_const);
        //cout<<"TYPE:"<<const_arc_type<<endl;
        if (out_arc_flag==SC_TRUE){
            it_const_arc=sc_iterator3_f_a_a_new(curr_const_element,const_arc_type,0);
        }else{
            it_const_arc=sc_iterator3_a_a_f_new(0,const_arc_type,curr_const_element);
        }
        while(sc_iterator3_next(it_const_arc)){
            if (out_arc_flag==SC_FALSE){
                addr1=sc_iterator3_value(it_pattern_arc, 0);
                if (SC_ADDR_IS_EQUAL(addr1,sc_pattern)) continue;
            }
            addr2=sc_iterator3_value(it_const_arc, 1);
            const_arc_set.push_back(addr2);
        }
        sc_iterator3_free(it_const_arc);

        //printf("ELEMENT %u|%u CONST ARCS COUNT:%d\n",curr_const_element.seg,curr_const_element.offset,const_arc_set.size());

        for (sc_uint j=0;j<const_arc_set.size();j++){
            sc_addr const_arc=const_arc_set[j];
            sc_addr next_const_element;

            if (out_arc_flag==SC_TRUE){
                if (SC_OK!=sc_memory_get_arc_end(const_arc,&next_const_element)){continue;}
            }else{
                if (SC_OK!=sc_memory_get_arc_begin(const_arc,&next_const_element)){continue;}
            }

            //printf("CONST ELEM: %u|%u\n",next_const_element.seg,next_const_element.offset);

            //!Results loop
            for (sc_uint k=0;k<common_result.size();k++){
                sc_type_result* result=common_result[k];

                if (SC_TRUE==find_result_pair_for_const(result,const_arc,&temp)){continue;}

                if (SC_TRUE==find_result_pair_for_var(result,pattern_arc,&temp)){
                    //!Gen new result
                    sc_type_result *new_result=new sc_type_result();
                    class_count++;
                    (*new_result)=(*result);
                    new_common_result.push_back(new_result);
                    result=new_result;
                    result->erase(pattern_arc);
                    if (pattern_is_const_or_has_value==SC_FALSE){
                        result->erase(next_pattern_element);
                    }
                }

                //!Genering pair for 2rd element
                result->insert(pair<sc_addr,sc_addr>(pattern_arc,const_arc));
                pattern.erase(SC_ADDR_LOCAL_TO_INT(pattern_arc));

                //!Genering pair for 3rd element
                if (pattern_is_const_or_has_value==SC_FALSE
                    && SC_FALSE==find_result_pair_for_var(result,next_pattern_element,&temp)){
                    result->insert(pair<sc_addr,sc_addr>(next_pattern_element,next_const_element));
                    pattern.erase(SC_ADDR_LOCAL_TO_INT(next_pattern_element));
                }

                sc_type_result *recurse_result=new sc_type_result();
                class_count++;
                (*recurse_result)=(*result);
                del_result.push_back(result);

                system_sys_search_recurse(sc_pattern,pattern,const_arc,pattern_arc,
                                          recurse_result,&next_common_result_arc);

                for (sc_uint kk=0;kk<next_common_result_arc.size();kk++){
                    sc_type_result *element_result=next_common_result_arc[kk];
                    system_sys_search_recurse(sc_pattern,pattern,next_const_element,next_pattern_element,
                                              element_result,&next_common_result1);
                    if (!next_common_result1.empty()){
                        next_common_result.insert(next_common_result.end(),
                                                  next_common_result1.begin(),next_common_result1.end());
                        next_common_result1.clear();
                    }else{
                        next_common_result.push_back(element_result);
                    }
                }

                pattern.insert(pair<int,sc_addr>(SC_ADDR_LOCAL_TO_INT(pattern_arc),pattern_arc));
                pattern.insert(pair<int,sc_addr>(SC_ADDR_LOCAL_TO_INT(next_pattern_element),next_pattern_element));

                out_common_result->insert(out_common_result->end(),next_common_result.begin(),next_common_result.end());
                new_common_result.insert(new_common_result.end(),next_common_result.begin(),next_common_result.end());
                cantorize_result_vector(&new_common_result);
                next_common_result.clear();
                next_common_result_arc.clear();
            }
        }//const loop

        common_result.insert(common_result.begin(),new_common_result.begin(),new_common_result.end());

        //remove_all_elements(&del_result,&new_common_result);
        new_common_result.clear();
        remove_all_elements(&del_result,&common_result);
        remove_all_elements(&del_result,out_common_result);
        free_result_vector(&del_result);
    }//pattern loop

    out_common_result->insert(out_common_result->end(),common_result.begin(),common_result.end());
    common_result.clear();
    cantorize_result_vector(out_common_result);

    return SC_TRUE;
}

void system_sys_search(sc_addr pattern){
    sc_addr start_node=find_element_by_id((sc_char*)"triangle");
    vector<sc_type_result*> result_set;
    sc_type_result *result=new sc_type_result();
    class_count++;
    sc_type_hash pattern_hash;
    copy_set_into_hash(pattern,sc_type_arc_pos_const_perm,0,&pattern_hash);
    //print_element(start_node);
    system_sys_search_recurse(pattern,pattern_hash,start_node,start_node,result,&result_set);

    //print_result_set(result_set);

    /*sc_addr addr,addr1;
    addr.seg=0;
    addr.offset=41;
    sc_bool res=find_result_pair_for_const(result_set[0],addr,&addr1);

    printf("\nSEARCH: %d\n",res);
    if (res==SC_TRUE){
        printf("ELEMENT: %u|%u\n",addr1.seg,addr1.offset);
    }*/

    free_result_vector(&result_set);

    //printf("Memory balance: %d\n",class_count);
}
