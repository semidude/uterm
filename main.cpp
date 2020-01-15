#include <iostream>
#include <memory>
#include "src/analyzer/Source.h"
#include "src/analyzer/Lexer.h"
#include "src/analyzer/Parser.h"

int main() {

//    std::string command;
//    std::cout << "=== uterm, a simple terminal ===" << std::endl;
//    std::cout << "$ ";
//    std::cin >> command;

    Source source("myprog 123 koles <<MARKER\ntresc here documentu\nMARKER | grep ziombel > jakis_pliczek_ziombla.txt; jakis_koles 'witaj gosciu'; def export ZIOMBEL='imie ziombla'");
    auto lexer = std::make_unique<Lexer>(source);

    auto parser = std::make_unique<Parser>(std::move(lexer));

    auto parseTree = parser->parse();

    std::cout << parseTree->statements[0]->redirection->value->evaluate();

    return 0;
}