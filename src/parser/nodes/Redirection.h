//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_REDIRECTION_H
#define UTERM_REDIRECTION_H


#include <string>
#include <memory>
#include <ostream>
#include "Value.h"

enum RedirectionType {
    LEFT, RIGHT
};

struct Redirection : public Node {
    std::unique_ptr<Value> value;
    RedirectionType redirectionType;

    explicit Redirection(std::unique_ptr<Value> value, RedirectionType redirectionType)
            : value(std::move(value)), redirectionType(redirectionType) {}

    std::string getFileName() {
        return value->evaluate();
    }

    void accept(Visitor *visitor) override {

        value->accept(visitor);

        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Redirection &redirection) {
        return os << "(Redirection " << redirection.value->evaluate() << ")";
    }
};


#endif //UTERM_REDIRECTION_H
