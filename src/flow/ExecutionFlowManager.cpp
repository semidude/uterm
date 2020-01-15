//
// Created by radek on 05.12.2019.
//

#include <iostream>
#include "ExecutionFlowManager.h"
#include "../analyzer/nodes/VarDef.h"
#include "../analyzer/nodes/RedirectedCmdCall.h"
#include "../analyzer/nodes/PipeCmdCall.h"
#include "../analyzer/nodes/CmdCall.h"
#include "../analyzer/nodes/HereDocument.h"
#include "../analyzer/nodes/Redirection.h"
#include "../analyzer/nodes/LiteralValue.h"
#include "../analyzer/nodes/VarValue.h"

void ExecutionFlowManager::visit(VarDef *varDef) {
    std::cout << "varDef (" << varDef->varName << ")" << std::endl;
}

void ExecutionFlowManager::visit(RedirectedCmdCall *redirectedCmdCall) {
    std::cout << "redirectedCmdCall (" << redirectedCmdCall->pipeCmdCall->cmdCall->cmd << ")" << std::endl;
}

void ExecutionFlowManager::visit(PipeCmdCall *pipeCmdCall) {
    std::cout << "pipeCmdCall (" << pipeCmdCall->cmdCall->cmd << ")" << std::endl;
}

void ExecutionFlowManager::visit(CmdCall *cmdCall) {
    std::cout << "cmdCall (" << cmdCall->cmd << ")" << std::endl;
}

void ExecutionFlowManager::visit(HereDocument *hereDocument) {
    std::cout << "hereDocument (" << hereDocument->hdToken << " " << hereDocument->hdContent << " " << hereDocument->hdToken << ")" << std::endl;
}

void ExecutionFlowManager::visit(Redirection *redirection) {
    std::cout << "redirection (" << redirection->value->evaluate() << ")" << std::endl;
}

void ExecutionFlowManager::visit(LiteralValue *literalValue) {
    std::cout << "literalValue (" << literalValue->evaluate() << ")" << std::endl;
}

void ExecutionFlowManager::visit(VarValue *varValue) {
    std::cout << "varValue.(.." << varValue->evaluate() << ")" << std::endl;
}
