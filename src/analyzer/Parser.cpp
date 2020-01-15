//
// Created by radek on 05.12.2019.
//

#include "Parser.h"
#include "nodes/PipeCmdCall.h"
#include "Token.h"
#include "nodes/Redirection.h"
#include "nodes/Value.h"
#include "nodes/LiteralValue.h"
#include "nodes/VarValue.h"
#include "nodes/VarDef.h"
#include "nodes/Statement.h"

std::unique_ptr<ParseTree> Parser::parse() {

    auto parseTree = std::make_unique<ParseTree>();

    do {
        advance();
        parseTree->statements.push_back(parseStatement(parseTree));
    } while (checkToken(STATEMENT_SEPARATOR));

    return parseTree;
}

std::unique_ptr<Statement> Parser::parseStatement(const std::_MakeUniq<ParseTree>::__single_object &parseTree) {

    if (checkToken(DEF_KEYWORD)) {
        return parseVarDef();
    }
    else {
        return parseRedirectedCmdCall();
    }
}

std::unique_ptr<RedirectedCmdCall> Parser::parseRedirectedCmdCall() {

    auto redirectedCmdCall = std::make_unique<RedirectedCmdCall>();

    redirectedCmdCall->pipeCmdCall = parsePipeCmdCall();

    if (checkToken(REDIRECT_LEFT, REDIRECT_RIGHT)) {
        redirectedCmdCall->redirection = parseRedirection();
    }

    return redirectedCmdCall;
}

std::unique_ptr<PipeCmdCall> Parser::parsePipeCmdCall() {

    auto pipeCmdCall = std::make_unique<PipeCmdCall>();

    pipeCmdCall->cmdCall = parseCmdCall();

    if (checkToken(PIPE_SEPARATOR)) {
        requireToken(PIPE_SEPARATOR);
        pipeCmdCall->pipeChain = parsePipeCmdCall();
    }

    return pipeCmdCall;
}

std::unique_ptr<CmdCall> Parser::parseCmdCall() {

    auto cmdCall = std::make_unique<CmdCall>();

    cmdCall->cmd = parseCmd();

    if (!checkToken(PIPE_SEPARATOR)) {
        cmdCall->args = parseArgs();
    }

    if (checkToken(HERE_DOCUMENT_MARKER)) {
        cmdCall->hereDocument = parseHereDocument();
    }

    return cmdCall;
}

std::string Parser::parseCmd() {
    return requireToken(WORD).value;
}

std::vector<std::unique_ptr<Value>> Parser::parseArgs() {

    std::vector<std::unique_ptr<Value>> args;

    while (notCmdCallTerminatingToken()) {
        auto value = parseValue();
        args.push_back(std::move(value));
    }

    return args;
}

bool Parser::notCmdCallTerminatingToken() {
    return !checkToken(HERE_DOCUMENT_MARKER) &&
           !checkToken(PIPE_SEPARATOR) &&
           !checkToken(REDIRECT_LEFT) &&
           !checkToken(REDIRECT_RIGHT) &&
           !checkToken(STATEMENT_SEPARATOR) &&
           !checkToken(END);
}

std::unique_ptr<HereDocument> Parser::parseHereDocument() {

    requireToken(HERE_DOCUMENT_MARKER);
    std::string hdToken1 = requireToken(WORD).value;
    requireToken(NEWLINE);
    std::string hdContent = parseStringWithSpaces();
    requireToken(NEWLINE);
    std::string hdToken2 = requireToken(WORD).value;

    if (hdToken1 != hdToken2)
        throw std::runtime_error("Here Document begin and end tokens should be equal!");

    return std::make_unique<HereDocument>(hdToken1, hdContent);
}

std::string Parser::parseStringWithSpaces() {

    std::string result;

    while (checkToken(NUMBER, WORD, STRING)) {
        if (!result.empty()) {
            result += " ";
        }
        result += requireToken(NUMBER, WORD, STRING).value;
    }

    return result;
}

std::unique_ptr<Value> Parser::parseValue() {

    if (checkToken(VALUE_EXTRACTOR)) {
        return parseValueExtraction();
    }
    else {
        return parseLiteral();
    }
}

std::unique_ptr<Value> Parser::parseValueExtraction() {
    requireToken(VALUE_EXTRACTOR);
    std::string varName = requireToken(WORD).value;
    return std::make_unique<VarValue>(varName);
}

std::unique_ptr<Value> Parser::parseLiteral() {
    if (checkToken(APOSTROPHE)) {
        return parseQuotedString();
    }
    else {
        std::string value = requireToken(WORD, NUMBER, STRING).value;
        return std::make_unique<LiteralValue>(value);
    }
}

std::unique_ptr<Value> Parser::parseQuotedString() {
    requireToken(APOSTROPHE);
    std::string quotedString = parseStringWithSpaces();
    requireToken(APOSTROPHE);
    return std::make_unique<LiteralValue>(quotedString);
}

std::unique_ptr<Redirection> Parser::parseRedirection() {
    if (checkToken(REDIRECT_LEFT)) {
        requireToken(REDIRECT_LEFT);
        auto value = parseValue();
        return std::make_unique<Redirection>(std::move(value));
    }
    else {
        requireToken(REDIRECT_RIGHT);
        auto value = parseValue();
        return std::make_unique<Redirection>(std::move(value));
    }
}

std::unique_ptr<VarDef> Parser::parseVarDef() {
    bool exported = false;

    requireToken(DEF_KEYWORD);

    if (checkToken(EXPORT_KEYWORD)) {
        requireToken(EXPORT_KEYWORD);
        exported = true;
    }

    std::string name = requireToken(WORD).value;
    requireToken(ASSIGN_OPERATOR);
    auto value = parseValue();

    return std::make_unique<VarDef>(name, std::move(value), exported);
}

void Parser::advance() {
    currentToken = lexer->getNextToken();
}

bool Parser::checkToken(TokenDescriptor descriptor) {
    return currentToken.descriptor == descriptor;
}

bool Parser::checkToken(TokenDescriptor first, TokenDescriptor second) {
    return currentToken.descriptor == first || currentToken.descriptor == second;
}

bool Parser::checkToken(TokenDescriptor first, TokenDescriptor second, TokenDescriptor third) {
    return currentToken.descriptor == first || currentToken.descriptor == second || currentToken.descriptor == third;
}

Token Parser::requireToken(TokenDescriptor descriptor) {
    if (!checkToken(descriptor)) {
        throw std::runtime_error("unexpected token " + currentToken.toString());
    }
    Token token = currentToken;
    advance();
    return token;
}

Token Parser::requireToken(TokenDescriptor first, TokenDescriptor second) {
    if (!checkToken(first, second)) {
        throw std::runtime_error("unexpected token " + currentToken.toString());
    }
    Token token = currentToken;
    advance();
    return token;
}

Token Parser::requireToken(TokenDescriptor first, TokenDescriptor second, TokenDescriptor third) {
    if (!checkToken(first, second, third)) {
        throw std::runtime_error("unexpected token " + currentToken.toString());
    }
    Token token = currentToken;
    advance();
    return token;
}
