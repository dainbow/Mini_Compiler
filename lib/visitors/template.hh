#pragma once

#include "base_element.hh"
#include "visitor.hh"

template <typename T>
class TemplateVisitor : public Visitor {
 public:
  T Eval(BaseElement* element) {
    element->Accept(this);
    return last_value_;
  }

 protected:
  T last_value_;
};
