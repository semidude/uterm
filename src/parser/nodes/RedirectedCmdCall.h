//
// Created by Radoslaw Panuszewski on 1/15/20.
//

#ifndef UTERM_REDIRECTEDCMDCALL_H
#define UTERM_REDIRECTEDCMDCALL_H


#include "PipeCmdCall.h"
#include "Redirection.h"
#include "Statement.h"

struct RedirectedCmdCall: public Statement {

    std::unique_ptr<PipeCmdCall> pipeCmdCall;
    std::unique_ptr<Redirection> redirection;

    void accept(Visitor *visitor) override {

        visitor->visit(this); //save output to file after command execution has completed

        pipeCmdCall->accept(visitor);

        if (redirection != nullptr) redirection->accept(visitor);

    }

    friend std::ostream &operator<<(std::ostream &os, const RedirectedCmdCall &redirectedCmdCall) {
        os << "(RedirectedCmdCall " << *redirectedCmdCall.pipeCmdCall;

        if (redirectedCmdCall.redirection != nullptr) {
            os << " > " << redirectedCmdCall.redirection->getFileName();
        }

        return os << ")";
    }
};


#endif //UTERM_REDIRECTEDCMDCALL_H
