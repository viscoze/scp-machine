#include "identification.h"
#include "sc_iterator5.h"
#include "sc_stream.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

sc_bool init_identification(){
    sc_addr *results = 0;
    sc_uint32 results_count = 0;
    sc_char* sys_idtf="nrel_system_identifier";
    sc_stream *stream = sc_stream_memory_new(sys_idtf, sizeof(sc_char)*strlen(sys_idtf), SC_STREAM_READ, SC_FALSE);

    if (sc_memory_find_links_with_content(stream, &results, &results_count) == SC_OK)
    {
        int i=0;
        for (i = 0; i < results_count; i++)
        {
            sc_iterator5 *it=sc_iterator5_a_a_f_a_a_new(sc_type_const|sc_type_node_norole,sc_type_arc_pos_const_perm,results[i],sc_type_arc_pos_const_perm,sc_type_const|sc_type_node_norole);
            while(sc_iterator5_a_a_f_a_a_next(it)){

                if (SC_ADDR_IS_EQUAL(it->results[0],it->results[4])){
                    NREL_SYSTEM_IDENTIFIER=it->results[0];
                    free(results);
                    sc_stream_free(stream);
                    return SC_TRUE;
                }
            }
        }
        free(results);
        results = NULLPTR;
    }else
        return SC_FALSE;

    sc_stream_free(stream);

    return SC_FALSE;
}

sc_addr find_element_by_id(sc_char* id){
    sc_addr *results = 0;
    sc_uint32 results_count = 0;
    sc_addr result;
    SC_ADDR_MAKE_EMPTY(result)
    sc_stream *stream = sc_stream_memory_new(id, sizeof(sc_char)*strlen(id), SC_STREAM_READ, SC_FALSE);

    if (sc_memory_find_links_with_content(stream, &results, &results_count) == SC_OK)
    {
        int i=0;
        for (i = 0; i < results_count; i++)
        {
            sc_iterator5 *it=sc_iterator5_a_a_f_a_f_new(0,sc_type_arc_pos_const_perm,results[i],sc_type_arc_pos_const_perm,NREL_SYSTEM_IDENTIFIER);
            if(sc_iterator5_a_a_f_a_f_next(it)){
                free(results);
                results = NULLPTR;
                sc_stream_free(stream);
                return it->results[0];
            }
        }
        free(results);
        results = NULLPTR;
    }else
        return result;

    sc_stream_free(stream);

    return result;
}
