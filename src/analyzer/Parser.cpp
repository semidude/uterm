//
// Created by radek on 05.12.2019.
//
#include "Parser.h"
#include "nodes/PipeCmdCall.h"
#include "Token.h"
#include "nodes/Redirection.h"
#include "nodes/Statement.h"
#include "nodes/Value.h"
#include "nodes/LiteralValue.h"
#include "nodes/VariableValue.h"

std::unique_ptr<ParseTree> Parser::parse() {

    auto parseTree = std::make_unique<ParseTree>();

    advance();
    do {
        parseTree->statements.push_back(parseStatement());
    } while (checkToken(STATEMENT_SEPARATOR));

    return parseTree;
}

std::unique_ptr<Statement> Parser::parseStatement() {

    auto statement = std::make_unique<Statement>();

    if (checkToken(DEF_KEYWORD)) {
        statement->varDef = parseVarDef();
    }
    else {
        statement->pipeCmdCall = parsePipeCmdCall();

        if (checkToken(REDIRECT_LEFT, REDIRECT_RIGHT)) {
            statement->redirection = parseRedirection();
        }
    }
    return statement;
}

std::unique_ptr<PipeCmdCall> Parser::parsePipeCmdCall() {

    auto pipeCmdCall = std::make_unique<PipeCmdCall>();

    pipeCmdCall->cmdCall = parseCmdCall();

    if (checkToken(PIPE_SEPARATOR)) {
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

    if (!checkToken(PIPE_SEPARATOR)) {
        cmdCall->hereDocument = parseHereDocument();
    }

    return cmdCall;
}

std::string Parser::parseCmd() {
    return requireToken(WORD).value;
}

std::vector<std::unique_ptr<Value>> Parser::parseArgs() {

    std::vector<std::unique_ptr<Value>> args;

    while (checkToken(WORD, NUMBER)) {
        auto value = parseValue();
        args.push_back(std::move(value));
    }

    return args;
}

std::unique_ptr<HereDocument> Parser::parseHereDocument() {

    requireToken(HERE_DOCUMENT_MARKER);
    auto hdToken1 = requireToken(WORD);
    requireToken(NEWLINE);
    auto hdContent = requireToken(STRING);
    requireToken(NEWLINE);
    auto hdToken2 = requireToken(WORD);

    if (hdToken1.value != hdToken2.value)
        throw std::runtime_error("Here Document begin and end tokens should be equal!");

    return std::make_unique<HereDocument>(hdToken1.value, hdContent.value);
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
    return std::make_unique<VariableValue>(varName);
}

std::unique_ptr<Value> Parser::parseLiteral() {
    if (checkToken(APOSTROPHE)) {
        return parseQuotedString();
    }
    else {
        auto token = requireToken(WORD, NUMBER);
        return std::make_unique<LiteralValue>(token.value);
    }
}

std::unique_ptr<Value> Parser::parseQuotedString() {
    requireToken(APOSTROPHE);
    std::string quotedString = requireToken(STRING).value;
    requireToken(APOSTROPHE);
    return std::make_unique<LiteralValue>(quotedString);
}

std::unique_ptr<Redirection> Parser::parseRedirection() {
    if (checkToken(REDIRECT_LEFT)) {
        requireToken(REDIRECT_LEFT);
        auto value = parseValue();
        std::make_unique<Redirection>(std::move(value));
    }
    else {
        requireToken(REDIRECT_RIGHT);
        auto value = parseValue();
        std::make_unique<Redirection>(std::move(value));
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