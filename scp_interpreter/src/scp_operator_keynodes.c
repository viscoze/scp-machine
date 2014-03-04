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

//scp_operand op_searchIterStr3;
//scp_operand op_searchIterStr5;

scp_operand op_searchSetStr3;
scp_operand op_searchSetStr5;

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
scp_operand op_contASin;
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

scp_operand op_sys_set_event_handler;
scp_operand op_sys_delete_event_handler;
scp_operand op_sys_wait;

scp_result init_operator_keynodes()
{
    MAKE_DEFAULT_OPERAND_FIXED(scp_operator);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchElStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchElStr5);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchSetStr3);
    MAKE_DEFAULT_OPERAND_FIXED(op_searchSetStr5);
    //MAKE_DEFAULT_OPERAND_FIXED(op_searchIterStr3);
    //MAKE_DEFAULT_OPERAND_FIXED(op_searchIterStr5);
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
    MAKE_DEFAULT_OPERAND_FIXED(op_contASin);
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
    MAKE_DEFAULT_OPERAND_FIXED(op_sys_set_event_handler);
    MAKE_DEFAULT_OPERAND_FIXED(op_sys_delete_event_handler);
    MAKE_DEFAULT_OPERAND_FIXED(op_sys_wait);
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("scp_operator", &scp_operator))
    {
        return print_error("Keynode not found", "scp_operator");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("searchElStr3", &op_searchElStr3))
    {
        return print_error("Keynode not found", "searchElStr3");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("searchElStr5", &op_searchElStr5))
    {
        return print_error("Keynode not found", "searchElStr5");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("searchSetStr3", &op_searchSetStr3))
    {
        return print_error("Keynode not found", "searchSetStr3");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("searchSetStr5", &op_searchSetStr5))
    {
        return print_error("Keynode not found", "searchSetStr5");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("genEl", &op_genEl))
    {
        return print_error("Keynode not found", "genEl");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("genElStr3", &op_genElStr3))
    {
        return print_error("Keynode not found", "genElStr3");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("genElStr5", &op_genElStr5))
    {
        return print_error("Keynode not found", "genElStr5");
    }
    /*if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("searchIterStr3", &op_searchIterStr3))
    {
        return print_error("Keynode not found", "searchIterStr3");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("searchIterStr5", &op_searchIterStr5))
    {
        return print_error("Keynode not found", "searchIterStr5");
    }*/
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("eraseEl", &op_eraseEl))
    {
        return print_error("Keynode not found", "eraseEl");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("eraseElStr3", &op_eraseElStr3))
    {
        return print_error("Keynode not found", "eraseElStr3");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("eraseElStr5", &op_eraseElStr5))
    {
        return print_error("Keynode not found", "eraseElStr5");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("eraseSetStr3", &op_eraseSetStr3))
    {
        return print_error("Keynode not found", "eraseSetStr3");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("eraseSetStr5", &op_eraseSetStr5))
    {
        return print_error("Keynode not found", "eraseSetStr5");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ifVarAssign", &op_ifVarAssign))
    {
        return print_error("Keynode not found", "ifVarAssign");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ifFormCont", &op_ifFormCont))
    {
        return print_error("Keynode not found", "ifFormCont");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ifCoin", &op_ifCoin))
    {
        return print_error("Keynode not found", "ifCoin");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ifEq", &op_ifEq))
    {
        return print_error("Keynode not found", "ifEq");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ifGr", &op_ifGr))
    {
        return print_error("Keynode not found", "ifGr");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("ifType", &op_ifType))
    {
        return print_error("Keynode not found", "ifType");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("varAssign", &op_varAssign))
    {
        return print_error("Keynode not found", "varAssign");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contAdd", &op_contAdd))
    {
        return print_error("Keynode not found", "contAdd");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contDiv", &op_contDiv))
    {
        return print_error("Keynode not found", "contDiv");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contMult", &op_contMult))
    {
        return print_error("Keynode not found", "contMult");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contSub", &op_contSub))
    {
        return print_error("Keynode not found", "contSub");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contPow", &op_contPow))
    {
        return print_error("Keynode not found", "contPow");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contLn", &op_contLn))
    {
        return print_error("Keynode not found", "contLn");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contSin", &op_contSin))
    {
        return print_error("Keynode not found", "contSin");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contCos", &op_contCos))
    {
        return print_error("Keynode not found", "contCos");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contTg", &op_contTg))
    {
        return print_error("Keynode not found", "contTg");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contASin", &op_contASin))
    {
        return print_error("Keynode not found", "contASin");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contACos", &op_contACos))
    {
        return print_error("Keynode not found", "contACos");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contATg", &op_contATg))
    {
        return print_error("Keynode not found", "contATg");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contAssign", &op_contAssign))
    {
        return print_error("Keynode not found", "contAssign");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("contErase", &op_contErase))
    {
        return print_error("Keynode not found", "contErase");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("print", &op_print))
    {
        return print_error("Keynode not found", "print");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("printNl", &op_printNl))
    {
        return print_error("Keynode not found", "printNl");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("printEl", &op_printEl))
    {
        return print_error("Keynode not found", "printEl");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sys_search", &op_sys_search))
    {
        return print_error("Keynode not found", "sys_search");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sys_gen", &op_sys_gen))
    {
        return print_error("Keynode not found", "sys_gen");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("call", &op_call))
    {
        return print_error("Keynode not found", "call");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("waitReturn", &op_waitReturn))
    {
        return print_error("Keynode not found", "waitReturn");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("waitReturnSet", &op_waitReturnSet))
    {
        return print_error("Keynode not found", "waitReturnSet");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("return", &op_return))
    {
        return print_error("Keynode not found", "return");
    }

    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sys_set_event_handler", &op_sys_set_event_handler))
    {
        return print_error("Keynode not found", "sys_set_event_handler");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sys_delete_event_handler", &op_sys_delete_event_handler))
    {
        return print_error("Keynode not found", "sys_delete_event_handler");
    }
    if (SCP_RESULT_TRUE != scp_lib_resolve_system_identifier("sys_wait", &op_sys_wait))
    {
        return print_error("Keynode not found", "sys_wait");
    }

    return SCP_RESULT_TRUE;
}
