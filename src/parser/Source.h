//
// Created by slighten on 19.12.2019.
//

#ifndef UTERM_SOURCE_H
#define UTERM_SOURCE_H


#include <string>

class Source {
private:
    std::string source = "";
    int currentReadPosition = 0;

public:
    Source(std::string source) {
        this->source = source;
    }

    Source() = default;

    void updateSource(std::string source) {
        this->source = source;
        this->currentReadPosition = 0;
    }

    void extendSource(std::string extension) {
        this->source += extension;
    }

    char getNextChar() {
        return source[currentReadPosition++];
    }

    char peekNextChar() {
        return source[currentReadPosition];
    }

    bool dataAvailable() {
        return currentReadPosition < source.size();
    }

    bool endsWithNewLine() {
        int lastCharPos = source.size() - 1;

        return lastCharPos == currentReadPosition && source[lastCharPos] == '\n';
    }
};


#endif //UTERM_SOURCE_H
