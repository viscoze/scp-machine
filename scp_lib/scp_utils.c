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

#include "scp_types.h"
#include "sc_memory.h"
#include "stdio.h"

scp_result check_type(sc_addr element, sc_type input_type)
{
    sc_type type;
    if (SC_RESULT_OK != sc_memory_get_element_type(element, &type))
    {
        return SCP_ERROR;
    }
    if ((input_type & type) == input_type)
    {
        return SCP_TRUE;
    }
    else
    {
        return SCP_FALSE;
    }
    return SCP_ERROR;
}

scp_result printError(const char *operator_name, const char *text)
{
    printf("\nSCP LIBRARY ERROR: %s : %s\n", operator_name, text);
    return SCP_ERROR;
}


