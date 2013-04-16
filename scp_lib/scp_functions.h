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

scp_result genEl(scp_element *param);
scp_result genElStr3(scp_element *param1, scp_element *param2, scp_element *param3);
scp_result genElStr5(scp_element *param1, scp_element *param2, scp_element *param3, scp_element *param4, scp_element *param5);

scp_result searchElStr3(scp_element *param1, scp_element *param2, scp_element *param3);
scp_result searchElStr5(scp_element *param1, scp_element *param2, scp_element *param3, scp_element *param4, scp_element *param5);

scp_result eraseEl(scp_element *param);
scp_result eraseElStr3(scp_element *param1, scp_element *param2, scp_element *param3);
scp_result eraseElStr5(scp_element *param1, scp_element *param2, scp_element *param3, scp_element *param4, scp_element *param5);

scp_result ifVarAssign(scp_element *param);
scp_result ifFormCont(scp_element *param);
scp_result ifCoin(scp_element *param1, scp_element *param2);
scp_result ifEq(scp_element *param1, scp_element *param2);
scp_result ifGr(scp_element *param1, scp_element *param2);
scp_result ifType(scp_element *param, scp_type type);

scp_result varAssign(scp_element *param1, scp_element *param2);

scp_result contAdd(scp_element *param1, scp_element *param2);
scp_result contDiv(scp_element *param1, scp_element *param2);
scp_result contMult(scp_element *param1, scp_element *param2);
scp_result contSub(scp_element *param1, scp_element *param2);
scp_result contPow(scp_element *param1, scp_element *param2);
scp_result contLn(scp_element *param1, scp_element *param2);

scp_result contAssign(scp_element *param1, scp_element *param2);
scp_result contErase(scp_element *param);

scp_result idtfSearch(scp_element *param, const char* idtf);
scp_result idtfAssign(scp_element *param, const char* idtf);

#endif // SCP_FUNCTIONS_H
