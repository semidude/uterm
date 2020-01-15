//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_VARDEF_H
#define UTERM_VARDEF_H


#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include "Statement.h"
#include "Value.h"

struct VarDef: public Statement {
    std::string varName;
    std::unique_ptr<Value> value;
    bool exported;

    VarDef(std::string varName, std::unique_ptr<Value> value, bool exported) : varName(std::move(varName)),
                                                                               value(std::move(value)),
                                                                               exported(exported) {}

    void accept(Visitor *visitor) override {
        visitor->visit(this);
        value->accept(visitor);
    }

    friend std::ostream& operator<<(std::ostream& os, const VarDef& varDef) {
        return os << "varDef (" << varDef.varName << " = " << varDef.value->evaluate() << ")" << std::endl;
    }
};


#endif //UTERM_VARDEF_H
