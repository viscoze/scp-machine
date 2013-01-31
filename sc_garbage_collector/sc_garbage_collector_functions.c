/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2012 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS. If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
 */

#include "sc_helper.h"
#include "sc_memory.h"
#include "sc_iterator5.h"


sc_result garbage_collector_unuseful_question(sc_addr quest){

    sc_addr nrel_answer;
    if (sc_helper_resolve_system_identifier("question_nrel_answer", &nrel_answer) == SC_FALSE)
        return SC_RESULT_ERROR;
    sc_addr nrel_translation;
    if (sc_helper_resolve_system_identifier("nrel_translation", &nrel_translation) == SC_FALSE)
        return SC_RESULT_ERROR;
    sc_addr rrel_source_constr;
    if (sc_helper_resolve_system_identifier("ui_rrel_source_sc_construction", &rrel_source_constr) == SC_FALSE)
        return SC_RESULT_ERROR;
    sc_addr nrel_result;
    if (sc_helper_resolve_system_identifier("ui_nrel_command_result", &nrel_result) == SC_FALSE)
        return SC_RESULT_ERROR;
    sc_addr rrel_arg;
    if (sc_helper_resolve_system_identifier("ui_rrel_command_arguments", &rrel_arg) == SC_FALSE)
        return SC_RESULT_ERROR;
    sc_addr nrel_user_formats;
    if (sc_helper_resolve_system_identifier("ui_nrel_user_answer_formats", &nrel_user_formats) == SC_FALSE)
        return SC_RESULT_ERROR;

    sc_iterator5 *it_answer=sc_iterator5_f_a_a_a_f_new(quest,0,0,sc_type_arc_pos_const_perm,nrel_answer);
    while(sc_iterator5_next(it_answer)){
        sc_addr answer=sc_iterator5_value(it_answer,2);

        //Removing translation
        sc_iterator5 *it_transl=sc_iterator5_f_a_a_a_f_new(answer,0,0,sc_type_arc_pos_const_perm,nrel_translation);
        while(sc_iterator5_next(it_transl)){
            sc_addr transl=sc_iterator5_value(it_transl,2);
            sc_memory_element_free(transl);
        }
        sc_iterator5_free(it_transl);

        //Removing user formats node
        sc_iterator5 *it_format=sc_iterator5_f_a_a_a_f_new(answer,0,0,sc_type_arc_pos_const_perm,nrel_user_formats);
        while(sc_iterator5_next(it_format)){
            sc_addr format=sc_iterator5_value(it_format,2);
            sc_memory_element_free(format);
        }
        sc_iterator5_free(it_format);

        //Removing source sc-construction
        sc_iterator5 *it_source=sc_iterator5_a_a_f_a_f_new(0,sc_type_arc_pos_const_perm,answer,sc_type_arc_pos_const_perm,rrel_source_constr);
        while(sc_iterator5_next(it_source)){
            sc_addr source=sc_iterator5_value(it_source,0);
            sc_memory_element_free(source);
        }
        sc_iterator5_free(it_source);

        //Removing command result
        sc_iterator5 *it_result=sc_iterator5_a_a_f_a_f_new(0,0,answer,sc_type_arc_pos_const_perm,nrel_result);
        while(sc_iterator5_next(it_result)){
            sc_addr result=sc_iterator5_value(it_result,0);

            //Removing arguments
            sc_iterator5 *it_arg=sc_iterator5_f_a_a_a_f_new(result,sc_type_arc_pos_const_perm,0,sc_type_arc_pos_const_perm,rrel_arg);
            while(sc_iterator5_next(it_arg)){
                sc_addr arg=sc_iterator5_value(it_arg,2);
                sc_memory_element_free(arg);
            }
            sc_iterator5_free(it_arg);

            sc_memory_element_free(result);
        }
        sc_iterator5_free(it_result);

        sc_memory_element_free(answer);
    }
    sc_iterator5_free(it_answer);

    sc_memory_element_free(quest);

    return SC_RESULT_OK;
}
