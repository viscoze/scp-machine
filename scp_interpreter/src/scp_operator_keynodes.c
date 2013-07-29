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

#include "sc_helper.h"
#include "scp_operator_keynodes.h"
#include "scp_interpreter_utils.h"

scp_operand scp_operator;

scp_operand op_searchElStr3;
scp_operand op_searchElStr5;

scp_operand op_searchIterStr3;
scp_operand op_searchIterStr5;

scp_operand op_genEl;
scp_operand op_genElStr3;
scp_operand op_genElStr5;

scp_operand op_eraseEl;
scp_operand op_eraseElStr3;
scp_operand op_eraseElStr5;
scp_operand op_eraseSetStr3;
scp_operand op_eraseSetStr5;

scp_operand op_ifVarAssign;
scp_operand op_ifFormCont;
scp_operand op_ifCoin;
scp_operand op_ifEq;
scp_operand op_ifGr;
scp_operand op_ifType;

scp_operand op_varAssign;

scp_operand op_contAdd;
scp_operand op_contDiv;
scp_operand op_contMult;
scp_operand op_contSub;
scp_operand op_contPow;

scp_operand op_contLn;
scp_operand op_contSin;
scp_operand op_contCos;
scp_operand op_contTg;
scp_operand op_contAsin;
scp_operand op_contACos;
scp_operand op_contATg;

scp_operand op_contAssign;
scp_operand op_contErase;

scp_operand op_print;
scp_operand op_printNl;
scp_operand op_printEl;

scp_operand op_sys_search;
scp_operand op_sys_gen;

scp_operand op_call;
scp_operand op_waitReturn;
scp_operand op_waitReturnSet;
scp_operand op_return;

