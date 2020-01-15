//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_EXECUTIONFLOWMANAGER_H
#define UTERM_EXECUTIONFLOWMANAGER_H


#include "../analyzer/Visitor.h"

class ExecutionFlowManager: public Visitor {

public:
    void visit(VarDef *varDef) override;

    void visit(RedirectedCmdCall *redirectedCmdCall) override;

    void visit(PipeCmdCall *pipeCmdCall) override;

    void visit(CmdCall *cmdCall) override;

    void visit(HereDocument *hereDocument) override;

    void visit(Redirection *redirection) override;

    void visit(LiteralValue *literalValue) override;

    void visit(VarValue *varValue) override;
};


#endif //UTERM_EXECUTIONFLOWMANAGER_H
