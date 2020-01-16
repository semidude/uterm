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
    std::string name;
    std::unique_ptr<Value> value;
    bool exported;

    VarDef(std::string varName, std::unique_ptr<Value> value, bool exported) : name(std::move(varName)),
                                                                               value(std::move(value)),
                                                                               exported(exported) {}

    void accept(Visitor *visitor) override {

        value->accept(visitor);

        visitor->visit(this);
    }

    friend std::ostream& operator<<(std::ostream& os, const VarDef& varDef) {
        return os << "(VarDef " << varDef.name << " = " << varDef.value->evaluate() << ")";
    }
};


#endif //UTERM_VARDEF_H
