#include <iostream>
#include <memory>
#include <zconf.h>
#include "parser/Source.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "executor/CommandExecutor.h"
#include "executor/Environment.h"

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
                  "ls | grep pliczek | cat;"
                  "/usr/bin/head < pliczek.txt");

    auto lexer = std::make_unique<Lexer>(source);

    auto parser = std::make_unique<Parser>(std::move(lexer));

    auto parseTree = parser->parse();

    auto executor = std::make_unique<CommandExecutor>(&env);
    parseTree->accept(executor.get());

    sleep(1);

    return 0;
}