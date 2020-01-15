//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_REDIRECTION_H
#define UTERM_REDIRECTION_H


#include <string>
#include <memory>
#include <ostream>
#include "Value.h"

struct Redirection: public Node {
    std::unique_ptr<Value> value;

    explicit Redirection(std::unique_ptr<Value> value) : value(std::move(value)) {}

    void accept(Visitor *visitor) override {
        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Redirection &redirection) {
        return os << "redirection (" << redirection.value->evaluate() << ")" << std::endl;
    }
};


#endif //UTERM_REDIRECTION_H
