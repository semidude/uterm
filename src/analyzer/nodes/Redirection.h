//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_REDIRECTION_H
#define UTERM_REDIRECTION_H


#include <string>
#include <memory>
#include "Value.h"

struct Redirection {
    std::unique_ptr<Value> value;

    explicit Redirection(std::unique_ptr<Value> value) : value(std::move(value)) {}
};


#endif //UTERM_REDIRECTION_H
