#include <utility>

#include <utility>

//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_LEXER_H
#define UTERM_LEXER_H

#include "Source.h"
#include "Token.h"


class Lexer {
private:
    Source source;

    Token currentToken;
    std::string currentTokenValue;

    char currentCharacter;

public:
    explicit Lexer(Source source);

    Token getNextToken();

private:
    void tryProcessingSpecialCharacter();

    void tryProcessingInternalCommand();

    void tryProcessingWord();

    void processString();

    void resetCurrentTokenState();

    void eatWhitespaces();

    void readNextChar();

    bool wasTokenTypeSelected();

    void readCharsUntilWhitespace();
};

#endif //UTERM_LEXER_H
