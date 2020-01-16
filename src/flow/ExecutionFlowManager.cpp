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

void ExecutionFlowManager::visit(RedirectedCmdCall *redirectedCmdCall) {
    std::cout << *redirectedCmdCall << std::endl;

    if (redirectedCmdCall->redirection != nullptr) {
        //TODO zrobić przekierowanie z redirectedCmdCall->pipeCmdCall do pliku o nazwie redirectedCmdCall->redirection->getFileName()
    }
}

void ExecutionFlowManager::visit(PipeCmdCall *pipeCmdCall) {
    std::cout << *pipeCmdCall << std::endl;

    if (pipeCmdCall->pipeChain != nullptr) {
        //TODO zrobić potok z pipeCmdCall->cmdCall do pipeCmdCall->pipeChain->cmdCall
    }
}

void ExecutionFlowManager::visit(CmdCall *cmdCall) {
    std::cout << *cmdCall << std::endl;

    //TODO utworzyć proces dla cmdCall

    if (cmdCall->hereDocument != nullptr) {
        //TODO utworzyć here document i podpiąć do cmdCall
    }
}

void ExecutionFlowManager::visit(HereDocument *hereDocument) {
    std::cout << *hereDocument << std::endl;
    //chyba nic nie trzeba tu robić...
}

void ExecutionFlowManager::visit(Redirection *redirection) {
    std::cout << *redirection << std::endl;
    //chyba nic nie trzeba tu robić...
}

void ExecutionFlowManager::visit(VarDef *varDef) {

    env->defineVariable(varDef->name, varDef->value->evaluate());

    std::cout << *varDef << std::endl;
}

void ExecutionFlowManager::visit(VarValue *varValue) {

    varValue->simpleValue = env->getValueOf(varValue->name);

    std::cout << *varValue << std::endl;
}

void ExecutionFlowManager::visit(LiteralValue *literalValue) {
    std::cout << *literalValue << std::endl;
    //chyba nic nie trzeba tu robić...
}
