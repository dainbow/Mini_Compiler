#include "visitor.hh"

#include <map>
#include <stack>
#include <string>

class Interpreter : public Visitor {
 public:
  virtual void Visit(Program* program) override;
  virtual void Visit(StatementsList* program) override;
  virtual void Visit(AssignState* assignment) override;
  virtual void Visit(IfState* ifState) override;
  virtual void Visit(PrintState* printState) override;
  virtual void Visit(WhileState* whileState) override;
  virtual void Visit(DeclState* declState) override;

  virtual void Visit(AddExpression* addExpr) override;
  virtual void Visit(NumberExpression* numExpr) override;
  virtual void Visit(NegExpression* negExpr) override;
  virtual void Visit(MulExpression* mulExpr) override;
  virtual void Visit(IdentExpression* identExpr) override;
  virtual void Visit(DivExpression* divExpr) override;

  virtual void Visit(LLogic* log) override;
  virtual void Visit(GLogic* log) override;
  virtual void Visit(LeqLogic* log) override;
  virtual void Visit(GeqLogic* log) override;
  virtual void Visit(EqLogic* log) override;
  virtual void Visit(NeqLogic* log) override;

  int Eval(Expression* expr);

 private:
  std::map<std::string, int> variables_;
  std::stack<int> values_;
};