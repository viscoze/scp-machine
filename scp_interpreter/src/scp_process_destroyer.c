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
#include "scp_process_destroyer.h"
#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"

#include <stdio.h>

sc_event *event_process_destroy;

sc_result destroy_scp_process(sc_event *event, sc_addr arg)
{
    scp_operand arc1, arc2, node1, node2, node3, node4, scp_process_node, operator_type;
    scp_iterator3 *it;
    MAKE_DEFAULT_OPERAND_FIXED(arc1);
    MAKE_DEFAULT_NODE_ASSIGN(scp_process_node);
    arc1.addr = arg;

    MAKE_DEFAULT_OPERAND_ASSIGN(node1);
    if (SCP_RESULT_TRUE != searchElStr3(&node1, &arc1, &scp_process_node))
    {
        return SC_RESULT_ERROR;
    }

    MAKE_DEFAULT_ARC_ASSIGN(arc1);
    scp_process_node.param_type = SCP_FIXED;

    MAKE_DEFAULT_ARC_ASSIGN(arc2);
    MAKE_DEFAULT_OPERAND_ASSIGN(node2);
    node1.erase = SCP_TRUE;
    node2.erase = SCP_TRUE;

    /*it = scp_iterator3_new(&node1, &arc1, &node2);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, &node1, &arc1, &node2))
    {

    }
    scp_iterator3_free(it);*/

    /*if (SCP_RESULT_TRUE == searchElStr5(&scp_process_node, &arc1, &node1, &arc2, &rrel_copies))
    {
        //printf("COPIES\n");
        node1.param_type = SCP_FIXED;
        eraseSetStr3(&node1, &arc2, &node2);
        node1.param_type = SCP_ASSIGN;
    }
    if (SCP_RESULT_TRUE == searchElStr5(&scp_process_node, &arc1, &node1, &arc2, &rrel_vars))
    {
        //printf("VARS\n");
        node1.param_type = SCP_FIXED;
        eraseSetStr3(&node1, &arc2, &node2);
        node1.param_type = SCP_ASSIGN;
    }

    MAKE_DEFAULT_OPERAND_ASSIGN(node3);
    MAKE_DEFAULT_OPERAND_ASSIGN(node4);
    node3.erase = SCP_TRUE;
    node4.erase = SCP_TRUE;
    MAKE_DEFAULT_NODE_ASSIGN(operator_type);
    if (SCP_RESULT_TRUE == searchElStr5(&scp_process_node, &arc1, &node1, &arc2, &rrel_operators))
    {
        node1.param_type = SCP_FIXED;
        it = scp_iterator3_new(&node1, &arc1, &node2);
        while (SCP_RESULT_TRUE == scp_iterator3_next(it, &node1, &arc1, &node2))
        {
            node2.param_type = SCP_FIXED;
            if (SCP_RESULT_TRUE != resolve_operator_type(&node2, &operator_type))
            {
                node2.param_type = SCP_ASSIGN;
                eraseEl(&node2);
                continue;
            }
            operator_type.param_type = SCP_FIXED;

            if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_call))
            {
                //printf("OPERATOR CALL\n");
                if (SCP_RESULT_TRUE == searchElStr5(&node2, &arc1, &node3, &arc2, &(ordinal_rrels[2])))
                {
                    node3.param_type = SCP_FIXED;
                    eraseEl(&node3);
                    node3.param_type = SCP_ASSIGN;
                }
                eraseEl(&node2);
                operator_type.param_type = SCP_ASSIGN;
                node2.param_type = SCP_ASSIGN;
                continue;
            }

            if (SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_gen) ||
                SCP_RESULT_TRUE == ifCoin(&operator_type, &op_sys_search))
            {
                //printf("OPERATOR SYSTEM\n");
                if (SCP_RESULT_TRUE == searchElStr5(&node2, &arc1, &node3, &arc2, &(ordinal_rrels[2])))
                {
                    node3.param_type = SCP_FIXED;
                    eraseSetStr3(&node3, &arc1, &node4);
                    node3.param_type = SCP_ASSIGN;
                }
                if (SCP_RESULT_TRUE == searchElStr5(&node2, &arc1, &node3, &arc2, &(ordinal_rrels[3])))
                {
                    node3.param_type = SCP_FIXED;
                    eraseSetStr3(&node3, &arc1, &node4);
                    node3.param_type = SCP_ASSIGN;
                }
                eraseEl(&node2);
                operator_type.param_type = SCP_ASSIGN;
                node2.param_type = SCP_ASSIGN;
                continue;
            }
            //printf("OPERATOR ORDINARY\n");
            eraseEl(&node2);
            operator_type.param_type = SCP_ASSIGN;
            node2.param_type = SCP_ASSIGN;
        }
        scp_iterator3_free(it);
        eraseEl(&node1);
        node1.param_type = SCP_ASSIGN;
    }

    scp_process_node.erase = SCP_TRUE;
    eraseSetStr3(&scp_process_node, &arc1, &node1);*/

    printf("PROCESS DESTROYED SUCCESSFULLY\n");
    return SC_RESULT_OK;
}

scp_result scp_process_destroyer_init()
{
    event_process_destroy = sc_event_new(useless_scp_process.addr, SC_EVENT_ADD_OUTPUT_ARC, 0, destroy_scp_process, 0);
    if (event_process_destroy == nullptr)
        return SCP_RESULT_ERROR;
    return SCP_RESULT_TRUE;
}

scp_result scp_process_destroyer_shutdown()
{
    sc_event_destroy(event_process_destroy);
    return SCP_RESULT_TRUE;
}

#include <stdio.h>
