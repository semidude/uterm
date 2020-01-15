#include <iostream>
#include <memory>
#include "src/analyzer/Source.h"
#include "src/analyzer/Lexer.h"
#include "src/analyzer/Parser.h"
#include "src/flow/ExecutionFlowManager.h"
#include "src/executor/CommandExecutor.h"

int main() {

//    std::string command;
//    std::cout << "=== uterm, a simple terminal ===" << std::endl;
//    std::cout << "$ ";
//    std::cin >> command;

    Source source("myprog 123 koles <<MARKER\ntresc here documentu\nMARKER | grep ziombel > jakis_pliczek_ziombla.txt; jakis_koles 'witaj gosciu'; def export ZIOMBEL='imie ziombla'");

    auto lexer = std::make_unique<Lexer>(source);

    auto parser = std::make_unique<Parser>(std::move(lexer));

    auto parseTree = parser->parse();

    auto flowManager = std::make_unique<ExecutionFlowManager>();
    parseTree->accept(flowManager.get());

    auto executor = std::make_unique<CommandExecutor>();
    parseTree->accept(executor.get());

    return 0;
}