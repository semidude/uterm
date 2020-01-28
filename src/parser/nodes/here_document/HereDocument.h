//
// Created by Radoslaw Panuszewski on 1/14/20.
//

#ifndef UTERM_HEREDOCUMENT_H
#define UTERM_HEREDOCUMENT_H


#include <string>
#include <utility>
#include "../../Visitor.h"
#include "../Node.h"
#include "HereDocumentLine.h"

struct HereDocument: public Node {
    std::string hdToken;

    std::vector<std::shared_ptr<HereDocumentLine>> hdContents;

    HereDocument(std::string hdToken, std::vector<std::shared_ptr<HereDocumentLine>> contents) : hdToken(std::move(hdToken)), hdContents(std::move(contents)) {}

    void accept(Visitor *visitor) override {

        for(auto& content : hdContents) {
            content->accept(visitor);
        }

        visitor->visit(this);
    }

    friend std::ostream &operator<<(std::ostream &os, const HereDocument &hereDocument) {
        return os << "(HereDocument " << hereDocument.hdToken << " " << hereDocument.hdToken << ")";
    }
};


#endif //UTERM_HEREDOCUMENT_H
