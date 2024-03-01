%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

<<EOF>>    return yy::parser::make_END (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"{"        return yy::parser::make_LBRACE (loc);
"}"        return yy::parser::make_RBRACE (loc);
","        return yy::parser::make_COMMA(loc);
"def"      return yy::parser::make_DEF(loc);
";"        return yy::parser::make_SEMICOLON (loc);
"="        return yy::parser::make_ASSIGN (loc);
"declare"  return yy::parser::make_DECL (loc);
"if"       return yy::parser::make_IF (loc);
"else"     return yy::parser::make_ELSE (loc);
"while"    return yy::parser::make_WHILE  (loc);
"print"    return yy::parser::make_PRINT   (loc);
"return"   return yy::parser::make_RET   (loc);
"+"        return yy::parser::make_ADD (loc);
"-"        return yy::parser::make_SUB (loc);
"*"        return yy::parser::make_MUL (loc);
"/"        return yy::parser::make_DIV (loc);
"<"        return yy::parser::make_L (loc);
">"        return yy::parser::make_G (loc);
"<="       return yy::parser::make_LEQ (loc);
">="       return yy::parser::make_GEQ (loc);
"=="       return yy::parser::make_EQ (loc);
"!="       return yy::parser::make_NEQ (loc);
{int}      return make_NUMBER(yytext, loc);
{id}       return yy::parser::make_IDENTIFIER(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}
