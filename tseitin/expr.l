%{
#include <iostream>
#include <cstdlib>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "expr.tab.hpp"
%}
%%
[ \t]         ;
[0-9]+          { yylval.ival = atoi(yytext); return TK_BOOL; }
"("             { return TK_LPAREN; }
")"             { return TK_RPAREN; }
"\\/"             { return TK_OR; }
"/\\"             { return TK_AND; }
"X"             { return TK_XOR; }
"=>"            { return TK_IMPL; }
"<=>"           { return TK_EQ; }
"\n"            { return TK_AND; }
"~"             { return TK_NEG; }
"-"             { return TK_NEG; }
.               ;
%%
