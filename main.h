#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "dpll/dpll.h"


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
