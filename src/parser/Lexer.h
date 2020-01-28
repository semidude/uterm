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

    bool endsWithNewLine();

    Token getNextToken();

    Token getNextHereDocumentToken();

    bool dataMissing();

    void updateSource(std::string data);

private:
    void requestNextLine();

    void tryProcessingSpecialCharacter();

    void tryProcessingKeyword();

    void tryProcessingNumber();

    void tryProcessingWord();

    void processString();

    void resetCurrentTokenState();

    void eatWhitespaces();

    void readNextChar();

    bool wasTokenTypeSelected();

    void readCharsUntilTerminalCharacter();

    void tryProcessingHereDocumentCmdCallOrVariableExtraction();

    void readCharsUntilSpecialCharOrEndOfLine();

    void readCharWhileAlphaNumeric();

    bool endsWithRightBracket();

    void tryProcessingNewLine();

    void readCharWhileAlphaNumericOrSlash();
};

#endif //UTERM_LEXER_H
