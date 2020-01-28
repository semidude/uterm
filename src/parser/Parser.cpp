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
#include "nodes/here_document/HereDocumentElement.h"
#include "nodes/here_document/HereDocumentLine.h"

std::unique_ptr<ParseTree> Parser::parse() {

    auto parseTree = std::make_unique<ParseTree>();

    if (lexer->dataMissing()) {
        return parseTree;
    }

    do {
        advance();
        parseTree->statements.push_back(parseStatement(parseTree));
    } while (checkToken(STATEMENT_SEPARATOR));

    return parseTree;
}

std::unique_ptr<Statement> Parser::parseStatement(const std::_MakeUniq<ParseTree>::__single_object &parseTree) {

    if (checkToken(DEF_KEYWORD)) {
        return parseVarDef();
    } else {
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
    std::string cmd = requireToken(WORD, STRING).value;

    if (systemCommands.count(cmd)) {
        cmd = "/bin/" + cmd;
    }

    return cmd;
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

    std::string hdToken = requireToken(WORD).value;

    requireToken(NEWLINE, END);

    std::vector<std::shared_ptr<HereDocumentLine>> hdContents;
    std::shared_ptr<HereDocumentLine> hdLine;

    advanceHereDocument();

    while (currentToken.value != hdToken || dataAvailable()) {
        hdLine = parseHereDocumentLine();

        hdContents.push_back(std::move(hdLine));

        advanceHereDocument();
    }

    advance();

    return std::make_unique<HereDocument>(std::move(hdToken), std::move(hdContents));
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
    } else {
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
    } else {
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
        return std::make_unique<Redirection>(std::move(value), RedirectionType::LEFT);
    } else {
        requireToken(REDIRECT_RIGHT);
        auto value = parseValue();
        return std::make_unique<Redirection>(std::move(value), RedirectionType::RIGHT);
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

void Parser::advanceHereDocument() {
    currentToken = lexer->getNextHereDocumentToken();
}

bool Parser::dataAvailable() {
    return !lexer->endsWithNewLine();
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
        throw std::runtime_error("unexpected token " + getTokenName(currentToken.descriptor) + " expected: " +
                                 getTokenName(descriptor));
    }
    Token token = currentToken;
    advance();
    return token;
}

Token Parser::requireToken(TokenDescriptor first, TokenDescriptor second) {
    if (!checkToken(first, second)) {
        throw std::runtime_error(
                "unexpected token " + getTokenName(currentToken.descriptor) + " expected: " + getTokenName(first) +
                " or " +
                getTokenName(second));
    }
    Token token = currentToken;
    advance();
    return token;
}

Token Parser::requireToken(TokenDescriptor first, TokenDescriptor second, TokenDescriptor third) {
    if (!checkToken(first, second, third)) {
        throw std::runtime_error(
                "unexpected token " + getTokenName(currentToken.descriptor) + " expected: " + getTokenName(first) +
                " or " +
                getTokenName(second) + " or " +
                getTokenName(third));
    }
    Token token = currentToken;
    advance();
    return token;
}

std::string Parser::getTokenName(const TokenDescriptor descriptor) {
    std::vector<std::string> names = {"NONE", "PIPE_SEPARATOR", "REDIRECT_LEFT", "REDIRECT_RIGHT", "ASSIGN_OPERATOR",
                                      "VALUE_EXTRACTOR", "STATEMENT_SEPARATOR", "APOSTROPHE", "NEWLINE",
                                      "HERE_DOCUMENT_MARKER", "EXPORT_KEYWORD0",
                                      "DEF_KEYWORD", "NUMBER", "WORD", "STRING", "END",
                                      "HERE_DOCUMENT_VARIABLE_EXTRACTION",
                                      "HERE_DOCUMENT_CMD_CALL"};

    return names[descriptor];
}

std::shared_ptr<HereDocumentLine> Parser::parseHereDocumentLine() {
    std::vector<std::shared_ptr<HereDocumentElement>> elements;

    do {
        auto element = parseHereDocumentElement();

        elements.push_back(std::move(element));

        advanceHereDocument();
    } while (!checkToken(NEWLINE, END));

    return std::make_shared<HereDocumentLine>(std::move(elements));
}

std::shared_ptr<HereDocumentElement> Parser::parseHereDocumentElement() {
    if (checkToken(HERE_DOCUMENT_CMD_CALL)) {
        return std::make_shared<HereDocumentElement>(currentToken.value, nullptr,
                                                     std::string());
    } else if (checkToken(HERE_DOCUMENT_VARIABLE_EXTRACTION)) {
        std::shared_ptr<VarValue> variable = std::make_shared<VarValue>(currentToken.value);

        return std::make_shared<HereDocumentElement>(std::string(), variable, std::string());

    } else {
        return std::make_shared<HereDocumentElement>(std::string(), nullptr,
                                                     std::move(currentToken.value));
    }
}

