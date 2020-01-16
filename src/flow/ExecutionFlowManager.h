//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_EXECUTIONFLOWMANAGER_H
#define UTERM_EXECUTIONFLOWMANAGER_H


#include <vector>
#include "../analyzer/Visitor.h"
#include "Environment.h"
#include "../util/Pipe.h"

class ExecutionFlowManager: public Visitor {
private:
    Environment *env;
    std::vector<Pipe> pipes;

public:
    explicit ExecutionFlowManager(Environment *env) : env(env) {}

    void visit(RedirectedCmdCall *redirectedCmdCall) override;

    void visit(PipeCmdCall *pipeCmdCall) override;

    void visit(CmdCall *cmdCall) override;

    void visit(HereDocument *hereDocument) override;

    void visit(Redirection *redirection) override;

    void visit(VarDef *varDef) override;

    void visit(VarValue *varValue) override;

    void visit(LiteralValue *literalValue) override;
};


#endif //UTERM_EXECUTIONFLOWMANAGER_H
