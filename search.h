#ifndef SEARCH_H
#define SEARCH_H
#include "sc_memory.h"
#include "sc_iterator.h"
#include "sc_stream_memory.h"
#include "system.h"

/*! Search all constant positive permanent arcs, which outcome from given element
 * @param addr sc-addr of element
 * @param addr sc-addr of set, which will contain all the elements of answer.
 * @return Returns SC_FALSE, if system error appeared. Otherwise returns SC_TRUE.
 */
sc_bool search_all_const_pos_output_arc(sc_addr node,sc_addr answer);
/*! Search all constant positive permanent arcs, which income in given element
 * @param addr sc-addr of element
 * @param addr sc-addr of set, which will contain all the elements of answer.
 * @return Returns SC_FALSE, if system error appeared. Otherwise returns SC_TRUE.
 */
sc_bool search_all_const_pos_input_arc(sc_addr node,sc_addr answer);
/*! Search all constant positive permanent arcs, which income in given element,
 * including signs of role relations, linked with these arcs.
 * @param addr sc-addr of element
 * @param addr sc-addr of set, which will contain all the elements of answer.
 * @return Returns SC_FALSE, if system error appeared. Otherwise returns SC_TRUE.
 */
sc_bool search_all_const_pos_input_arc_with_attr(sc_addr node,sc_addr answer);
/*! Search all constant positive permanent arcs, which outcome from given element,
 * including signs of role relations, linked with these arcs.
 * @param addr sc-addr of element
 * @param addr sc-addr of set, which will contain all the elements of answer.
 * @return Returns SC_FALSE, if system error appeared. Otherwise returns SC_TRUE.
 */
sc_bool search_all_const_pos_output_arc_with_attr(sc_addr node,sc_addr answer);

sc_bool search_full_semantic_neighbourhood(sc_addr node,sc_addr answer);

#endif // SEARCH_H
