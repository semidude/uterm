//
// Created by radek on 16.01.2020.
//

#ifndef UTERM_ENVIRONMENT_H
#define UTERM_ENVIRONMENT_H


#include <map>
#include <utility>

class Environment {
private:
    std::map<std::string, std::string> variables;

public:
    void defineVariable(const std::string& name, std::string value) {
        variables[name] = std::move(value);
    }

    std::string getValueOf(const std::string& varName) {
        return variables[varName];
    }
};


#endif //UTERM_ENVIRONMENT_H
