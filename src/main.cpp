#include <iostream>
#include <memory>
#include <zconf.h>
#include "parser/Source.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "executor/CommandExecutor.h"
#include "executor/Environment.h"

int main() {

    Environment env;
    Source source;

    auto lexer = std::make_shared<Lexer>(source);

    auto parser = std::make_unique<Parser>(lexer);

    auto executor = std::make_unique<CommandExecutor>(&env);

    std::string userInput;

    while (userInput != "exit") {

        std::cout << "$ " << std::flush;

        getline(std::cin, userInput);

        lexer->updateSource(userInput);

        auto parseTree = parser->parse();

        parseTree->accept(executor.get());
    }

    return 0;
}