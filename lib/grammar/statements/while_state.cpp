#include "while_state.hh"

WhileState::WhileState(Expression* expression, Statement* cond)
    : expression_(expression), cond_(cond) {}

void WhileState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}