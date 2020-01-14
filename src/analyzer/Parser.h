//
// Created by radek on 05.12.2019.
//

#ifndef UTERM_PARSER_H
#define UTERM_PARSER_H

#include <utility>

#include "ParseTree.h"
#include "nodes/Node.h"
#include "nodes/PipeCmdCall.h"
#include "Token.h"
#include "nodes/Redirection.h"
#include "nodes/Value.h"
#include "Lexer.h"

/**
 * STATEMENT = VAR_DEF | (PIPE_CMD_CALL, [REDIRECTION]), [STATEMENT_SEPARATOR, STATEMENT]
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
    std::unique_ptr<Lexer> lexer;

public:
    explicit Parser(std::unique_ptr<Lexer> lexer): lexer(std::move(lexer)) {}

    std::unique_ptr<ParseTree> parse();

private:
    std::unique_ptr<Statement> parseStatement();
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

    void advance();

    bool checkToken(TokenDescriptor descriptor);
    bool checkToken(TokenDescriptor first, TokenDescriptor second);

    Token requireToken(TokenDescriptor descriptor);
    Token requireToken(TokenDescriptor first, TokenDescriptor second);
};


#endif //UTERM_PARSER_H
