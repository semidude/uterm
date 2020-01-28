//
// Created by mivine on 27.01.20.
//

#ifndef UTERM_HEREDOCUMENTLINE_H
#define UTERM_HEREDOCUMENTLINE_H

#include <string>
#include <vector>
#include "HereDocumentElement.h"

struct HereDocumentLine : public Node {
    std::vector<std::shared_ptr<HereDocumentElement>> lineContents;

    explicit HereDocumentLine(std::vector<std::shared_ptr<HereDocumentElement>> lineContents)
            : lineContents(std::move(lineContents)) {}

    void accept(Visitor *visitor) override {
        for(auto& content : lineContents) {
            content->accept(visitor);
        }

        visitor->visit(this);
    }
};

#endif //UTERM_HEREDOCUMENTLINE_H
