project(Compiler)

set(CURRENT_EXECUTABLE "${PROJECT_NAME}Executable")
set(GRAMMAR_LIB "${PROJECT_NAME}GrammarLib")
set(GRAMMAR_PROJECT "${PROJECT_NAME}GrammarProject")

set(
    SOURCES

    types/func_type.cpp
    types/type.cpp
    types/frame_idx_type.cpp

    symbol_table/scope_layer.cpp

    visitors/interpreter.cpp
    visitors/printer.cpp
    visitors/symbol_tree.cpp
    visitors/template.cpp
)

add_subdirectory(grammar)

add_executable(
    ${CURRENT_EXECUTABLE}
    main.cpp
    ${SOURCES}
)

target_include_directories(
    ${CURRENT_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}
)
target_include_directories(
    ${CURRENT_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/grammar
)

target_link_libraries(${CURRENT_EXECUTABLE} ${GRAMMAR_LIB})