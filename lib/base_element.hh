#pragma once

#include "visitors/visitor.hh"

class BaseElement {
 public:
    virtual void Accept(Visitor* visitor) = 0;
    virtual ~BaseElement() = default;
};
