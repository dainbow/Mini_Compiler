#include "assign_state.hh"

AssignState::AssignState(const std::string& variable, Expression* expression)
    : variable_(variable), expression_(expression) {}

void AssignState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}