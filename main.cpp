extern "C"
{
#include "sc_kpm_additional.h"
#include <stdio.h>
#include <glib.h>
#include "sc_helper.h"
}
#include "sc_system_gen.h"
#include "sc_system_search.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int getch()
{
    struct termios oldt,
            newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

sc_result create_temp_question1()
{
    sc_addr node;
    sc_addr class_question_initiated, class_question_private;

    if (sc_helper_resolve_system_identifier("class_question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_output_const_pos_arc", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node01", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest = sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_private, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_initiated, quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest, &answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question2()
{
    sc_addr node;
    sc_addr class_question_initiated, class_question_private;

    if (sc_helper_resolve_system_identifier("class_question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_input_const_pos_arc", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node01", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest = sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_private, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_initiated, quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest, &answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question3()
{
    sc_addr node;
    sc_addr class_question_initiated, class_question_private;

    if (sc_helper_resolve_system_identifier("class_question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_full_semantic_neighbourhood", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node01", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest = sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_private, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_initiated, quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest, &answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question4()
{
    sc_addr node;
    sc_addr class_question_initiated, class_question_private;

    if (sc_helper_resolve_system_identifier("question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_output_const_pos_arc_with_rel", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node21", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest = sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_private, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_initiated, quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest, &answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question5()
{
    sc_addr node;
    sc_addr class_question_initiated, class_question_private;

    if (sc_helper_resolve_system_identifier("question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_input_const_pos_arc_with_rel", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node21", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest = sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_private, quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, quest, node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, class_question_initiated, quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest, &answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question_garbage1()
{
    sc_addr question_unuseful;

    if (sc_helper_resolve_system_identifier("question_unuseful", &question_unuseful) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr node69;
    node69.seg = 0;
    node69.offset = 69;
    print_element(node69);
    //sc_addr quest=sc_memory_node_new(0);
    //sc_memory_arc_new(sc_type_arc_pos_const_perm,question_unuseful,quest);

    sc_addr pattern;
    if (sc_helper_resolve_system_identifier("garbage_pattern", &pattern) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr temp;
    if (sc_helper_resolve_system_identifier("temp_question", &temp) == SC_FALSE)
        return SC_RESULT_ERROR;

    print_element(pattern);

    sc_memory_arc_new(sc_type_arc_pos_const_perm, question_unuseful, temp);

    sleep(2);

    print_element(pattern);

    return SC_RESULT_OK;
}

sc_result test_sys_search()
{

    //sc_addr start2;
    /*if (sc_helper_resolve_system_identifier("start2", &start2) == SC_FALSE)
        return SC_RESULT_ERROR;
    print_element(start2);*/

    //sc_addr end2;
    /*if (sc_helper_resolve_system_identifier("end2", &end2) == SC_FALSE)
        return SC_RESULT_ERROR;
    print_element(end2);*/

    sc_addr pattern;
    //pattern=sc_memory_node_new(sc_type_node_struct|sc_type_const);
    //start2=sc_memory_node_new(sc_type_node_struct|sc_type_const);
    //end2=sc_memory_node_new(sc_type_node_struct|sc_type_const);
    if (sc_helper_resolve_system_identifier("pattern3", &pattern) == SC_FALSE)
        return SC_RESULT_ERROR;
    print_element(pattern);

    /*for (int i=0;i<7;i++){
        sc_addr arc=sc_memory_arc_new(sc_type_arc_access|sc_type_var,start2,end2);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,arc);
        sc_memory_arc_new(sc_type_arc_pos_const_perm,start2,end2);
    }*/

    //sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,start2);
    //sc_memory_arc_new(sc_type_arc_pos_const_perm,pattern,end2);

    sc_type_result params;
    sc_type_result_vector results;

    system_sys_search(pattern, params, &results);

    return SC_RESULT_OK;
}

sc_result test_sys_gen()
{

    sc_addr pattern;
    /*if (sc_helper_resolve_system_identifier("start2", &pattern) == SC_FALSE)
        return SC_RESULT_ERROR;
    print_element(pattern);*/

    if (sc_helper_resolve_system_identifier("pattern2", &pattern) == SC_FALSE)
        return SC_RESULT_ERROR;
    print_element(pattern);

    sc_type_result params;
    sc_type_result_vector results;
    sc_type_result result;

    sc_addr addr1, addr2;
    addr1.seg = addr2.seg = 0;
    addr1.offset = 153;
    addr2.offset = 222;
    //params.insert(sc_addr_pair(addr1,addr2));

    sc_addr_vector vars;
    vars.push_back(addr1);

    system_sys_gen_for_variables(pattern, params, vars, &result);

    return SC_RESULT_OK;
}

void temp()
{
    sc_addr link;
    sc_char* data0=(sc_char*)"Minsk";
    sc_char* data;
    sc_uint32 buf_len,read_len;
    sc_stream *stream;

    link=sc_memory_node_new(sc_type_link);

    stream=sc_stream_memory_new(data0,6,SC_STREAM_READ,SC_FALSE);
    sc_memory_set_link_content(link,stream);
    sc_stream_free(stream);

    sc_memory_get_link_content(link,&stream);

    sc_stream_get_length(stream,&buf_len);
    data=(sc_char*)calloc(buf_len,sizeof(sc_char));

    sc_stream_read_data(stream,data,buf_len,&read_len);
    sc_stream_free(stream);

    printf("%s\n",data);
    free(data);
}

int main()
{
    sc_memory_initialize((sc_char *)"repo", (sc_char *)"test.ini");
    sc_helper_init();
    //sc_memory_initialize_ext("../bin/extensions");

    GTimer *timer = 0;
    timer = g_timer_new();
    g_timer_start(timer);

    //temp();

    //int i=0;
    sc_type_result params;
    sc_type_result_vector results;
    /*sc_addr_vector vars;
    sc_addr addr1,addr2;
    addr1.seg=0;addr2.seg=0;
    addr1.offset=39;addr2.offset=41;
    vars.push_back(addr1);
    vars.push_back(addr2);*/
    sc_addr node;
    sc_helper_resolve_system_identifier("pattern4",&node);
    //for (i=0;i<1;i++){
        system_sys_search_only_full(node,params,&results);
    //}

    g_timer_stop(timer);
    printf((sc_char *)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    //sc_memory_shutdown();

    sc_helper_shutdown();

    //getch();
    return 0;
}
