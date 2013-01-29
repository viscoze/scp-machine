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
#include "sc_iterator3.h"
#include "sc_garbage_collector.h"
#include "sc_garbage_collector_functions.h"
#include <stdio.h>

sc_result operation_garbage_collector_unuseful_question(sc_event *event, sc_addr arg) {
    sc_addr quest;

    if (!sc_memory_get_arc_end(arg, &quest)) {
        return SC_RESULT_ERROR_INVALID_PARAMS;
    };

    garbage_collector_unuseful_question(quest);

    printf("KPM: operation_garbage_collector_unuseful_question worked succesfully\n");

    return SC_RESULT_OK;
}
