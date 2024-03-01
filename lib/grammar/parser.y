%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    
    #include "forwards.hh"
}


%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "elements.hh"
    #include "program.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}
// token name in variable
%token
    END 0 "end of file"
    LPAREN "("
    RPAREN ")"
    LBRACE "{"
    RBRACE "}"
    SEMICOLON ";"
    ASSIGN "="
    DECL "declare"
    IF "if"
    ELSE "else"
    WHILE "while"
    PRINT "print"
    RET "return"
    ADD "+"
    SUB "-"
    MUL "*"
    DIV "/"
    L "<"
    G ">"
    LEQ "<="
    GEQ ">="
    EQ "=="
    NEQ "!="
    COMMA ","
    DEF "def"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%nterm <FunctionsList*> functions_list

%nterm <Function*> function_def

%nterm <ParamsList*> params_list
%nterm <ParamsList*> empty_params_list
%nterm <ParamsList*> complex_params_list

%nterm <ExpressionsList*> expressions_list
%nterm <ExpressionsList*> empty_expressions_list
%nterm <ExpressionsList*> complex_expressions_list

%nterm <Program*> program

%nterm <Statement*> statement
%nterm <StatementsList*> statements_list

%nterm <Expression*> expression

// Prints output in parsing option for debugging location terminal
%printer { yyo << $$; } <*>;

%%
%start program;

program: functions_list {
        $$ = new Program($1);
        driver.program = $$;
    };

functions_list:
    %empty { $$ = new FunctionsList(); }
    | functions_list function_def {
        $1->AddFunction($2); $$ = $1;
    };

function_def:
    "def" "identifier" "(" params_list ")" "{" statements_list "}" { $$ = new Function($2, $4, new ScopeStatements($7)); };

params_list:
    empty_params_list {$$ = $1;} /* def foo () {}*/
    | complex_params_list {$$ = $1;} /* def foo(a, b, c) {} */
    ;

empty_params_list:
    %empty { $$ = new ParamsList();}
    ;

complex_params_list:
    "identifier" {$$ = new ParamsList($1);}
    | complex_params_list "," "identifier" { $1->AddParam($3); $$ = $1; }
    ;

statements_list: 
    %empty { $$ = new StatementsList(); /* A -> eps */}
    | statements_list statement {
        $1->AddStatement($2); 
        $$ = $1;
    };

statement: "declare" "identifier" ";" { $$ = new DeclState($2); }
|  "{" statements_list "}" { $$ = new ScopeStatements($2); }
|  "if" "(" expression ")" statement { $$ = new IfState($3, $5, new StatementsList()); }
|  "if" "(" expression ")" statement "else" statement { $$ = new IfState($3, $5, $7); }
|  "while" "(" expression ")" statement { $$ = new WhileState($3, $5); }
|  "print" "(" expression ")" ";" { $$ = new PrintState($3); }
|  "identifier" "=" expression ";" { $$ = new AssignState($1, $3); }
|  "return" expression ";" {$$ = new ReturnState($2); }
;

expression: "number" { $$ = new NumberExpression($1); }
| "identifier" {$$ = new IdentExpression($1); }
| "-" expression { $$ = new NegExpression($2); }
| expression "+" expression {$$ = new AddExpression($1, $3); }
| expression "-" expression {$$ = new AddExpression($1, new NegExpression($3)); }
| expression "*" expression {$$ = new MulExpression($1, $3); }
| expression "/" expression {$$ = new DivExpression($1, $3); }
| expression "<" expression {$$ = new LLogic($1, $3); }
| expression ">" expression {$$ = new GLogic($1, $3); }
| expression "<=" expression {$$ = new LeqLogic($1, $3); }
| expression ">=" expression {$$ = new GeqLogic($1, $3); }
| expression "==" expression {$$ = new EqLogic($1, $3); }
| expression "!=" expression {$$ = new NeqLogic($1, $3); }
| "identifier" "(" expressions_list ")"  {$$ = new CallExpression($1, $3); }
| "(" expression ")" {$$ = $2; };

expressions_list:
    empty_expressions_list {$$ = $1;} /* foo () {}*/
    | complex_expressions_list {
        $$ = $1;
      } /* foo(a, b, c) {} */
    ;

empty_expressions_list:
    %empty { $$ = new ExpressionsList();}
    ;

complex_expressions_list: 
    expression {$$ = new ExpressionsList($1);}
    | complex_expressions_list "," expression { $1->AddExpression($3); $$ = $1; }
    ;

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
