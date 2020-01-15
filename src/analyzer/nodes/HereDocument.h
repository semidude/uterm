//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_HEREDOCUMENT_H
#define UTERM_HEREDOCUMENT_H


#include <string>
#include <utility>
#include "../Visitor.h"
#include "Node.h"

struct HereDocument: public Node {
    std::string hdToken;
    std::string hdContent;

    HereDocument(std::string hdToken, std::string hdContent) : hdToken(std::move(hdToken)), hdContent(std::move(hdContent)) {}

    void accept(Visitor *visitor) override {
        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const HereDocument &hereDocument) {
        return os << "hereDocument (" << hereDocument.hdToken << " " << hereDocument.hdContent << " " << hereDocument.hdToken << ")" << std::endl;
    }
};


#endif //UTERM_HEREDOCUMENT_H
