#ifndef SYSTEM_H
#define SYSTEM_H
#include "sc_memory.h"
#include "sc_iterator.h"
#include "sc_stream_memory.h"

/*! Prints sc-element and all its input and output arcs.
 * @param addr sc-addr of element
 * @return Returns SC_FALSE, if system error appeared. Otherwise returns SC_TRUE.
 */
sc_bool print_element(sc_addr element);

#endif // SYSTEM_H
