//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_PARSETREE_H
#define UTERM_PARSETREE_H


#include <vector>
#include <memory>
#include "nodes/Statement.h"

struct ParseTree {
    std::vector<std::unique_ptr<Statement>> statements;
};


#endif //UTERM_PARSETREE_H
