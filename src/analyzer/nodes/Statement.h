//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_STATEMENT_H
#define UTERM_STATEMENT_H


#include "PipeCmdCall.h"
#include "VarDef.h"

class Statement {
public:
    std::unique_ptr<PipeCmdCall> pipeCmdCall;
    std::unique_ptr<Redirection> redirection;
    std::unique_ptr<VarDef> varDef;
};


#endif //UTERM_STATEMENT_H
