#pragma once

#include "expressions/add_expression.hh"
#include "expressions/call_expression.hh"
#include "expressions/div_expression.hh"
#include "expressions/expression.hh"
#include "expressions/ident_expression.hh"
#include "expressions/mul_expression.hh"
#include "expressions/neg_expression.hh"
#include "expressions/number_expression.hh"

#include "functions/expressions_list.hh"
#include "functions/function.hh"
#include "functions/functions_list.hh"
#include "functions/params_list.hh"

#include "statements/assign_state.hh"
#include "statements/decl_state.hh"
#include "statements/if_state.hh"
#include "statements/print_state.hh"
#include "statements/return_state.hh"
#include "statements/scope_statements.hh"
#include "statements/statement.hh"
#include "statements/statements_list.hh"
#include "statements/while_state.hh"

#include "logic/eq_log.hh"
#include "logic/g_log.hh"
#include "logic/geq_log.hh"
#include "logic/l_log.hh"
#include "logic/leq_log.hh"
#include "logic/neq_log.hh"

#include "program.hh"
