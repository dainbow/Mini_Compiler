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
    LARR "["
    RARR "]"
    SEMICOLON ";"
    DDOTS ":"
    ASSIGN "="
    MAIN "main"
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
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%nterm <Program*> program

%nterm <Statement*> statements
%nterm <Expression*> expression

%nterm <StatementsList*> statements_list
%nterm <StatementsList*> main

// Prints output in parsing option for debugging location terminal
%printer { yyo << $$; } <*>;

%%
%start program;

program: main {
        $$ = new Program($1);
        driver.program = $$;
    };

main: "main" "(" ")" "{" statements_list "}"  {
      $$ = $5;
    };

statements_list: 
    %empty { $$ = new StatementsList(); /* A -> eps */}
    | statements_list statements {
        $1->AddStatement($2); 
        $$ = $1;
    };

statements: "declare" "identifier" ";" { $$ = new VarDeclState($2); }
|  "{" statements_list "}" { $$ = $2 }
|  "if" "(" expression ")" statements { $$ = new IfState($3, $5, {}); }
|  "if" "(" expression ")" statements "else" statements { $$ = new IfState($3, $5, $7); }
|  "while" "(" expression ")" statements { $$ = new WhileState($3, $5); }
|  "print" "(" expression ")" ";" { $$ = new PrintState("print", $3); }
|  "identifier" "=" expression ";" { $$ = new AssignState($1, $3); };

expression: "number" { $$ = new NumberExpression($1); }
| "identifier" {$$ = new IdentExpression($1); }
| "-" expression { $$ = new NegateExpression($2); }
| expression "+" expression {$$ = new AddExpression($1, $3); }
| expression "-" expression {$$ = new AddExpression($1, new NegExpression($3)); }
| expression "*" expression {$$ = new MulExpression($1, $3); }
| expression "/" expression {$$ = new DivExpression($1, $3); }
| "(" expression ")" {$$ = $2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
