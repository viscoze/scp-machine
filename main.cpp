extern "C"
{
#include "sc_kpm_additional.h"
#include <stdio.h>
#include <glib.h>
#include "sc_helper.h"
}
#include "sc_search_system.h"
#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldt,
            newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

sc_result create_temp_question1()
{
    sc_addr node;
    sc_addr class_question_initiated,class_question_private;

    if (sc_helper_resolve_system_identifier("class_question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_output_const_pos_arc", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node01", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_private,quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_initiated,quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest,&answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question2()
{
    sc_addr node;
    sc_addr class_question_initiated,class_question_private;

    if (sc_helper_resolve_system_identifier("class_question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_input_const_pos_arc", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node01", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_private,quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_initiated,quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest,&answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question3()
{
    sc_addr node;
    sc_addr class_question_initiated,class_question_private;

    if (sc_helper_resolve_system_identifier("class_question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_full_semantic_neighbourhood", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node01", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_private,quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_initiated,quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest,&answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question4()
{
    sc_addr node;
    sc_addr class_question_initiated,class_question_private;

    if (sc_helper_resolve_system_identifier("question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_output_const_pos_arc_with_rel", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node21", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_private,quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_initiated,quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest,&answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question5()
{
    sc_addr node;
    sc_addr class_question_initiated,class_question_private;

    if (sc_helper_resolve_system_identifier("question_initiated", &class_question_initiated) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("class_question_all_input_const_pos_arc_with_rel", &class_question_private) == SC_FALSE)
        return SC_RESULT_ERROR;
    if (sc_helper_resolve_system_identifier("node21", &node) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr quest=sc_memory_node_new(0);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_private,quest);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,quest,node);
    sc_memory_arc_new(sc_type_arc_pos_const_perm,class_question_initiated,quest);

    sleep(2);

    sc_addr answer;

    search_question_answer(quest,&answer);

    print_element(answer);

    return SC_RESULT_OK;
}

sc_result create_temp_question_garbage1()
{
    sc_addr question_unuseful;

    if (sc_helper_resolve_system_identifier("question_unuseful", &question_unuseful) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_addr node69;
    node69.seg=0;
    node69.offset=69;
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

    sc_memory_arc_new(sc_type_arc_pos_const_perm,question_unuseful,temp);

    sleep(2);

    print_element(pattern);

    return SC_RESULT_OK;
}

sc_result test_sys_search(){
    sc_addr pattern;
    if (sc_helper_resolve_system_identifier("pattern2", &pattern) == SC_FALSE)
        return SC_RESULT_ERROR;
    print_element(pattern);

    sc_type_result params;
    sc_type_result_vector results;

    system_sys_search(pattern,params,&results);

    return SC_RESULT_OK;
}

int main()
{
    sc_memory_initialize((sc_char*)"repo",(sc_char*)"test.ini");
    sc_helper_init();
    sc_memory_initialize_ext("../bin/modules");

    GTimer *timer = 0;
    timer=g_timer_new();
    g_timer_start(timer);

    test_sys_search();

    /*int i=0;
    sc_type_result params;
    sc_type_result_vector results;
    sc_addr_vector vars;
    sc_addr addr1,addr2;
    addr1.seg=0;addr2.seg=0;
    addr1.offset=39;addr2.offset=41;
    vars.push_back(addr1);
    vars.push_back(addr2);
    for (i=0;i<1;i++){
        //system_sys_search_only_full(node,params,&results);
    }  
*/
    g_timer_stop(timer);
    printf((sc_char*)"Time: %f s\n", g_timer_elapsed(timer, 0));
    g_timer_destroy(timer);

    //sc_memory_shutdown();

    sc_helper_shutdown();

    //getch();
    return 0;
}
