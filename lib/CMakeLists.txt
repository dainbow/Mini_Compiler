project(Visitor)
set(
    HEADERS
    driver.hh
    parser.hh
    )

BISON_TARGET(
    ParserVisitor
    parser.y
    ${Visitor_SOURCE_DIR}/parser.cpp
    COMPILE_FLAGS --graph
    DEFINES_FILE ${Visitor_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    ScannerVisitor
    scanner.l
    ${Visitor_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(ScannerVisitor ParserVisitor)

add_executable(
    VisitorExecutable
    main.cpp
    driver.cpp
    ${BISON_ParserVisitor_OUTPUTS}
    ${FLEX_ScannerVisitor_OUTPUTS}

    expressions/number_expression.cpp
    expressions/add_expression.cpp
    expressions/mul_expression.cpp
    expressions/div_expression.cpp
    expressions/neg_expression.cpp
    expressions/ident_expression.cpp

    statements/assign_state.cpp
    statements/statements_list.cpp
    statements/if_state.cpp
    statements/while_state.cpp
    statements/print_state.cpp
    
    program.cpp
)

target_include_directories(
    VisitorExecutable PRIVATE ${Visitor_SOURCE_DIR}
)

add_custom_target(
    VisitorTree
    COMMAND dot -Tpng ${Visitor_SOURCE_DIR}/parser.gv -o ${Visitor_SOURCE_DIR}/parser.png
    
    DEPENDS ${Visitor_SOURCE_DIR}/parser.cpp
)

add_dependencies(VisitorExecutable VisitorTree)