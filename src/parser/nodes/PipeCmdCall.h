//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_PIPECMDCALL_H
#define UTERM_PIPECMDCALL_H


#include <bits/unique_ptr.h>
#include "Redirection.h"
#include "CmdCall.h"
#include "Node.h"

struct PipeCmdCall: public Node {

    std::unique_ptr<CmdCall> cmdCall;
    std::unique_ptr<PipeCmdCall> pipeChain;

    int infd = STDIN_FILENO;
    int outfd = STDOUT_FILENO;

    void accept(Visitor *visitor) override {

        visitor->visit(this); //create the pipe before spawning child processes

        cmdCall->accept(visitor);

        if (pipeChain != nullptr) pipeChain->accept(visitor);
    }

    friend std::ostream &operator<<(std::ostream &os, const PipeCmdCall &pipeCmdCall) {
        os << "(PipeCmdCall " << *pipeCmdCall.cmdCall;

        if (pipeCmdCall.pipeChain != nullptr) {
            os << " | " << *pipeCmdCall.pipeChain;
        }

        os << ")";
        return os;
    }
};


#endif //UTERM_PIPECMDCALL_H
