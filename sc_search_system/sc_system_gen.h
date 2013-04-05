#ifndef SC_SYSTEM_GEN_H
#define SC_SYSTEM_GEN_H

extern "C"
{
#include "sc_memory.h"
}
#include "sc_system_operators.h"

/*! Generates fully isomorfic construction to given
 * @param pattern Generation pattern
 * @param params Generation parameters. Can be empty
 * @param result Set of results. Contains pairs between variables from pattern and generated constants.
 * @return If input params are correct and generation completed without errors, then return SC_OK;
 * otherwise return SC_ERROR
 */
sc_result system_sys_gen(sc_addr pattern, sc_type_result params, sc_type_result *result);

/*! Generates fully isomorfic construction to given
 * @param pattern Generation pattern
 * @param params Generation parameters. Can be empty
 * @param result Set of results. Contains pairs between variables from pattern and generated constants onle for variables given in requested_values vector
 * @return If input params are correct and generation completed without errors, then return SC_OK;
 * otherwise return SC_ERROR
 */
sc_result system_sys_gen_for_variables(sc_addr pattern, sc_type_result params, sc_addr_vector requested_values, sc_type_result *result);

#endif // SC_SYSTEM_GEN_H
