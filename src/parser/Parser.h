//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_PARSER_H
#define UTERM_PARSER_H

#include <utility>
#include <set>

#include "ParseTree.h"
#include "nodes/Node.h"
#include "nodes/PipeCmdCall.h"
#include "Token.h"
#include "nodes/Redirection.h"
#include "nodes/Value.h"
#include "Lexer.h"
#include "nodes/RedirectedCmdCall.h"
#include "nodes/VarDef.h"

/**
 * STATEMENT = (REDIRECTED_CMD_CALL | VAR_DEF), [STATEMENT_SEPARATOR, STATEMENT]
 *
 * REDIRECTED_CMD_CALL = PIPE_CMD_CALL, [REDIRECTION]
 *
 * PIPE_CMD_CALL = CMD_CALL, [PIPE_SEPARATOR, PIPE_CMD_CALL]
 *
 * CMD_CALL = CMD, [ARGS], [HERE_DOCUMENT]
 *
 * CMD = WORD | INTERNAL_COMMAND
 *
 * ARGS = VALUE, [ARGS]
 *
 * HERE_DOCUMENT = HD_MARKER, HD_TOKEN, NEWLINE, [HD_CONTENT], NEWLINE, HD_TOKEN
 *
 * VALUE = LITERAL | VALUE_EXTRACTION
 *
 * LITERAL = NUMBER | WORD | QUOTED_STRING
 *
 * QUOTED_STRING = APOSTROPHE, STRING, APOSTROPHE
 *
 * REDIRECTION = (REDIRECT_LEFT | REDIRECT_RIGHT) TARGET
 *
 * VAR_DEF = DEF_KW, [EXPORT_KW], VAR_NAME, ASSIGN_OPERATOR, VALUE
 *
 * VALUE_EXTRACTION = VALUE_EXTRACTOR, VAR_NAME
 *
 * PIPE_SEPARATOR = "|"
 * REDIRECT_LEFT = "<"
 * REDIRECT_RIGHT = ">"
 * ASSIGN_OPERATOR = "="
 * VALUE_EXTRACTOR = "$"
 * DEF_KW = "def"
 * EXPORT_KW = "export"
 * INTERNAL_COMMAND = "cd" | "pwd" | "echo" | "exit"
 * STATEMENT_SEPARATOR = ";"
 * APOSTROPHE = "'"
 * NEWLINE = "\n"
 * HD_MARKER = "<<"
 * STRING = .+
 * WORD = \w+
 * NUMBER = \d+
 * VAR_NAME = [a-zA-Z_]\w*
 **/

class Parser {
private:
    Token currentToken;
    std::shared_ptr<Lexer> lexer;
    std::set<std::string> systemCommands = { "ls", "grep", "touch", "cat", "echo" }; //TODO add more...

public:
    explicit Parser(std::shared_ptr<Lexer> lexer): lexer(lexer) {}

    std::unique_ptr<ParseTree> parse();

private:
    std::unique_ptr<RedirectedCmdCall> parseRedirectedCmdCall();
    std::unique_ptr<PipeCmdCall> parsePipeCmdCall();
    std::unique_ptr<CmdCall> parseCmdCall();
    std::string parseCmd();
    std::vector<std::unique_ptr<Value>> parseArgs();
    std::unique_ptr<HereDocument> parseHereDocument();
    std::unique_ptr<Value> parseValue();
    std::unique_ptr<Value> parseLiteral();
    std::unique_ptr<Value> parseQuotedString();
    std::unique_ptr<Redirection> parseRedirection();
    std::unique_ptr<VarDef> parseVarDef();
    std::unique_ptr<Value> parseValueExtraction();
    std::string parseStringWithSpaces();
    bool notCmdCallTerminatingToken();

    void advance();

    bool checkToken(TokenDescriptor descriptor);
    bool checkToken(TokenDescriptor first, TokenDescriptor second);
    bool checkToken(TokenDescriptor first, TokenDescriptor second, TokenDescriptor third);

    Token requireToken(TokenDescriptor descriptor);
    Token requireToken(TokenDescriptor first, TokenDescriptor second);
    Token requireToken(TokenDescriptor first, TokenDescriptor second, TokenDescriptor third);

    std::unique_ptr<Statement> parseStatement(const std::_MakeUniq<ParseTree>::__single_object &parseTree);

    std::string getTokenName(const TokenDescriptor descriptor);
};


#endif //UTERM_PARSER_H
