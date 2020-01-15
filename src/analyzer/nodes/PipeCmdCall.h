//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_PIPECMDCALL_H
#define UTERM_PIPECMDCALL_H


#include <bits/unique_ptr.h>
#include "Redirection.h"
#include "CmdCall.h"

class PipeCmdCall {
public:
    std::unique_ptr<CmdCall> cmdCall;
    std::unique_ptr<PipeCmdCall> pipeChain;
};


#endif //UTERM_PIPECMDCALL_H
