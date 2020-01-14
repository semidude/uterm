//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_VARIABLEVALUE_H
#define UTERM_VARIABLEVALUE_H


#include "Value.h"

#include <utility>

class VariableValue: public Value {
private:
    std::string varName;

public:
    explicit VariableValue(std::string varName) : varName(std::move(varName)) {}

    std::string evaluate() override {

    }
};


#endif //UTERM_VARIABLEVALUE_H
