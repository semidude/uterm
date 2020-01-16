//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_COMMANDEXECUTOR_H
#define UTERM_COMMANDEXECUTOR_H


#include "../analyzer/Visitor.h"

class CommandExecutor: public Visitor {

public:
    void visit(RedirectedCmdCall *redirectedCmdCall) override;

    void visit(PipeCmdCall *pipeCmdCall) override;

    void visit(CmdCall *cmdCall) override;

    void visit(HereDocument *hereDocument) override;

    void visit(Redirection *redirection) override;

    void visit(VarDef *varDef) override;

    void visit(VarValue *varValue) override;

    void visit(LiteralValue *literalValue) override;
};


#endif //UTERM_COMMANDEXECUTOR_H
