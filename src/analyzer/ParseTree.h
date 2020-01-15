//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_PARSETREE_H
#define UTERM_PARSETREE_H


#include <vector>
#include <memory>
#include "nodes/Node.h"
#include "nodes/Statement.h"

struct ParseTree: public Node {

    std::vector<std::unique_ptr<Statement>> statements;

    void accept(Visitor *visitor) override {

        for (const auto& statement : statements) {
            statement->accept(visitor);
        }
    }
};


#endif //UTERM_PARSETREE_H
