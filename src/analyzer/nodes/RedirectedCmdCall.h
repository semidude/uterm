//
// Created by Radoslaw Panuszewski on 1/15/20.
//

#ifndef UTERM_REDIRECTEDCMDCALL_H
#define UTERM_REDIRECTEDCMDCALL_H


#include "Statement.h"

struct RedirectedCmdCall : public Statement {
    std::unique_ptr<PipeCmdCall> pipeCmdCall;
    std::unique_ptr<Redirection> redirection;
};


#endif //UTERM_REDIRECTEDCMDCALL_H
