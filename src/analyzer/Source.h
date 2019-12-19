//
// Created by slighten on 19.12.2019.
//

#ifndef UTERM_SOURCE_H
#define UTERM_SOURCE_H


class Source {
private:
    std::string source;
    int pos = 0;

public:
    Source(std::string source) {
        this->source = source;
    }

    char getNextChar() {
        return source[pos++];
    }
};


#endif //UTERM_SOURCE_H
