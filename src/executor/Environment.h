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
    std::vector<Variable> variables;

public:
    void defineVariable(const std::string& name, std::string value, bool exported) {
        variables.push_back(Variable(name, value, exported));
    }

    std::string getValueOf(const std::string& varName) {
        for(Variable v : variables){
            if(v.getVarName() == varName)
                return v.getValue();
        }
        throw std::runtime_error("Variable with a given name not found in the environment!");
    }

    bool getExportedOf(const std::string& varName){
        for(Variable v : variables){
            if(v.getVarName() == varName)
                return v.getExported();
        }
        throw std::runtime_error("Variable with a given name not found in the environment!");
    }

    std::vector<Variable> getEnvironmentVariables(){
        return variables;
    }
};


#endif //UTERM_ENVIRONMENT_H
