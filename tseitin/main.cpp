#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#include "expr.hpp"
#include "expr.tab.hpp"

//extern "C" int yyparse();
extern "C" FILE *yyin;
extern Expr *res;

int main(int, char**) {
    // parse through the input until there is no more:
    do {
        yyparse();

	vector<Expr*> exprs;
	
	set<Expr*> vars;

	res->get_vars(vars);

	Expr * var = res->tseitin(vars.size(), exprs);
	exprs.push_back(var);

	for(int i = 0; i < exprs.size(); i++)
	    cout << exprs[i]->to_cnf() << endl;
	
        cout << res->to_string() << endl << res->eval() << endl;
	cout << endl;
    } while (!feof(yyin));
    return 0;
}

void yyerror(const char *s) {
    cout << "EEK, parse error!  Message: " << s << endl;
    // might as well halt now:
    exit(-1);
}

