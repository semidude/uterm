//
// Created by radek on 05.12.2019.
//
#include "Lexer.h"

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
            }
            else {
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
    while (!isspace(source.peekNextChar()) && source.peekNextChar() != ';' && source.peekNextChar() != '\'' && source.peekNextChar() != '=' && source.dataAvailable()) {
        readNextChar();
    }
}

void Lexer::tryProcessingKeyword() {
    if (wasTokenTypeSelected()) return;

    if (currentTokenValue == "export") {
        currentToken = Token(EXPORT_KEYWORD);
    }
    else if (currentTokenValue == "def") {
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

bool Lexer::wasTokenTypeSelected() {
    return currentToken.descriptor != NONE;
}

void Lexer::updateSource(std::string data) {
    source.updateSource(data);
}

bool Lexer::dataMissing() {
    return !source.dataAvailable();
}
