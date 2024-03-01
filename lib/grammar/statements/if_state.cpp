#include "if_state.hh"

IfState::IfState(Expression* expression, Statement* condTrue,
                 Statement* condFalse)
    : expression_(expression), condTrue_(condTrue), condFalse_(condFalse) {}

void IfState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}