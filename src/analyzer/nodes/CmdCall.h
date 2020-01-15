//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_CMDCALL_H
#define UTERM_CMDCALL_H


#include <string>
#include <vector>
#include <memory>
#include "Node.h"
#include "HereDocument.h"
#include "Value.h"

struct CmdCall: public Node {
    std::string cmd;
    std::vector<std::unique_ptr<Value>> args;
    std::unique_ptr<HereDocument> hereDocument;

    void accept(Visitor *visitor) override {

        visitor->visit(this);

        for (const auto& arg : args) {
            arg->accept(visitor);
        }

        if (hereDocument != nullptr) hereDocument->accept(visitor);
    }

    friend std::ostream &operator<<(std::ostream &os, const CmdCall &cmdCall) {
        return os << "cmdCall (" << cmdCall.cmd << ")" << std::endl;
    }
};


#endif //UTERM_CMDCALL_H
