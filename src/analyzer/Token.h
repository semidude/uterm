//
// Created by mivine on 31.12.19.
//

#ifndef UTERM_TOKEN_H
#define UTERM_TOKEN_H

#include <string>
#include <ostream>
#include <utility>

enum TokenDescriptor {
    NONE,
    PIPE_SEPARATOR,         // expected string : "|"
    REDIRECT_LEFT,          // expected string : "<",
    REDIRECT_RIGHT,         // expected string : ">",
    ASSIGN_OPERATOR,        // expected string : "=",
    VALUE_EXTRACTOR,        // expected string : "$",
    STATEMENT_SEPARATOR,    // expected string : ";",
    APOSTROPHE,             // expected string : "'",
    NEWLINE,                // expected string : "\n",
    HERE_DOCUMENT_MARKER,   // expected string : "<<",
    EXPORT_KEYWORD,         // expected string : "export",
    DEF_KEYWORD,            // expected string : "def"
    NUMBER,                 // expected string : "\d+"
    WORD,                   // expected string : "\w+",
    STRING                  // expected string : ".+",
};

struct Token {
    TokenDescriptor descriptor;
    std::string value;

    Token(TokenDescriptor descriptor, std::string value): descriptor(descriptor), value(std::move(value)) {}

    explicit Token(TokenDescriptor descriptor): descriptor(descriptor) {}

    Token(): descriptor(TokenDescriptor::NONE) {}

    bool operator==(const Token& other) const {
        return descriptor == other.descriptor && value == other.value;
    }

    friend std::ostream& operator<<(std::ostream& out, const Token& token) {
        return out << token.descriptor << "(" << token.value << ")";
    }

    std::string toString() {
        return value;
    }
};


#endif //UTERM_TOKEN_H
