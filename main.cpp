#include <iostream>
#include <memory>
#include <zconf.h>
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

//    Source source("myprog 123 koles <<MARKER\ntresc here documentu\nMARKER | grep ziombel > jakis_pliczek_ziombla.txt; jakis_koles 'witaj gosciu'; def export ZIOMBEL='imie ziombla'");
//    Source source("cat sample | grep abc > fajl.txt; mkdir ujebanekolosy; def export ELKA='chujnia z grzybnia'");
//    Source source("rm jakisfolder; prog 13 cokolwiek <<MARKER\nbla bla bla bla\nMARKER; mkdir jakisfolder");
//    Source source("grep aaa plik1; cat plik2 > plik3 | def spanie=$jaknajbardziej");
//    Source source(cd jakisfolder);
//    Source source("");

//    Source source("myprog 123 koles <<MARKER\ntresc here documentu\nMARKER | grep ziombel > jakis_pliczek_ziombla.txt;"
//                  "jakis_koles 'witaj gosciu';"
//                  "def export ZIOMBEL='imie ziombla';"
//                  "echo $ZIOMBEL;"
//                  "echo 'siema gosciu smieszny' < $ZIOMBEL");

    Environment env;

    Source source("touch ziombel;"
                  "touch koles;"
                  "def COSTAM=koles;"
                  "ls | grep l | cat | grep $COSTAM > pliczek.txt;"
                  "ls | grep pliczek | cat");

    auto lexer = std::make_unique<Lexer>(source);

    auto parser = std::make_unique<Parser>(std::move(lexer));

    auto parseTree = parser->parse();

    auto flowManager = std::make_unique<ExecutionFlowManager>(&env);
    parseTree->accept(flowManager.get());

    auto executor = std::make_unique<CommandExecutor>();
    parseTree->accept(executor.get());

    sleep(1);

    return 0;
}