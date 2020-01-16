cmake_minimum_required(VERSION 3.5.1)
project(uterm)

set(CMAKE_CXX_STANDARD 17)

add_executable(uterm main.cpp src/analyzer/CommadAnalyzer.cpp src/analyzer/CommadAnalyzer.h src/analyzer/Lexer.cpp src/analyzer/Lexer.h src/analyzer/Parser.cpp src/analyzer/Parser.h src/flow/ExecutionFlowManager.cpp src/flow/ExecutionFlowManager.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/util/PipeInputStream.cpp src/util/PipeInputStream.h src/util/PipeOutputStream.cpp src/util/PipeOutputStream.h src/analyzer/Source.h src/analyzer/Token.h src/analyzer/nodes/PipeCmdCall.h src/analyzer/nodes/Redirection.h src/analyzer/nodes/Value.h)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable (Boost_Tests_run test/analyzer/LexerUT.cpp src/analyzer/CommadAnalyzer.cpp src/analyzer/CommadAnalyzer.h src/analyzer/Lexer.cpp src/analyzer/Lexer.h src/analyzer/Parser.cpp src/analyzer/Parser.h src/flow/ExecutionFlowManager.cpp src/flow/ExecutionFlowManager.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/util/PipeInputStream.cpp src/util/PipeInputStream.h src/util/PipeOutputStream.cpp src/util/PipeOutputStream.h src/analyzer/Source.h src/analyzer/Token.h src/analyzer/ParseTree.h src/analyzer/nodes/Node.h src/analyzer/nodes/PipeCmdCall.h src/analyzer/nodes/Redirection.h src/analyzer/nodes/CmdCall.h src/analyzer/nodes/HereDocument.h src/analyzer/nodes/VarDef.h src/analyzer/nodes/Value.h src/analyzer/nodes/LiteralValue.h src/analyzer/nodes/VarValue.h src/analyzer/nodes/RedirectedCmdCall.h src/analyzer/Visitor.h src/analyzer/nodes/Statement.h src/flow/Environment.h)

target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})

#add_subdirectory(test)