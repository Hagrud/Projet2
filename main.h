#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "dpll/dpll.h"
#include "tseitin/expr.hpp"
#include "tseitin/expr.tab.hpp"

extern "C" FILE *yyin;
extern Expr *res;


#include "dpll/paris.h"
#include "dpll/graph.h"

#include "dpll/parieurs/parieur.h"
#include "dpll/solveurs/solveur_deduction.h"

using namespace std;

/**
*@desc Lit les arguments donnés au programme, détecte les options, prévient si une option inconnue est utilisée
*@return Le nom du fichier entrée en argument.
*/
char* lire_args(int argc, char* argv[]);

/**
*@desc Met en forme la réponse du programme.
*/
void reponse(vector<vector<int>>& clauses,vector<bool>& rep);

char* create_tseitin(char* file);

bool get_option(string option);

void init();

/**
*@desc Contient les variables globales.
*/
class global
{
    public:
    static bool DLIS;
    static bool MOMS;
    static bool RAND;
    static bool TSEITIN;
    static bool INTERACT;
    static bool WL;
};
