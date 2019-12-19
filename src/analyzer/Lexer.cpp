//
// Created by radek on 05.12.2019.
//
#include "Lexer.h"

Token Lexer::getNextToken() {

    char c = source.getNextChar();

    if (isDigit(c)) {
        processDigit(c);
    }
    else if (isLetter(c)) {
        processLetter(c);
    }
    else if (isEOF(c)) {
        processEOF(c);
    }
    else {
        processSpecialCharacter();
    }
}