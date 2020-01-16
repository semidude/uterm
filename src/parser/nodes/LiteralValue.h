//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_LITERALVALUE_H
#define UTERM_LITERALVALUE_H


#include "Value.h"

#include <utility>

class LiteralValue: public Value {
private:
    std::string value;

public:
    explicit LiteralValue(std::string value): value(std::move(value)) {}

    std::string evaluate() const override {
        return value;
    }

    void accept(Visitor *visitor) override {
        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const LiteralValue &literalValue) {
        return os << "(LiteralValue " << literalValue.evaluate() << ")";
    }
};


#endif //UTERM_LITERALVALUE_H
