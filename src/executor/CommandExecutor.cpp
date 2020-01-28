//
// Created by radek on 05.12.2019.
//

#include <iostream>
#include <zconf.h>
#include <fcntl.h>
#include "CommandExecutor.h"
#include "../parser/nodes/VarDef.h"
#include "../parser/nodes/RedirectedCmdCall.h"
#include "../parser/nodes/PipeCmdCall.h"
#include "../parser/nodes/CmdCall.h"
#include "../parser/nodes/HereDocument.h"
#include "../parser/nodes/Redirection.h"
#include "../parser/nodes/LiteralValue.h"
#include "../parser/nodes/VarValue.h"

/**
 * This method is responsible for opening a file and redirecting command output to this file.
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
        }
        else {
            int fd = open(redirectedCmdCall->redirection->getFileName().c_str(), O_RDONLY, 0666);

            redirectedCmdCall->pipeCmdCall->cmdCall->infd = fd;

            openDescriptors.push_back(fd);
        }

    }
}

/**
 * This method is responsible for creating a pipe and setting appropriate descriptors in CmdCall objects, which will
 * be later used for in dup2 calls in child processes of the commands (they will get spawned in visit(CmdCall) method).
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

    if (fork() == 0) { //in child process

        //TODO add all exported variables to the child process environment

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

        // reserve necessary space to prevent vector allocation errors
        std::vector<std::string> args = cmdCall->evaluateArgs();
        std::vector<const char *> functionArgs;
        functionArgs.reserve(args.size());

        for(int i = 0 ; i < args.size() ; i ++) {
            functionArgs.push_back(args[i].c_str());
        }

        functionArgs.push_back(nullptr);

        execv(cmdCall->cmd.c_str(), const_cast<char **>(&functionArgs[0]));
    }

    //in parent process close descriptors used in this command
    if (cmdCall->infd != STDIN_FILENO)
        close(cmdCall->infd);

    if (cmdCall->outfd != STDOUT_FILENO)
        close(cmdCall->outfd);


    if (cmdCall->hereDocument != nullptr) {
        //TODO create here document and make it input for the CmdCall
    }
}

void CommandExecutor::visit(VarDef *varDef) {
    env->defineVariable(varDef->name, varDef->value->evaluate());
}

void CommandExecutor::visit(VarValue *varValue) {
    varValue->simpleValue = env->getValueOf(varValue->name);
}

void CommandExecutor::visit(LiteralValue *literalValue) {
    //nothing to do here, probably...
}

void CommandExecutor::visit(HereDocument *hereDocument) {
    //nothing to do here, probably...
}

void CommandExecutor::visit(Redirection *redirection) {
    //nothing to do here, probably...
}