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
#ifndef SCP_FUNCTIONS_H
#define SCP_FUNCTIONS_H

#include "scp_types.h"

scp_result scp_lib_init(const sc_char *repo_path, const sc_char *config_file);
scp_result scp_lib_shutdown();

scp_result genEl(scp_operand *param);
scp_result genElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result genElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5);

scp_result searchElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result searchElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5);

//scp_result searchSetStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3);
//scp_result searchSetStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5);

scp_result eraseEl(scp_operand *param);
scp_result eraseElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result eraseElStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5);
scp_result eraseSetStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result eraseSetStr5(scp_operand *param1, scp_operand *param2, scp_operand *param3, scp_operand *param4, scp_operand *param5);

scp_result ifVarAssign(scp_operand *param);
scp_result ifFormCont(scp_operand *param);
scp_result ifCoin(scp_operand *param1, scp_operand *param2);
scp_result ifEq(scp_operand *param1, scp_operand *param2);
scp_result ifGr(scp_operand *param1, scp_operand *param2);
scp_result ifType(scp_operand *param);

scp_result varAssign(scp_operand *param1, scp_operand *param2);

scp_result contAdd(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result contDiv(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result contMult(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result contSub(scp_operand *param1, scp_operand *param2, scp_operand *param3);
scp_result contPow(scp_operand *param1, scp_operand *param2, scp_operand *param3);

scp_result contLn(scp_operand *param1, scp_operand *param2);
scp_result contSin(scp_operand *param1, scp_operand *param2);
scp_result contCos(scp_operand *param1, scp_operand *param2);
scp_result contTg(scp_operand *param1, scp_operand *param2);
scp_result contAsin(scp_operand *param1, scp_operand *param2);
scp_result contACos(scp_operand *param1, scp_operand *param2);
scp_result contATg(scp_operand *param1, scp_operand *param2);

scp_result contAssign(scp_operand *param1, scp_operand *param2);
scp_result contErase(scp_operand *param);

//scp_result idtfSearch(scp_operand *param, const char *idtf);
//scp_result idtfAssign(scp_operand *param, const char *idtf);

scp_result print(scp_operand *param);
scp_result printNl(scp_operand *param);
scp_result printEl(scp_operand *param);

scp_result scp_lib_resolve_system_identifier(const char* idtf, scp_operand *param);

#endif // SCP_FUNCTIONS_H
