//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_CMDCALL_H
#define UTERM_CMDCALL_H


#include <string>
#include <vector>
#include <memory>
#include <zconf.h>
#include "Node.h"
#include "HereDocument.h"
#include "Value.h"

struct CmdCall: public Node {

    std::string cmd;
    std::vector<std::unique_ptr<Value>> args;
    std::unique_ptr<HereDocument> hereDocument;

    int infd = STDIN_FILENO;
    int outfd = STDOUT_FILENO;

    std::vector<const char*> evaluateArgs() {
        std::vector<const char*> evaluatedArgs;

        evaluatedArgs.push_back("grep");
        for (auto& arg : args) {
            evaluatedArgs.push_back(arg->evaluate().c_str());
        }
        evaluatedArgs.push_back(nullptr);

        return std::move(evaluatedArgs);
    }

    void accept(Visitor *visitor) override {

        for (const auto& arg : args) {
            arg->accept(visitor);
        }

        if (hereDocument != nullptr) hereDocument->accept(visitor);

        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const CmdCall &cmdCall) {
        os << "(CmdCall " << cmdCall.cmd << " ";

        for (int i = 0; i < cmdCall.args.size(); i++) {
            os << "'" << cmdCall.args[i]->evaluate() << "'";

            if (i != cmdCall.args.size() - 1) {
                os << " ";
            }
        }

        if (cmdCall.hereDocument != nullptr) {
            os << "<<" << *cmdCall.hereDocument;
        }

        return os << ")";
    }
};


#endif //UTERM_CMDCALL_H
