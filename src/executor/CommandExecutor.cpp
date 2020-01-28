//
// Created by radek on 05.12.2019.
//

#include <iostream>
#include<sys/wait.h>
#include <zconf.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include "CommandExecutor.h"
#include "../parser/nodes/VarDef.h"
#include "../parser/nodes/RedirectedCmdCall.h"
#include "../parser/nodes/PipeCmdCall.h"
#include "../parser/nodes/CmdCall.h"
#include "../parser/nodes/here_document/HereDocument.h"
#include "../parser/nodes/here_document/HereDocumentLine.h"
#include "../parser/nodes/here_document/HereDocumentElement.h"
#include "../parser/nodes/Redirection.h"
#include "../parser/nodes/LiteralValue.h"
#include "../parser/nodes/VarValue.h"

/**
 * This method is responsible for opening a file and redirecting command input/output from/to this file.
 * NOTE: The RIGHT redirection is for the whole pipeline output (which practically means output of the last command in pipeline).
 * BUT: The LEFT redirection is for the first cmd call in pipeline (first command in pipeline).
 *
 * The call order is: visit(RedirectedCmdCall) --> visit(PipeCmdCall) --> visit(CmdCall)
 */
void CommandExecutor::visit(RedirectedCmdCall *redirectedCmdCall) {

    if (redirectedCmdCall->redirection != nullptr) {

        if (redirectedCmdCall->redirection->redirectionType == RedirectionType::RIGHT) {
            int fd = open(redirectedCmdCall->redirection->getFileName().c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);

            redirectedCmdCall->pipeCmdCall->cmdCall->outfd = fd;
            redirectedCmdCall->pipeCmdCall->outfd = fd;

            openDescriptors.push_back(fd);
        } else {
            int fd = open(redirectedCmdCall->redirection->getFileName().c_str(), O_RDONLY, 0666);

            redirectedCmdCall->pipeCmdCall->cmdCall->infd = fd;

            openDescriptors.push_back(fd);
        }

    }
}

/**
 * This method is responsible for creating a pipe and setting appropriate descriptors in CmdCall objects, which will
 * be later used in dup2 calls in child processes of the commands (they will get spawned in visit(CmdCall) method).
 *
 * The call order is: visit(RedirectedCmdCall) --> visit(PipeCmdCall) --> visit(CmdCall)
 */
void CommandExecutor::visit(PipeCmdCall *pipeCmdCall) {

    if (pipeCmdCall->pipeChain != nullptr) { //there is a pipe to next command

        int fd[2];
        pipe(fd);

        pipeCmdCall->cmdCall->outfd = fd[1];
        pipeCmdCall->pipeChain->cmdCall->infd = fd[0];

        //maybe it's the last PipeCmdCall object, in that case set the command outfd to whole pipeline outfd
        pipeCmdCall->pipeChain->cmdCall->outfd = pipeCmdCall->outfd;

        //and in case it's not the last one, let the descriptor pass through to the next one
        pipeCmdCall->pipeChain->outfd = pipeCmdCall->outfd;

        openDescriptors.push_back(fd[0]);
        openDescriptors.push_back(fd[1]);
    }
}

/**
 * This method is responsible for spawning child processes for the CmdCall objects. If there were any descriptors
 * set in visit(PipeCmdCall) method, then they will be duplicated into STDIN and/or STDOUT.
 *
 * The call order is: visit(RedirectedCmdCall) --> visit(PipeCmdCall) --> visit(CmdCall)
 */