scp_result init_operator_keynodes()
{
    MAKE_DEFAULT_OPERAND_FIXED(scp_operator);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchElStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchElStr5);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchIterStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchIterStr5);
    MAKE_DEFAULT_OPERAND_FIXED(op_genEl);
    MAKE_DEFAULT_OPERAND_FIXED(op_genElStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_genElStr5);
    MAKE_DEFAULT_OPERAND_FIXED(op_eraseEl);
    MAKE_DEFAULT_OPERAND_FIXED(op_eraseElStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_eraseElStr5);
    MAKE_DEFAULT_OPERAND_FIXED(op_eraseSetStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_eraseSetStr5);
    MAKE_DEFAULT_OPERAND_FIXED(op_ifVarAssign);
    MAKE_DEFAULT_OPERAND_FIXED(op_ifFormCont);
    MAKE_DEFAULT_OPERAND_FIXED(op_ifCoin);
    MAKE_DEFAULT_OPERAND_FIXED(op_ifEq);
    MAKE_DEFAULT_OPERAND_FIXED(op_ifGr);
    MAKE_DEFAULT_OPERAND_FIXED(op_ifType);
    MAKE_DEFAULT_OPERAND_FIXED(op_varAssign);
    MAKE_DEFAULT_OPERAND_FIXED(op_contAdd);
    MAKE_DEFAULT_OPERAND_FIXED(op_contDiv);
    MAKE_DEFAULT_OPERAND_FIXED(op_contMult);
    MAKE_DEFAULT_OPERAND_FIXED(op_contSub);
    MAKE_DEFAULT_OPERAND_FIXED(op_contPow);
    MAKE_DEFAULT_OPERAND_FIXED(op_contLn);
    MAKE_DEFAULT_OPERAND_FIXED(op_contSin);
    MAKE_DEFAULT_OPERAND_FIXED(op_contCos);
    MAKE_DEFAULT_OPERAND_FIXED(op_contTg);
    MAKE_DEFAULT_OPERAND_FIXED(op_contAsin);
    MAKE_DEFAULT_OPERAND_FIXED(op_contACos);
    MAKE_DEFAULT_OPERAND_FIXED(op_contATg);
    MAKE_DEFAULT_OPERAND_FIXED(op_contAssign);
    MAKE_DEFAULT_OPERAND_FIXED(op_contErase);
    MAKE_DEFAULT_OPERAND_FIXED(op_print);
    MAKE_DEFAULT_OPERAND_FIXED(op_printNl);
    MAKE_DEFAULT_OPERAND_FIXED(op_printEl);
    MAKE_DEFAULT_OPERAND_FIXED(op_sys_search);
    MAKE_DEFAULT_OPERAND_FIXED(op_sys_gen);
    MAKE_DEFAULT_OPERAND_FIXED(op_call);
    MAKE_DEFAULT_OPERAND_FIXED(op_waitReturn);
    MAKE_DEFAULT_OPERAND_FIXED(op_waitReturnSet);
    MAKE_DEFAULT_OPERAND_FIXED(op_return);
    if (SC_TRUE != sc_helper_resolve_system_identifier("scp_operator", &scp_operator.addr))
    {
        return print_error("Keynode not found", "scp_operator");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("searchElStr3", &op_searchElStr3.addr))
    {
        return print_error("Keynode not found", "searchElStr3");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("searchElStr5", &op_searchElStr5.addr))
    {
        return print_error("Keynode not found", "searchElStr5");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("searchIterStr3", &op_searchIterStr3.addr))
    {
        return print_error("Keynode not found", "searchIterStr3");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("searchIterStr5", &op_searchIterStr5.addr))
    {
        return print_error("Keynode not found", "searchIterStr5");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("eraseEl", &op_eraseEl.addr))
    {
        return print_error("Keynode not found", "eraseEl");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("eraseElStr3", &op_eraseElStr3.addr))
    {
        return print_error("Keynode not found", "eraseElStr3");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("eraseElStr5", &op_eraseElStr5.addr))
    {
        return print_error("Keynode not found", "eraseElStr5");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("eraseSetStr3", &op_eraseSetStr3.addr))
    {
        return print_error("Keynode not found", "eraseSetStr3");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("eraseSetStr5", &op_eraseSetStr5.addr))
    {
        return print_error("Keynode not found", "eraseSetStr5");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("ifVarAssign", &op_ifVarAssign.addr))
    {
        return print_error("Keynode not found", "ifVarAssign");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("ifFormCont", &op_ifFormCont.addr))
    {
        return print_error("Keynode not found", "ifFormCont");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("ifCoin", &op_ifCoin.addr))
    {
        return print_error("Keynode not found", "ifCoin");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("ifEq", &op_ifEq.addr))
    {
        return print_error("Keynode not found", "ifEq");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("ifGr", &op_ifGr.addr))
    {
        return print_error("Keynode not found", "ifGr");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("ifType", &op_ifType.addr))
    {
        return print_error("Keynode not found", "ifType");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("varAssign", &op_varAssign.addr))
    {
        return print_error("Keynode not found", "varAssign");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contAdd", &op_contAdd.addr))
    {
        return print_error("Keynode not found", "contAdd");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contDiv", &op_contDiv.addr))
    {
        return print_error("Keynode not found", "contDiv");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contMult", &op_contMult.addr))
    {
        return print_error("Keynode not found", "contMult");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contSub", &op_contSub.addr))
    {
        return print_error("Keynode not found", "contSub");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contPow", &op_contPow.addr))
    {
        return print_error("Keynode not found", "contPow");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contLn", &op_contLn.addr))
    {
        return print_error("Keynode not found", "contLn");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contSin", &op_contSin.addr))
    {
        return print_error("Keynode not found", "contSin");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contCos", &op_contCos.addr))
    {
        return print_error("Keynode not found", "contCos");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contTg", &op_contTg.addr))
    {
        return print_error("Keynode not found", "contTg");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contAsin", &op_contAsin.addr))
    {
        return print_error("Keynode not found", "contAsin");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contACos", &op_contACos.addr))
    {
        return print_error("Keynode not found", "contACos");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contATg", &op_contATg.addr))
    {
        return print_error("Keynode not found", "contATg");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contAssign", &op_contAssign.addr))
    {
        return print_error("Keynode not found", "contAssign");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("contErase", &op_contErase.addr))
    {
        return print_error("Keynode not found", "contErase");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("print", &op_print.addr))
    {
        return print_error("Keynode not found", "print");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("printNl", &op_printNl.addr))
    {
        return print_error("Keynode not found", "printNl");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("printEl", &op_printEl.addr))
    {
        return print_error("Keynode not found", "printEl");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("sys_search", &op_sys_search.addr))
    {
        return print_error("Keynode not found", "sys_search");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("sys_gen", &op_sys_gen.addr))
    {
        return print_error("Keynode not found", "sys_gen");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("call", &op_call.addr))
    {
        return print_error("Keynode not found", "call");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("waitReturn", &op_waitReturn.addr))
    {
        return print_error("Keynode not found", "waitReturn");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("waitReturnSet", &op_waitReturnSet.addr))
    {
        return print_error("Keynode not found", "waitReturnSet");
    }
    if (SC_TRUE != sc_helper_resolve_system_identifier("return", &op_return.addr))
    {
        return print_error("Keynode not found", "return");
    }

    return SCP_RESULT_TRUE;
}
