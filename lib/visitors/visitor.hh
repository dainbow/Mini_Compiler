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

    virtual void Visit(AddExpression* addExpr) = 0;
    virtual void Visit(NumberExpression* numExpr) = 0;
    virtual void Visit(NegExpression* negExpr) = 0;
    virtual void Visit(MulExpression* mulExpr) = 0;
    virtual void Visit(IdentExpression* identExpr) = 0;
    virtual void Visit(DivExpression* divExpr) = 0;
};
