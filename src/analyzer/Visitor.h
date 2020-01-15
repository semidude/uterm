//
// Created by radek on 15.01.2020.
//

#ifndef UTERM_VISITOR_H
#define UTERM_VISITOR_H

struct VarDef;
struct RedirectedCmdCall;
struct PipeCmdCall;
struct CmdCall;
struct HereDocument;
struct LiteralValue;
struct Redirection;
struct VarValue;

struct Visitor {
    virtual void visit(VarDef *varDef) { /*no nop*/ }
    virtual void visit(RedirectedCmdCall *redirectedCmdCall) { /*no nop*/ }
    virtual void visit(PipeCmdCall *pipeCmdCall) { /*no nop*/ }
    virtual void visit(CmdCall *cmdCall) { /*no nop*/ }
    virtual void visit(HereDocument *hereDocument) { /*no nop*/ }
    virtual void visit(Redirection *redirection) { /*no nop*/ }
    virtual void visit(LiteralValue *literalValue) { /*no nop*/ }
    virtual void visit(VarValue *varValue) { /*no nop*/ }
};


#endif //UTERM_VISITOR_H
