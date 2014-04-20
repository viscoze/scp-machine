
#include "scp_lib.h"
#include "sc_helper.h"
//#include "sc_memory_headers.h"

#include <stdio.h>

#include <glib.h>
#include <unistd.h>

sc_bool check_type(sc_addr element, sc_type input_type)
{
    sc_type type;
    if (SC_RESULT_OK != sc_memory_get_element_type(element, &type))
    {
        return SC_FALSE;
    }
    if ((input_type & type) == input_type)
    {
        return SC_TRUE;
    }
    else
    {
        return SC_FALSE;
    }
    return SC_FALSE;
}

sc_result printElem(sc_addr element)
{
    sc_addr addr2, addr3;
    sc_addr idtf;
    sc_iterator3 *it = nullptr;
    sc_uint32 out_c = 0, in_c = 0;
    if (SC_FALSE == sc_memory_is_element(element)){
        return SC_RESULT_ERROR;
    }
    if (SC_RESULT_OK == sc_helper_get_system_identifier(element, &idtf))
    {
        sc_stream *stream;
        sc_uint32 length = 0, read_length = 0;
        sc_char *data;
        sc_memory_get_link_content(idtf, &stream);
        sc_stream_get_length(stream, &length);
        data = calloc(length + 1, sizeof(sc_char));
        sc_stream_read_data(stream, data, length, &read_length);
        data[length] = '\0';
        printf("\nPrint element: %s =\n", data);
        sc_stream_free(stream);
        free(data);
    }
    else
    {
        printf("\nPrint element: %u|%u =\n", element.seg, element.offset);
    }

    it = sc_iterator3_a_a_f_new(0, 0, element);
    if (it == 0)
    {
        return SC_RESULT_ERROR;
    }
    printf("Input arcs:\n");
    while (SC_TRUE == sc_iterator3_next(it))
    {
        in_c++;
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);

        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr3, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            if (SC_TRUE == check_type(addr3, sc_type_arc_common))
            {
                printf("\t%s <= ", data);
            }
            else
            {
                printf("\t%s <- ", data);
            }
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            if (SC_TRUE == check_type(addr3, sc_type_arc_common))
            {
                printf("\t%u|%u <= ", addr3.seg, addr3.offset);
            }
            else
            {
                printf("\t%u|%u <- ", addr3.seg, addr3.offset);
            }
        }
        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr2, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            printf("%s;\n", data);
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            printf("%u|%u;\n", addr2.seg, addr2.offset);
        }
    }
    sc_iterator3_free(it);
    printf("Total input arcs: %d\n", in_c);

    it = sc_iterator3_f_a_a_new(element, 0, 0);
    if (it == 0)
    {
        return SC_RESULT_ERROR;
    }
    printf("Output arcs:\n");
    while (SC_TRUE == sc_iterator3_next(it))
    {
        out_c++;
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);

        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr2, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            if (SC_TRUE == check_type(addr2, sc_type_arc_access))
            {
                printf("\t%s -> ", data);
            }
            else
            {
                printf("\t%s => ", data);
            }
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            if (SC_TRUE == check_type(addr2, sc_type_arc_access))
            {
                printf("\t%u|%u -> ", addr2.seg, addr2.offset);
            }
            else
            {
                printf("\t%u|%u => ", addr2.seg, addr2.offset);
            }

        }
        if (SC_RESULT_OK == sc_helper_get_system_identifier(addr3, &idtf))
        {
            sc_stream *stream;
            sc_uint32 length = 0, read_length = 0;
            sc_char *data;
            sc_memory_get_link_content(idtf, &stream);
            sc_stream_get_length(stream, &length);
            data = calloc(length + 1, sizeof(sc_char));
            sc_stream_read_data(stream, data, length, &read_length);
            data[length] = '\0';
            printf("%s;\n", data);
            sc_stream_free(stream);
            free(data);
        }
        else
        {
            printf("%u|%u;\n", addr3.seg, addr3.offset);
        }
    }
    sc_iterator3_free(it);
    printf("Total output arcs: %d\n", out_c);
    return SC_RESULT_OK;
}

sc_result printIdtf(sc_addr element)
{
    sc_addr idtf;
    if (SC_FALSE == sc_memory_is_element(element)){
        return SC_RESULT_ERROR;
    }
    if (SC_RESULT_OK == sc_helper_get_system_identifier(element, &idtf))
    {
        sc_stream *stream;
        sc_uint32 length = 0, read_length = 0;
        sc_char *data;
        sc_memory_get_link_content(idtf, &stream);
        sc_stream_get_length(stream, &length);
        data = calloc(length + 1, sizeof(sc_char));
        sc_stream_read_data(stream, data, length, &read_length);
        data[length] = '\0';
        printf("\nPrint element: %s =\n", data);
        sc_stream_free(stream);
        free(data);
    }
    else
    {
        printf("\nPrint element: %u|%u =\n", element.seg, element.offset);
    }
    return SC_RESULT_OK;
}

void create_process_test()
{
    sc_addr quest, init, nrel_answer, active_sc_agent, agent;
    scp_operand op;

    sc_helper_resolve_system_identifier("quest1", &quest);
    sc_helper_resolve_system_identifier("question_initiated", &init);
    sc_helper_resolve_system_identifier("nrel_answer", &nrel_answer);

    sc_helper_resolve_system_identifier("active_sc_agent", &active_sc_agent);
    sc_helper_resolve_system_identifier("sc_agent_of_search_of_all_output_arcs_agent_scp", &agent);

    sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);

    //sc_addr arc = sc_memory_arc_new(sc_type_arc_pos_const_perm, active_sc_agent, agent);

    //sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);

    /*sc_memory_element_free(arc);

    sc_memory_arc_new(sc_type_arc_pos_const_perm, init, quest);*/
}

void test_scp_process_creating(int value)
{
    int i = 0;
    for (i = 0; i < value; i++)
    {
        create_process_test();
    }
}

int main(void)
{
    GTimer *timer = 0;
    sc_memory_params params;
    sc_memory_params_clear(&params);

    params.clear = SC_FALSE;
    params.repo_path = "repo";
    params.config_file = "sctp_config.ini";
    params.ext_path = "extensions";

    sc_memory_initialize(&params);

    timer = g_timer_new();
    g_timer_start(timer);

    sleep(1);

    test_scp_process_creating(1);
    //merge_test();
    //temp();

    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    sc_memory_shutdown();

    return 0;
}
