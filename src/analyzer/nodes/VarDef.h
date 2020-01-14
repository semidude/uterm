//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_VARDEF_H
#define UTERM_VARDEF_H


#include <string>
#include <memory>
#include <utility>
#include "Value.h"

struct VarDef {
    std::string varName;
    std::unique_ptr<Value> value;
    bool exported;

    VarDef(std::string varName, std::unique_ptr<Value> value, bool exported) : varName(std::move(varName)),
                                                                               value(std::move(value)),
                                                                               exported(exported) {}
};


#endif //UTERM_VARDEF_H
