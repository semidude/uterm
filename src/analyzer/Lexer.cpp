//
// Created by radek on 05.12.2019.
//
#include "Lexer.h"

Token Lexer::getNextToken() {

    resetCurrentTokenState();
    eatWhitespaces();
    readNextChar();

    tryProcessingSpecialCharacter();

    readCharsUntilWhitespace();

    tryProcessingInternalCommand();
    tryProcessingNumber();
    tryProcessingWord();
    processString();

    return currentToken;
}

Lexer::Lexer(Source source)
        : source(std::move(source)) {
}

void Lexer::tryProcessingSpecialCharacter() {
    switch (currentCharacter) {
        case '|':
            currentToken = Token(TokenDescriptor::PIPE_SEPARATOR);
            break;

        case '<':
            if (source.peekNextChar() == '<') {
                readNextChar();
                currentToken = Token(TokenDescriptor::HERE_DOCUMENT_MARKER);
            } else {
                currentToken = Token(TokenDescriptor::REDIRECT_LEFT);
            }
            break;

        case '>':
            currentToken = Token(TokenDescriptor::REDIRECT_RIGHT);
            break;

        case '=':
            currentToken = Token(TokenDescriptor::ASSIGN_OPERATOR);
            break;

        case '$':
            currentToken = Token(TokenDescriptor::VALUE_EXTRACTOR);
            break;

        case ';':
            currentToken = Token(TokenDescriptor::STATEMENT_SEPARATOR);
            break;

        case '\'':
            currentToken = Token(TokenDescriptor::APOSTROPHE);
            break;

        case '\n': // check if NEWLINE : \n
            currentToken = Token(TokenDescriptor::NEWLINE);
            break;
    }
}

void Lexer::tryProcessingInternalCommand() {
    if (wasTokenTypeSelected()) return;

    if (currentTokenValue == "export") {
        currentToken = Token(TokenDescriptor::EXPORT_KEYWORD);
    } else if (currentTokenValue == "cd") {
        currentToken = Token(TokenDescriptor::CD_COMMAND);
    } else if (currentTokenValue == "pwd") {
        currentToken = Token(TokenDescriptor::PWD_COMMAND);
    } else if (currentTokenValue == "echo") {
        currentToken = Token(TokenDescriptor::ECHO_COMMAND);
    } else if (currentTokenValue == "exit") {
        currentToken = Token(TokenDescriptor::EXIT_COMMAND);
    }
}

void Lexer::tryProcessingNumber() {
    if (wasTokenTypeSelected()) return;

    for (char c : currentTokenValue) {
        if (!isdigit(c)) return;
    }

    currentToken = Token(TokenDescriptor::NUMBER);
}

void Lexer::tryProcessingWord() {
    if (wasTokenTypeSelected()) return;

    for (char c : currentTokenValue) {
        if (!isalnum(c)) return;
    }

    currentToken = Token(TokenDescriptor::WORD);
}

void Lexer::processString() { // if not already matched then string is only option
    if (wasTokenTypeSelected()) return;

    currentToken = Token(TokenDescriptor::STRING);
}

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

bool Lexer::wasTokenTypeSelected() {
    return currentToken.getDescriptor() != TokenDescriptor::NONE;
}

void Lexer::readCharsUntilWhitespace() {
    while (!isspace(source.peekNextChar()) && source.dataAvailable()) {
        readNextChar();
    }
}
