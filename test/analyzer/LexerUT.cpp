//
// Created by mivine on 02.01.20.
//


#define BOOST_TEST_MODULE my test suite
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#include <boost/test/unit_test.hpp>


#include "../../src/analyzer/Source.h"
#include "../../src/analyzer/Lexer.h"


BOOST_AUTO_TEST_CASE(internal_commands_test) {
    Source source = Source("export cd pwd echo exit XAXAXA");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::EXPORT_KEYWORD));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::CD_COMMAND));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::PWD_COMMAND));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::ECHO_COMMAND));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::EXIT_COMMAND));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "XAXAXA"));
}

BOOST_AUTO_TEST_CASE(string_and_number_test) {
    Source source = Source("123 123asd ASDsdaw12 @123sadd XAXAXA0912*5 0123557687890");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "123"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "123asd"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "ASDsdaw12"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::STRING, "@123sadd"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::STRING, "XAXAXA0912*5"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "0123557687890"));
}

BOOST_AUTO_TEST_CASE(special_chars_test) {
    Source source = Source("| < > << = $ ; '\n");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::PIPE_SEPARATOR));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::REDIRECT_LEFT));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::REDIRECT_RIGHT));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::HERE_DOCUMENT_MARKER));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::ASSIGN_OPERATOR));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::VALUE_EXTRACTOR));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::STATEMENT_SEPARATOR));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::APOSTROPHE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NEWLINE));
}