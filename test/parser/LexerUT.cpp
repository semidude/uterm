//
// Created by mivine on 02.01.20.
//


#define BOOST_TEST_MODULE my test suite
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#include <boost/test/unit_test.hpp>
#include "../../src/parser/Source.h"
#include "../../src/parser/Lexer.h"


BOOST_AUTO_TEST_CASE(internal_commands_test) {
    Source source = Source("export cd pwd echo exit XAXAXA");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::EXPORT_KEYWORD));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "cd"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "pwd"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "echo"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "exit"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "XAXAXA"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));
}

BOOST_AUTO_TEST_CASE(string_and_number_test) {
    Source source = Source("123 123asd ASDsdaw12 @123sadd XAXAXA0912*5 0123557687890");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NUMBER, "123"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "123asd"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "ASDsdaw12"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::STRING, "@123sadd"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::STRING, "XAXAXA0912*5"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NUMBER, "0123557687890"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));
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

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));
}

BOOST_AUTO_TEST_CASE(here_document_test) {
    Source source = Source("myprog 123 <<MARKER\ntresc here documentu\nMARKER");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "myprog"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NUMBER, "123"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::HERE_DOCUMENT_MARKER));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "MARKER"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NEWLINE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "tresc"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "here"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "documentu"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NEWLINE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "MARKER"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));
}

BOOST_AUTO_TEST_CASE(test_multiple_statements) {
    Source source = Source("myprog 123; anotherprog aaa");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "myprog"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::NUMBER, "123"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::STATEMENT_SEPARATOR));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "anotherprog"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "aaa"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));
}

BOOST_AUTO_TEST_CASE(test_quoted_string) {
    Source source = Source("'hello darkness'");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::APOSTROPHE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "hello"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "darkness"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::APOSTROPHE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));
}

BOOST_AUTO_TEST_CASE(test_variable_definition) {
    Source source = Source("ZIOMBEL='imie ziombla'");

    Lexer lexer = Lexer(source);

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "ZIOMBEL"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::ASSIGN_OPERATOR));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::APOSTROPHE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "imie"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::WORD, "ziombla"));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::APOSTROPHE));

    BOOST_CHECK_EQUAL(lexer.getNextToken(), Token(TokenDescriptor::END));

}