//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_COMMANDEXECUTOR_H
#define UTERM_COMMANDEXECUTOR_H


#include <vector>
#include "../parser/Visitor.h"
#include "Environment.h"
#include "Pipe.h"

class CommandExecutor: public Visitor {
private:
    Environment *env;
    std::vector<int> openDescriptors;

public:
    explicit CommandExecutor(Environment *env) : env(env) {}

    void visit(RedirectedCmdCall *redirectedCmdCall) override;

    void visit(PipeCmdCall *pipeCmdCall) override;

    void visit(CmdCall *cmdCall) override;

    void visit(HereDocument *hereDocument) override;

    void visit(Redirection *redirection) override;

    void visit(VarDef *varDef) override;

    void visit(VarValue *varValue) override;

    void visit(LiteralValue *literalValue) override;

    void printWorkingDirectory() const;

    void executeExternalProgram(const CmdCall *cmdCall, std::vector<const char*> args) const;

    void changeDirectory(std::vector<const char *> args) const;

    std::vector<const char *> getArgs(const CmdCall *cmdCall) const;
};


#endif //UTERM_COMMANDEXECUTOR_H
