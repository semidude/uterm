//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_VALUE_H
#define UTERM_VALUE_H


#include <string>

enum ValueType {STRING_VALUE, NUMBER_VALUE};

struct Value: public Node {

    virtual std::string evaluate() = 0;
};


#endif //UTERM_VALUE_H
