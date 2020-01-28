//
// Created by radek on 05.12.2019.
//
#include "Lexer.h"
#include <iostream>
#include <climits>

Token Lexer::getNextToken() {

    if (!source.dataAvailable()) return Token(END);

    resetCurrentTokenState();
    eatWhitespaces();
    readNextChar();

    tryProcessingSpecialCharacter();

    if (!wasTokenTypeSelected()) {

        readCharsUntilTerminalCharacter();

        tryProcessingKeyword();
        tryProcessingNumber();
        tryProcessingWord();
        processString();
    }

    return currentToken;
}

Token Lexer::getNextHereDocumentToken() {

    if (!source.dataAvailable()) requestNextLine();

    resetCurrentTokenState();
    readNextChar();

    tryProcessingNewLine();

    tryProcessingHereDocumentCmdCallOrVariableExtraction();

    if (!wasTokenTypeSelected()) {

        readCharsUntilSpecialCharOrEndOfLine();

        processString();
    }

    return currentToken;
}

void Lexer::requestNextLine() {
    std::string input;

    getline(std::cin, input);

    this->source.extendSource(input + '\n');
}

Lexer::Lexer(Source source) : source(std::move(source)) {}

void Lexer::resetCurrentTokenState() {
    currentToken = Token();
    currentTokenValue = "";
}

void Lexer::eatWhitespaces() {
    while (isspace(source.peekNextChar()) && source.peekNextChar() != '\n') {
        source.getNextChar();
    }
}

void Lexer::readNextChar() {
    currentCharacter = source.getNextChar();
    currentTokenValue += currentCharacter;
}

void Lexer::tryProcessingSpecialCharacter() {
    switch (currentCharacter) {
        case '|':
            currentToken = Token(PIPE_SEPARATOR);
            break;

        case '<':
            if (source.peekNextChar() == '<') {
                readNextChar();
                currentToken = Token(HERE_DOCUMENT_MARKER);
            } else {
                currentToken = Token(REDIRECT_LEFT);
            }
            break;

        case '>':
            currentToken = Token(REDIRECT_RIGHT);
            break;

        case '=':
            currentToken = Token(ASSIGN_OPERATOR);
            break;

        case '$':
            currentToken = Token(VALUE_EXTRACTOR);
            break;

        case ';':
            currentToken = Token(STATEMENT_SEPARATOR);
            break;

        case '\'':
            currentToken = Token(APOSTROPHE);
            break;

        case '\n': // check if NEWLINE : \n
            currentToken = Token(NEWLINE);
            break;
    }
}

void Lexer::readCharsUntilTerminalCharacter() {
    while (!isspace(source.peekNextChar()) && source.peekNextChar() != ';' && source.peekNextChar() != '\'' &&
           source.peekNextChar() != '=' && source.dataAvailable()) {
        readNextChar();
    }
}

void Lexer::readCharsUntilSpecialCharOrEndOfLine() {
    while (source.peekNextChar() != '\n' && source.dataAvailable() && source.peekNextChar() != '$') {
        readNextChar();
    }
}

void Lexer::tryProcessingKeyword() {
    if (wasTokenTypeSelected()) return;

    if (currentTokenValue == "export") {
        currentToken = Token(EXPORT_KEYWORD);
    } else if (currentTokenValue == "def") {
        currentToken = Token(DEF_KEYWORD);
    }
}

void Lexer::tryProcessingNumber() {
    if (wasTokenTypeSelected()) return;

    for (char c : currentTokenValue) {
        if (!isdigit(c)) return;
    }

    currentToken = Token(NUMBER, currentTokenValue);
}

void Lexer::tryProcessingWord() {
    if (wasTokenTypeSelected()) return;

    for (char c : currentTokenValue) {
        if (!isalnum(c) && c != '_') return;
    }

    currentToken = Token(WORD, currentTokenValue);
}

void Lexer::processString() { // if not already matched then string is only option
    if (wasTokenTypeSelected()) return;

    currentToken = Token(STRING, currentTokenValue);
}

void Lexer::tryProcessingHereDocumentCmdCallOrVariableExtraction() {
    if (currentCharacter == '$') {
        readNextChar();

        if (currentCharacter == '(') {
            readCharWhileAlphaNumeric();

            if (endsWithRightBracket()) {
                currentTokenValue = currentTokenValue.substr(2, currentTokenValue.length() - 3);
                currentToken = Token(HERE_DOCUMENT_CMD_CALL, currentTokenValue);
            }

        } else if (isalnum(currentCharacter)) {
            readCharWhileAlphaNumeric();
            currentTokenValue = currentTokenValue.substr(1);
            currentToken = Token(HERE_DOCUMENT_VARIABLE_EXTRACTION, currentTokenValue);
        }
    }
}

bool Lexer::wasTokenTypeSelected() {
    return currentToken.descriptor != NONE;
}

void Lexer::updateSource(std::string data) {
    source.updateSource(data);
}

bool Lexer::dataMissing() {
    return !source.dataAvailable();
}

bool Lexer::endsWithNewLine() {
    return source.endsWithNewLine();
}

void Lexer::readCharWhileAlphaNumeric() {
    do {
        readNextChar();
    } while (isalnum(source.peekNextChar()) && source.dataAvailable());
}

bool Lexer::endsWithRightBracket() {
    if(source.dataAvailable()) {
        readNextChar();
        if(currentCharacter == ')') {
            return true;
        }
    }
    return false;
}

void Lexer::tryProcessingNewLine() {
    if(currentCharacter == '\n') {
        currentToken = Token(NEWLINE);
    }
}
