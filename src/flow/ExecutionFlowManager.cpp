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
    std::cout << *varDef;
}

void ExecutionFlowManager::visit(RedirectedCmdCall *redirectedCmdCall) {
    std::cout << *redirectedCmdCall;
}

void ExecutionFlowManager::visit(PipeCmdCall *pipeCmdCall) {
    std::cout << *pipeCmdCall;
}

void ExecutionFlowManager::visit(CmdCall *cmdCall) {
    std::cout << *cmdCall;
}

void ExecutionFlowManager::visit(HereDocument *hereDocument) {
    std::cout << *hereDocument;
}

void ExecutionFlowManager::visit(Redirection *redirection) {
    std::cout << *redirection;
}

void ExecutionFlowManager::visit(LiteralValue *literalValue) {
    std::cout << *literalValue;
}

void ExecutionFlowManager::visit(VarValue *varValue) {
    std::cout << *varValue;
}
