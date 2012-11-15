#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include "system.h"

sc_addr NREL_SYSTEM_IDENTIFIER;

sc_bool init_identification();
sc_addr find_element_by_id(sc_char* id);
sc_addr gen_element_with_id(sc_char* sys_idtf, sc_type type);

#endif // IDENTIFICATION_H
