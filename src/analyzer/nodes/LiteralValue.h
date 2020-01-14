//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_LITERALVALUE_H
#define UTERM_LITERALVALUE_H


#include "Value.h"

#include <utility>

class LiteralValue : public Value {
private:
    std::string value;

public:
    explicit LiteralValue(std::string value): value(std::move(value)) {}

private:

    std::string evaluate() override {
        return value;
    }
};


#endif //UTERM_LITERALVALUE_H
