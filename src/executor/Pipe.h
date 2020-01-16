//
// Created by radek on 16.01.2020.
//

#ifndef UTERM_PIPE_H
#define UTERM_PIPE_H


struct Pipe {
    int infd;
    int outfd;

    Pipe(int infd, int outfd) : infd(infd), outfd(outfd) {}
};


#endif //UTERM_PIPE_H
