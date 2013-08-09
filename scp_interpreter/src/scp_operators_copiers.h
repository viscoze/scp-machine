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

#ifndef SCP_OPERATORS_COPIERS_H
#define SCP_OPERATORS_COPIERS_H

#include "sc_memory_headers.h"

sc_result copy_sys_operator(sc_event *event, sc_addr arg);
sc_result copy_return_operator(sc_event *event, sc_addr arg);
sc_result copy_call_operator(sc_event *event, sc_addr arg);
sc_result copy_ordinary_operator(sc_event *event, sc_addr arg);

sc_result process_successfully_finished_operator_copying_request(sc_event *event, sc_addr arg);
sc_result process_unsuccessfully_finished_operator_copying_request(sc_event *event, sc_addr arg);

#endif // SCP_OPERATORS_COPIERS_H