void CommandExecutor::visit(CmdCall *cmdCall) {
    if (cmdCall->hereDocument != nullptr) {

        int fd[2];

        if (pipe(fd) == -1)
            throw std::runtime_error("Failed to create pipe required for program inside here document");

        const char *content = cmdCall->hereDocument->finalContent.c_str();
        int size = cmdCall->hereDocument->finalContent.size();


        cmdCall->infd = fd[0];

        write(fd[1], content, size);

        openDescriptors.push_back(fd[0]);
        openDescriptors.push_back(fd[1]);
    }

    std::vector<const char *> args = getArgs(cmdCall);

    if (cmdCall->cmd == "cd") {
        changeDirectory(args);
        return;
    }

    if (fork() == 0) { //in child process

        std::vector<Variable> parentVariables = env->getEnvironmentVariables();
        for (Variable v : parentVariables) {
            if (v.isExported())
                setenv(v.getVarName().data(), v.getValue().data(), 0);
        }

        if (cmdCall->infd != STDIN_FILENO) {
            //redirect standard input from infd
            dup2(cmdCall->infd, STDIN_FILENO);
        }

        if (cmdCall->outfd != STDOUT_FILENO) {
            //redirect standard output to outfd
            dup2(cmdCall->outfd, STDOUT_FILENO);
        }

        //close all inherited descriptors
        for (int fd : openDescriptors) {
            close(fd);
        }

        if (cmdCall->cmd == "pwd") {
            printWorkingDirectory();
            exit(0);
        } else {
            executeExternalProgram(cmdCall, args);
        }

    } else {
        wait(nullptr);

        //in parent process close descriptors used in this command
        if (cmdCall->infd != STDIN_FILENO)
            close(cmdCall->infd);

        if (cmdCall->outfd != STDOUT_FILENO)
            close(cmdCall->outfd);
    }
}


std::vector<const char *> CommandExecutor::getArgs(const CmdCall *cmdCall) const {

    std::vector<std::string> args = cmdCall->evaluateArgs();
    std::vector<const char *> functionArgs;

    // reserve necessary space to prevent vector allocation errors
    functionArgs.reserve(args.size());

    for (int i = 0; i < args.size(); i++) {
        functionArgs.push_back(args[i].c_str());
    }

    functionArgs.push_back(nullptr);
    return functionArgs;
}

void CommandExecutor::changeDirectory(std::vector<const char *> args) const {

    chdir(args[1]);
}

void CommandExecutor::printWorkingDirectory() const {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << cwd << std::endl;
    } else {
        std::cout << "pwd error occured" << std::endl;
    }
}

void CommandExecutor::executeExternalProgram(const CmdCall *cmdCall, std::vector<const char *> args) const {

    execv(cmdCall->cmd.c_str(), const_cast<char **>(&args[0]));
}

void CommandExecutor::visit(VarDef *varDef) {
    env->defineVariable(varDef->name, varDef->value->evaluate(), varDef->exported);
}

void CommandExecutor::visit(VarValue *varValue) {
    Variable variable = env->getVariableOfName(varValue->name);

    varValue->simpleValue = variable.getValue();
    varValue->exported = variable.isExported();
}

void CommandExecutor::visit(LiteralValue *literalValue) {
    //nothing to do here, probably...
}

void CommandExecutor::visit(HereDocument *hereDocument) {
    std::string finalContent = "";

    for (const auto &line : hereDocument->hdContents) {

        for (auto &lineContent : line->lineContents) {
            finalContent += lineContent->text;
        }

        finalContent += '\n';
    }

    hereDocument->finalContent = finalContent;
}

void CommandExecutor::visit(HereDocumentElement *hereDocumentElement) {
    if (hereDocumentElement->variable != nullptr) {
        Variable variable = env->getVariableOfName(hereDocumentElement->variable->name);

        hereDocumentElement->text = variable.getValue();
    } else if (!hereDocumentElement->cmdCall.empty()) {

        int pipes[2];
        pid_t pid;
        char buffer[4096];

        if (pipe(pipes) == -1)
            throw std::runtime_error("Failed to create pipe required for program inside here document");

        if ((pid = fork()) == -1)
            throw std::runtime_error("Failed to execute program inside here document");

        if (pid == 0) {

            dup2(pipes[1], STDOUT_FILENO);
            close(pipes[0]);
            close(pipes[1]);
            execl(hereDocumentElement->cmdCall.c_str(), hereDocumentElement->cmdCall.c_str(), (char *) 0);

        } else {

            close(pipes[1]);
            int nbytes = read(pipes[0], buffer, sizeof(buffer));

            std::string programOutput = "";

            for (int i = 0; i < nbytes; i++) {
                programOutput += buffer[i];
            }

            hereDocumentElement->text = programOutput;
            wait(NULL);
        }
    }
    //nothing to do here, probably...
}

void CommandExecutor::visit(HereDocumentLine *hereDocumentLine) {
    //nothing to do here, probably...
}

void CommandExecutor::visit(Redirection *redirection) {
    //nothing to do here, probably...
}