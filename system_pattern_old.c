#include "system.h"
#include "system_pattern_old.h"
#include "identification.h"
#include <malloc.h>
#include <stdio.h>

void print_pair(gpointer key, gpointer value, gpointer user_data){
    sc_addr _key=*((sc_addr*)key);
    sc_addr _value=*((sc_addr*)value);
    printf("Pair: <%u|%u ; %u|%u> \n",_key.seg,_key.offset,_value.seg,_value.offset);
}

void copy_pair(gpointer key, gpointer value, gpointer user_data){
    //sc_addr _key=*((sc_addr*)key);
    //sc_addr _value=*((sc_addr*)value);
    GHashTable* table=(GHashTable*)user_data;
    g_hash_table_insert(table,key,value);
}

void print_result(gpointer result, gpointer user_data){
    int num=(*((int*)user_data))++;
    printf("Result[%d]:\n",num);
    g_hash_table_foreach(result,print_pair,&num);
}

void free_sc_addr(gpointer data){
    free(data);
}

void print_single_result(GHashTable* result){
    printf("Result:\n");
    g_hash_table_foreach(result,print_pair,0);
}

void print_result_set(GList* result){
    printf("Total result count: %d\n",g_list_length(result));
    int i=0;
    g_list_foreach(result,print_result,&i);
}

guint sc_hash_table_hash_func(gconstpointer pointer)
{
    const sc_addr *addr = (const sc_addr*)pointer;
    return SC_ADDR_LOCAL_TO_INT(*addr);
}

gboolean sc_hash_table_equal_func(gconstpointer a, gconstpointer b)
{
    const sc_addr *addr1 = (const sc_addr*)a;
    const sc_addr *addr2 = (const sc_addr*)b;
    return SC_ADDR_IS_EQUAL(*addr1, *addr2);
}

GHashTable* copy_hash_table(GHashTable* table){
    GHashTable* new_table=g_hash_table_new(sc_hash_table_hash_func,sc_hash_table_equal_func);
    g_hash_table_foreach(table,copy_pair,new_table);
    return new_table;
}

gboolean g_hash_table_contains(GHashTable* table, gpointer key){
    if (g_hash_table_lookup(table,key)==NULL) {return 0;}
    else {return 1;}
}

sc_bool copy_set_into_hash(sc_addr set,sc_type arc_type, sc_type end_type, GHashTable* table){
    sc_addr* addr3;
    sc_iterator3 *it=sc_iterator3_f_a_a_new(set,arc_type,end_type);
    if (it==0){
        return SC_FALSE;
    }
    while (sc_iterator3_next(it))
    {
        addr3=calloc(1,sizeof(sc_addr));
        *addr3=sc_iterator3_value(it, 2);
        g_hash_table_insert(table,(gpointer)addr3,(gpointer)addr3);
    }
    sc_iterator3_free(it);
    return SC_TRUE;
}

sc_bool system_sys_search_recurse(sc_addr sc_pattern, GHashTable* pattern, sc_addr curr_const_element, sc_addr curr_pattern_element, GHashTable* inp_result, GList** out_common_result)
{
    sc_addr* addr2;
    sc_addr addr1;
    int out_arc_count=0;

    GList* common_result=NULLPTR;
    GHashTable* inp_result_copy=copy_hash_table(inp_result);
    common_result=g_list_append(common_result,inp_result);

    //Pattern arcs list
    GList* pattern_arc_set=NULLPTR;

    sc_iterator3* it_pattern_arc=sc_iterator3_f_a_a_new(curr_pattern_element,sc_type_var,0);
    if (it_pattern_arc==NULLPTR){return SC_FALSE;}
    while(sc_iterator3_next(it_pattern_arc)){
        addr2=calloc(1,sizeof(sc_addr));
        *addr2=sc_iterator3_value(it_pattern_arc, 1);
        if (g_hash_table_contains(pattern,addr2)){
            out_arc_count++;
            pattern_arc_set=g_list_append(pattern_arc_set,addr2);
        }
    }
    sc_iterator3_free(it_pattern_arc);

    it_pattern_arc=sc_iterator3_a_a_f_new(0,sc_type_var,curr_pattern_element);
    if (it_pattern_arc==NULLPTR){return SC_FALSE;}
    while(sc_iterator3_next(it_pattern_arc)){
        addr1=sc_iterator3_value(it_pattern_arc, 0);
        if (SC_ADDR_IS_EQUAL(addr1,sc_pattern)) continue;
        addr2=calloc(1,sizeof(sc_addr));
        *addr2=sc_iterator3_value(it_pattern_arc, 1);
        if (g_hash_table_contains(pattern,addr2)){
            pattern_arc_set=g_list_append(pattern_arc_set,addr2);
        }
    }
    sc_iterator3_free(it_pattern_arc);

    //Pattern arcs loop
    while(1){
        GList* first_elem=g_list_first(pattern_arc_set);
        if (first_elem==NULLPTR){break;}
        sc_addr* pattern_arc=first_elem->data;
        sc_addr next_pattern_element;

        sc_addr temp;
        temp.offset=41;
        temp.seg=0;
        print_element(temp);

        printf("ARC: %u|%u\n",pattern_arc->seg,pattern_arc->offset);
        sc_type type;
        sc_memory_get_element_type(*pattern_arc,&type);
        printf("TYPE: %x\n",type);
        if (out_arc_count>0){
            if (SC_TRUE!=sc_memory_get_arc_end(*pattern_arc,next_pattern_element)){continue;}
            printf("ARC IS OUT\nELEMENT: %u|%u\n",next_pattern_element->seg,next_pattern_element->offset);
            out_arc_count--;
        }else{
            if (SC_TRUE!=sc_memory_get_arc_begin(*pattern_arc,next_pattern_element)){continue;}
            printf("ARC IS OUT\nELEMENT: %u|%u\n",next_pattern_element->seg,next_pattern_element->offset);
        }

        free(pattern_arc);
        pattern_arc_set=g_list_delete_link(pattern_arc_set,first_elem);
    }

    //!TODO free memory allocated for all structures
    free(inp_result_copy);
    return SC_TRUE;
}

void system_sys_search(sc_addr pattern){
    sc_addr start_node=find_element_by_id("triangle");
    GList* result_set=NULLPTR;
    //!TODO add full creation function
    GHashTable* result=g_hash_table_new(sc_hash_table_hash_func,sc_hash_table_equal_func);
    GHashTable* pattern_hash=g_hash_table_new_full(sc_hash_table_hash_func,sc_hash_table_equal_func,free_sc_addr,free_sc_addr);
    copy_set_into_hash(pattern,sc_type_arc_pos_const_perm,0,pattern_hash);

    system_sys_search_recurse(pattern,pattern_hash,start_node,start_node,result,&result_set);
    //printf("BOOL: %d\n",g_hash_table_contains(pattern_hash,(gpointer)&start_node));

    //print_result_set(result_set);
    //!TODO free memory allocated for all structures
    g_hash_table_remove_all(pattern_hash);
    free(pattern_hash);
}
