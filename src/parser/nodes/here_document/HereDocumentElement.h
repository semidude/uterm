//
// Created by mivine on 27.01.20.
//

#ifndef UTERM_HEREDOCUMENTELEMENT_H
#define UTERM_HEREDOCUMENTELEMENT_H

#include <string>
#include <utility>
#include <memory>
#include "../Node.h"
#include "../VarValue.h"

struct HereDocumentElement: public Node {
    std::string cmdCall;

    std::shared_ptr<VarValue> variable;

    std::string text;

    HereDocumentElement(std::string cmdCall, std::shared_ptr<VarValue> variable, std::string text)
    : cmdCall(std::move(cmdCall)), variable(std::move(variable)), text(std::move(text)) {}

    void accept(Visitor *visitor) override {
        visitor->visit(this);
    }
};


#endif //UTERM_HEREDOCUMENTELEMENT_H
