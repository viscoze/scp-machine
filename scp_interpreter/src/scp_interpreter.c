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

#include "scp_interpreter.h"
#include "scp_keynodes.h"
#include "scp_procedure_preprocessor.h"
#include "scp_process_creator.h"
#include "scp_process_destroyer.h"
#include "scp_operator_interpreter_agents.h"
#include "scp_interpreter_utils.h"

#include <stdio.h>

scp_result init_all_scp_agents()
{
    scp_operand proc, arc, com_arc, init_prog;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    MAKE_COMMON_ARC_ASSIGN(com_arc);
    MAKE_DEFAULT_OPERAND_ASSIGN(proc);
    MAKE_DEFAULT_NODE_ASSIGN(init_prog);
    scp_iterator3 *it;
    it = scp_iterator3_new(&scp_agent, &arc, &proc);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &scp_agent, &arc, &proc))
    {
        proc.param_type = SCP_FIXED;
        init_prog.param_type = SCP_ASSIGN;
        searchElStr5(&proc, &com_arc, &init_prog, &arc, &nrel_init_program);
        init_prog.param_type = SCP_FIXED;
        run_scp_program(&init_prog);
        proc.param_type = SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SC_RESULT_OK;
}

sc_result initialize()
{
    if (SCP_RESULT_TRUE == scp_lib_init() &&
        SCP_RESULT_TRUE == scp_keynodes_init() &&
        SCP_RESULT_TRUE == scp_process_destroyer_init() &&
        SCP_RESULT_TRUE == scp_operator_interpreter_agents_init() &&
        SCP_RESULT_TRUE == scp_procedure_preprocessor_init() &&
        SCP_RESULT_TRUE == scp_process_creator_init() &&
        SCP_RESULT_TRUE == init_all_scp_agents())
        return SCP_RESULT_TRUE;
    else
        return SCP_RESULT_ERROR;
}

sc_result shutdown()
{
    if (SCP_RESULT_TRUE == scp_lib_shutdown() &&
        SCP_RESULT_TRUE == scp_process_destroyer_shutdown() &&
        SCP_RESULT_TRUE == scp_operator_interpreter_agents_shutdown() &&
        SCP_RESULT_TRUE == scp_procedure_preprocessor_shutdown() &&
        SCP_RESULT_TRUE == scp_process_creator_shutdown())
        return SCP_RESULT_TRUE;
    else
        return SCP_RESULT_ERROR;
}
