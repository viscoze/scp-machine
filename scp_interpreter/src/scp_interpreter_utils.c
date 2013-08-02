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

#include "scp_interpreter_utils.h"
#include "scp_keynodes.h"
#include "stdio.h"

scp_result print_error(const char *error_type, const char *text)
{
    printf("\nSCP INTERPRETER ERROR: %s : %s\n", error_type, text);
    return SCP_RESULT_ERROR;
}

scp_result resolve_operator_type(scp_operand *oper, scp_operand *type)
{
    scp_operand arc;
    MAKE_DEFAULT_ARC_ASSIGN(arc);
    MAKE_DEFAULT_NODE_ASSIGN((*type));

    oper->param_type = SCP_FIXED;
    scp_iterator3 *it = scp_iterator3_new(type, &arc, oper);
    while (SCP_RESULT_TRUE == scp_iterator3_next(it, type, &arc, oper))
    {
        type->param_type=SCP_FIXED;
        if (SCP_RESULT_TRUE == searchElStr3(&scp_operator, &arc, type))
        {
            scp_iterator3_free(it);
            return SCP_RESULT_TRUE;
        }
        type->param_type=SCP_ASSIGN;
    }
    scp_iterator3_free(it);
    return SCP_RESULT_FALSE;
}
