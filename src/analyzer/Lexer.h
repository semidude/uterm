//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_LEXER_H
#define UTERM_LEXER_H

#include "Source.h"

class Token {
private:
    TokenDescriptor descriptor;

public:
    Token(TokenDescriptor descriptor) {
        this->descriptor = descriptor;
    }

    TokenDescriptor getDescriptor() {
        return descriptor;
    }
};

enum TokenDescriptor {
    PIPE_SEPARATOR = "|",
    REDIRECT_LEFT = "<",
    REDIRECT_RIGHT = ">",
    ASSIGN_OPERATOR = "=",
    VALUE_EXTRACTOR = "$",
    EXPORT_KW = "export",
    INTERNAL_COMMAND = "cd" | "pwd" | "echo" | "exit",
    STATEMENT_SEPARATOR = ";",
    APOSTROPHE = "'",
    NEWLINE = "\n",
    HD_MARKER = "<<",
    //STRING = ".+",
    //WORD = "\w+",
    //NUMBER = \d+,
    //VAR_NAME = [a-zA-Z_]\w*,
};

class Lexer {
private:
    Source source;

public:
    Lexer(Source source) {
        this->source = source;
    }

    Token getNextToken();

private:
    bool isLetter(char c);
    bool isDigit(char c);
    bool isEOF(char c);
};

#endif //UTERM_LEXER_H
