#include "decl_state.hh"

DeclState::DeclState(const std::string& name) : variable_(name) {}

void DeclState::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
