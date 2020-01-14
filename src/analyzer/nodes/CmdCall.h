//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_CMDCALL_H
#define UTERM_CMDCALL_H


#include <string>
#include <vector>
#include <memory>
#include "HereDocument.h"
#include "Value.h"

struct CmdCall {
    std::string cmd;
    std::vector<std::unique_ptr<Value>> args;
    std::unique_ptr<HereDocument> hereDocument;
};


#endif //UTERM_CMDCALL_H
