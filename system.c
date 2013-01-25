#include "system.h"
#include "sc_helper.h"
#include "sc_stream.h"
#include <malloc.h>
#include <stdio.h>

sc_bool print_element(sc_addr element){

    sc_addr addr2,addr3;
    sc_addr idtf;

    if (SC_RESULT_OK==sc_helper_get_system_identifier(element,&idtf)){
        sc_stream *stream;
        sc_memory_get_link_content(idtf,&stream);
        sc_uint length=0,read_length=0;
        sc_stream_get_length(stream,&length);
        sc_char *data=calloc(length,sizeof(sc_char));
        sc_stream_read_data(stream,data,length,&read_length);
        printf("\nPrint element: %s =\n",data);
        sc_stream_free(stream);
        free(data);
    }else{
        printf("\nPrint element: %u|%u =\n", element.seg, element.offset);
    }

    sc_iterator3 *it=sc_iterator3_a_a_f_new(0,0,element);
    if (it==0){
        return SC_FALSE;
    }
    printf("Input arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);

        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr2,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("\t%s <- ",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("\t%u|%u <- ", addr2.seg, addr2.offset);
        }
        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr2,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("%s;\n",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("%u|%u;\n", addr3.seg, addr3.offset);
        }

        //printf("\t%u|%u <- %u|%u;\n", addr3.seg, addr3.offset, addr2.seg, addr2.offset);
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

        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr2,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("\t%s -> ",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("\t%u|%u -> ", addr2.seg, addr2.offset);
        }
        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr3,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("%s;\n",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("%u|%u;\n", addr3.seg, addr3.offset);
        }
        //printf("\t%u|%u -> %u|%u;\n", addr2.seg, addr2.offset, addr3.seg, addr3.offset);
    }
    sc_iterator3_free(it);

    return SC_TRUE;
}

sc_result search_question_answer(sc_addr question, sc_addr* answer){
    sc_addr nrel_answer;
    if (sc_helper_resolve_system_identifier("nrel_answer", &nrel_answer) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_iterator5 *it=sc_iterator5_f_a_a_a_f_new(question,0,0,0,nrel_answer);
    if (SC_TRUE==sc_iterator5_next(it)){
        *answer=sc_iterator5_value(it,2);
        sc_iterator5_free(it);
        return SC_RESULT_OK;
    }
    sc_iterator5_free(it);
    return SC_RESULT_ERROR;
}
