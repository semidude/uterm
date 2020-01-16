//
// Created by slighten on 16.01.2020.
//

// #define BOOST_TEST_MODULE my test suite
// #define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../src/parser/Source.h"
#include "../../src/parser/Lexer.h"
#include "../../src/parser/Parser.h"
#include "../../src/flow/CommandExecutor.h"
#include "../../src/executor/CommandExecutor.h"

BOOST_AUTO_TEST_CASE(dummy_parser_test) {
    Source source("cat sample | grep abc > fajl.txt; mkdir ujebanekolosy; def ELKA='chujnia z grzybnia'");

    auto lexer = std::make_unique<Lexer>(source);

    auto parser = std::make_unique<Parser>(std::move(lexer));

    auto parseTree = parser->parse();

    //BOOST_CHECK_EQUAL(parseTree->statements.at(0), Statement());
}
