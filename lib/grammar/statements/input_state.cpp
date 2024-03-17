#include "input_state.hh"

InputState::InputState(const std::string& expression) : var_name_(expression) {}

void InputState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
