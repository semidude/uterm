//
// Created by mivine on 31.12.19.
//

#include "Token.h"

Token::Token(TokenDescriptor descriptor, std::string tokenValue) {
    this->descriptor = descriptor;
    this->value = tokenValue;
}

Token::Token(TokenDescriptor descriptor) {
    this->descriptor = descriptor;
}

TokenDescriptor Token::getDescriptor() {
    return descriptor;
}

Token::Token() {
    this->descriptor = TokenDescriptor::NONE;
};
