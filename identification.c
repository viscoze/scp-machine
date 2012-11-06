#include "identification.h"
#include <stdio.h>

sc_bool init_identification(){
    sc_stream *stream = 0;
    sc_addr *results = 0;
    sc_uint32 results_count = 0;
    char* sys_idtf="nrel_system_identifier";

    stream = sc_stream_memory_new(sys_idtf, sizeof(sys_idtf), SC_STREAM_READ, SC_FALSE);

    /*if (sc_storage_find_links_with_content(stream, &results, &results_count) == SC_OK)
    {
        for (j = 0; j < results_count; j++)
        {

        }
        free(results);
        results = NULLPTR;
    }else
        return SC_FALSE;*/

    sc_stream_free(stream);

    return SC_TRUE;
}
