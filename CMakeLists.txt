cmake_minimum_required(VERSION 3.5.1)
project(uterm)

set(CMAKE_CXX_STANDARD 17)

add_executable(uterm main.cpp src/analyzer/CommadAnalyzer.cpp src/analyzer/CommadAnalyzer.h src/analyzer/Lexer.cpp src/analyzer/Lexer.h src/analyzer/Parser.cpp src/analyzer/Parser.h src/flow/ExecutionFlowManager.cpp src/flow/ExecutionFlowManager.h src/executor/CommandExecutor.cpp src/executor/CommandExecutor.h src/util/PipeInputStream.cpp src/util/PipeInputStream.h src/util/PipeOutputStream.cpp src/util/PipeOutputStream.h src/analyzer/Source.h)