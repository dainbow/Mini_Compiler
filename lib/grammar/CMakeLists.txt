project(Grammar)

set(PARSER_TARGET "Parser${PROJECT_NAME}")
set(SCANNER_TARGET "Scanner${PROJECT_NAME}")
set(TREE_TARGET "Tree${PROJECT_NAME}")

set(PARSER_OUTPUT "BISON_${PARSER_TARGET}_OUTPUTS")
set(SCANNER_OUTPUT "FLEX_${SCANNER_TARGET}_OUTPUTS")

set(
  HEADERS
  driver.hh
  parser.hh
)

BISON_TARGET(
  ${PARSER_TARGET}
  parser.y
  ${PROJECT_SOURCE_DIR}/parser.cpp
  DEFINES_FILE ${PROJECT_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
  ${SCANNER_TARGET}
  scanner.l
  ${PROJECT_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(ScannerGrammar ParserGrammar)

set(
  SOURCES

  driver.cpp
  program.cpp

  ${${PARSER_OUTPUT}}
  ${${SCANNER_OUTPUT}}

  expressions/number_expression.cpp
  expressions/add_expression.cpp
  expressions/call_expression.cpp
  expressions/mul_expression.cpp
  expressions/div_expression.cpp
  expressions/neg_expression.cpp
  expressions/ident_expression.cpp

  functions/expressions_list.cpp
  functions/function.cpp
  functions/functions_list.cpp
  functions/params_list.cpp

  statements/assign_state.cpp
  statements/decl_state.cpp
  statements/statements_list.cpp
  statements/scope_statements.cpp
  statements/if_state.cpp
  statements/return_state.cpp
  statements/input_state.cpp
  statements/while_state.cpp
  statements/print_state.cpp

  logic/eq_log.cpp
  logic/neq_log.cpp
  logic/g_log.cpp
  logic/l_log.cpp
  logic/geq_log.cpp
  logic/leq_log.cpp

  program.cpp
)

add_library(
  ${GRAMMAR_LIB}
  SHARED
  ${SOURCES}
)

target_include_directories(
  ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}
)

target_include_directories(
  ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/..
)

target_include_directories(
  ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/../include
)
