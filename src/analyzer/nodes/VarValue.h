//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_VARVALUE_H
#define UTERM_VARVALUE_H


#include "Value.h"

#include <utility>

class VarValue: public Value {
private:
    std::string varName;

public:
    explicit VarValue(std::string varName) : varName(std::move(varName)) {}

    std::string evaluate() const override {
        return ""; //TODO...
    }

    void accept(Visitor *visitor) override {
        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const VarValue &varValue) {
        return os << "varValue.(.." << varValue.evaluate() << ")" << std::endl;
    }
};


#endif //UTERM_VARVALUE_H