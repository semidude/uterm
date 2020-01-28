//
// Created by radek on 16.01.2020.
//

#ifndef UTERM_ENVIRONMENT_H
#define UTERM_ENVIRONMENT_H


#include <map>
#include <utility>
#include "../parser/nodes/Variable.h"

class Environment {
private:
    std::map<std::string, Variable> variables;

public:
    void defineVariable(const std::string &name, std::string value, bool exported) {
        variables[name] = (Variable(name, std::move(value), exported));
    }

    Variable getVariableOfName(const std::string &varName) {
        if (variables.count(varName) == 0) {
            throw std::runtime_error("Variable with a given name not found in the environment!");
        }
        return variables[varName];
    }

    std::vector<Variable> getEnvironmentVariables(){
        std::vector<Variable> v;

        for(const std::pair<std::string, Variable>& pair : variables) {
            v.push_back(pair.second);
        }
        return v;
    }
};


#endif //UTERM_ENVIRONMENT_H
