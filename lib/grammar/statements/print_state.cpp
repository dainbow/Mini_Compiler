#include "print_state.hh"

PrintState::PrintState(Expression* expression) : expression_(expression) {}

void PrintState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}