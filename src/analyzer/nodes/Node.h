//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_NODE_H
#define UTERM_NODE_H


#include "../Visitor.h"

struct Node {
    virtual void accept(Visitor *visitor) = 0;
};


#endif //UTERM_NODE_H
