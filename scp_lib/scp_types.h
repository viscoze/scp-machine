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
#ifndef SCP_TYPES_H
#define SCP_TYPES_H

#include "sc_types.h"

// parameter type
enum _scp_param_type
{
    SCP_ASSIGN = 0,
    SCP_FIXED = 1,
    SCP_ERASE
};

typedef enum _scp_param_type scp_param_type;

// result types
enum _scp_result
{
    SCP_TRUE = 0,
    SCP_FALSE = 1,
    SCP_ERROR
};

typedef enum _scp_result scp_result;

//! Structure to store scp-element
struct _scp_operand
{
    sc_addr addr;
    scp_param_type param_type;
    sc_type element_type;
};

typedef struct _scp_operand scp_operand;

typedef sc_uint16 scp_type;

// scp-element types
extern scp_type scp_type_node;
extern scp_type scp_type_link;
extern scp_type scp_type_edge_common;
extern scp_type scp_type_arc_common;
extern scp_type scp_type_arc_access;

// scp-element constant
extern scp_type scp_type_const;
extern scp_type scp_type_var;

// scp-element positivity
extern scp_type scp_type_arc_pos;
extern scp_type scp_type_arc_neg;
extern scp_type scp_type_arc_fuz;

// scp-element premanently
extern scp_type scp_type_arc_temp;
extern scp_type scp_type_arc_perm;

#endif // SCP_TYPES_H
