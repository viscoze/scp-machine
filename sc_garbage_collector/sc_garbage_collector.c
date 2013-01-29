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

#include "sc_garbage_collector.h"
#include "sc_helper.h"
#include "sc_event.h"
#include "sc_garbage_collector_operations.h"
#include <stdio.h>

sc_addr question_unuseful;

const char question_unuseful_str[] = "question_unuseful";

sc_event* event_question_unuseful;

// --------------------- Module ------------------------

sc_result initialize() {

    if (sc_helper_resolve_system_identifier(question_unuseful_str, &question_unuseful) == SC_FALSE)
        return SC_RESULT_ERROR;

    event_question_unuseful = sc_event_new(question_unuseful, SC_EVENT_ADD_OUTPUT_ARC, 0, operation_garbage_collector_unuseful_question, 0);
    if (event_question_unuseful == nullptr)
        return SC_RESULT_ERROR;

    return SC_RESULT_OK;
}

sc_result shutdown() {
    sc_event_destroy(event_question_unuseful);

    return SC_RESULT_OK;
}

