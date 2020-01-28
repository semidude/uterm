//
// Created by slighten on 28.01.2020.
//

#ifndef UTERM_VARIABLE_H
#define UTERM_VARIABLE_H


#include <string>

class Variable{
private:
    std::string name;
    std::string value;
    bool exported;
public:
    Variable(std::string name, std::string value, bool exported) : name(std::move(name)), value(std::move(value)), exported(exported){}

    std::string getVarName(){
        return name;
    }
    std::string getValue(){
        return value;
    }
    bool getExported(){
        return exported;
    }
};

#endif //UTERM_VARIABLE_H
