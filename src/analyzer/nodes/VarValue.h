//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_VARVALUE_H
#define UTERM_VARVALUE_H


#include "Value.h"

#include <utility>

struct VarValue: public Value {

    std::string name;
    std::string simpleValue;

    explicit VarValue(std::string name) : name(std::move(name)) {}

    std::string evaluate() const override {
        return simpleValue;
    }

    void accept(Visitor *visitor) override {
        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const VarValue &varValue) {
        return os << "(VarValue " << varValue.evaluate() << ")";
    }
};


#endif //UTERM_VARVALUE_H
