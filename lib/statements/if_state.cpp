#include "if_state.hh"

IfState::IfState(Expression* expression, StatementsList* condTrue,
                 StatementsList* condFalse)
    : expression_(expression), condTrue_(condTrue), condFalse_(condFalse) {}

void IfState::Accept(Visitor* visitor) {
  visitor->Visit(this);
} 