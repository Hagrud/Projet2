%{
#include <iostream>
#include <cstdlib>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "expr.tab.hpp"
%}
%%
[ \t\n]         ;
[0-9]+          { yylval.ival = atoi(yytext); return TK_VAR; }
"("             { return TK_LPAREN; 		}
")"             { return TK_RPAREN; 		}
"/\\"		{ return TK_CONJONCTION;	}
"\\/"		{ return TK_DISJONCTION;	}
"-"		{ return TK_NEGATION;		}
"~"		{ return TK_NEGATION;		}
"X"		{ return TK_XOR;		}
"=>"		{ return TK_IMPLIQUE;		}
"<=>"		{ return TK_EQUIVALENT;	}
.               ;
%%
