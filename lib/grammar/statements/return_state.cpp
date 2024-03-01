#include "return_state.hh"

ReturnState::ReturnState(Expression* expression)
    : return_expression_(expression) {}

void ReturnState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
