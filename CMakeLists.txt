cmake_minimum_required(VERSION 3.5.1)
project(uterm)

set(CMAKE_CXX_STANDARD 17)

add_executable(uterm src/main.cpp src/parser/Lexer.cpp src/parser/Lexer.h src/parser/Parser.cpp src/parser/Parser.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/parser/Source.h src/parser/Token.h src/parser/nodes/PipeCmdCall.h src/parser/nodes/Redirection.h src/parser/nodes/Value.h src/parser/nodes/here_document/HereDocumentElement.h src/parser/nodes/here_document/HereDocumentLine.h)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable (Boost_Tests_run test/parser/LexerUT.cpp src/parser/Lexer.cpp src/parser/Lexer.h src/parser/Parser.cpp src/parser/Parser.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/parser/Source.h src/parser/Token.h src/parser/ParseTree.h src/parser/nodes/Node.h src/parser/nodes/PipeCmdCall.h src/parser/nodes/Redirection.h src/parser/nodes/CmdCall.h src/parser/nodes/here_document/HereDocument.h src/parser/nodes/VarDef.h src/parser/nodes/Value.h src/parser/nodes/LiteralValue.h src/parser/nodes/VarValue.h src/parser/nodes/RedirectedCmdCall.h src/parser/Visitor.h src/parser/nodes/Statement.h src/executor/Environment.h test/parser/ParserUT.cpp src/executor/Pipe.h src/parser/nodes/here_document/HereDocumentElement.h src/parser/nodes/here_document/HereDocumentLine.h src/parser/nodes/Variable.h)

target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})

#add_subdirectory(test)