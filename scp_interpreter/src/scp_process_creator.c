/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2013 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "sc_memory_headers.h"
#include "scp_process_creator.h"
#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"

#include <stdio.h>

sc_event *event_program_iterpretation;

sc_result create_scp_process(sc_event *event, sc_addr arg)
{
    scp_operand param1, param2, scp_procedure_node, scp_process_node;
    MAKE_DEFAULT_OPERAND_ASSIGN(param1);
    MAKE_DEFAULT_OPERAND_FIXED(param2);
    MAKE_DEFAULT_OPERAND_ASSIGN(scp_procedure_node);
    MAKE_DEFAULT_OPERAND_FIXED(scp_process_node);
    param2.addr = arg;

    if (SCP_RESULT_TRUE != searchElStr3(&param1, &param2, &scp_procedure_node))
    {
        return print_error("scp-process creating", "Can't find scp-procedure");
    }

    param2.param_type = SCP_ASSIGN;
    param2.element_type = scp_type_arc_pos | scp_type_arc_perm | scp_type_const;
    if (SCP_RESULT_TRUE != searchElStr3(&scp_procedure, &param2, &scp_procedure_node))
    {
        return SCP_RESULT_FALSE;
    }

    scp_process_node.element_type = scp_type_const | scp_type_node;
    scp_process_node.param_type = SCP_ASSIGN;
    genEl(&scp_process_node);

    printEl(&scp_procedure_node);

    return SCP_RESULT_TRUE;
}

scp_result scp_process_creator_init()
{
    event_program_iterpretation = sc_event_new(interpretation_request.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, create_scp_process, 0);
    if (event_program_iterpretation == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_process_creator_shutdown()
{
    sc_event_destroy(event_program_iterpretation);
    return SCP_RESULT_TRUE;
}
