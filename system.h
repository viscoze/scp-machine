#ifndef SYSTEM_H
#define SYSTEM_H
#define NULLPTR (void*)0
#include "sc_memory.h"
#include "sc_iterator.h"
#include "sc_stream_memory.h"

/*! Prints sc-element and all its input and output arcs.
 * @param addr sc-addr of element
 * @return Returns SC_FALSE, if system error appeared. Otherwise returns SC_TRUE.
 */
sc_bool print_element(sc_addr element);

sc_result search_question_answer(sc_addr question, sc_addr* answer);

#endif // SYSTEM_H
