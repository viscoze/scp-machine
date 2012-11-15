#ifndef SEARCH_OPERATIONS_H
#define SEARCH_OPERATIONS_H

#include "system.h"

sc_result operation_search_all_const_pos_output_arc(sc_event *event, sc_addr arg);
sc_result operation_search_all_const_pos_input_arc(sc_event *event, sc_addr arg);
sc_result operation_search_full_semantic_neighbourhood(sc_event *event, sc_addr arg);

#endif // SEARCH_OPERATIONS_H
