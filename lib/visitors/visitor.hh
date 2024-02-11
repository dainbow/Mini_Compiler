#pragma once

#include "../forwards.hh"

class Visitor {
 public:
    virtual void Visit(Program* program) = 0;
    virtual void Visit(StatementsList* program) = 0;
    virtual void Visit(AssignState* assignment) = 0;
    virtual void Visit(IfState* ifState) = 0;
    virtual void Visit(PrintState* printState) = 0;
    virtual void Visit(WhileState* whileState) = 0;
    virtual void Visit(DeclState* declState) = 0;

    virtual void Visit(AddExpression* addExpr) = 0;
    virtual void Visit(NumberExpression* numExpr) = 0;
    virtual void Visit(NegExpression* negExpr) = 0;
    virtual void Visit(MulExpression* mulExpr) = 0;
    virtual void Visit(IdentExpression* identExpr) = 0;
    virtual void Visit(DivExpression* divExpr) = 0;

    virtual void Visit(LLogic* log) = 0;
    virtual void Visit(GLogic* log) = 0;
    virtual void Visit(LeqLogic* log) = 0;
    virtual void Visit(GeqLogic* log) = 0;
    virtual void Visit(EqLogic* log) = 0;
    virtual void Visit(NeqLogic* log) = 0;
};
