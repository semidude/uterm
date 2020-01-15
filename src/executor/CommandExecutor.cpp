//
// Created by radek on 05.12.2019.
//

#include "CommandExecutor.h"
#include "../analyzer/nodes/VarDef.h"
#include "../analyzer/nodes/RedirectedCmdCall.h"
#include "../analyzer/nodes/PipeCmdCall.h"
#include "../analyzer/nodes/CmdCall.h"
#include "../analyzer/nodes/HereDocument.h"
#include "../analyzer/nodes/Redirection.h"
#include "../analyzer/nodes/LiteralValue.h"
#include "../analyzer/nodes/VarValue.h"

void CommandExecutor::visit(VarDef *varDef) {

}

void CommandExecutor::visit(RedirectedCmdCall *redirectedCmdCall) {

}

void CommandExecutor::visit(PipeCmdCall *pipeCmdCall) {

}

void CommandExecutor::visit(CmdCall *cmdCall) {

}

void CommandExecutor::visit(HereDocument *hereDocument) {

}

void CommandExecutor::visit(Redirection *redirection) {

}

void CommandExecutor::visit(LiteralValue *literalValue) {

}

void CommandExecutor::visit(VarValue *varValue) {

}
