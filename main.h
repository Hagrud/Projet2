#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "dpll/dpll.h"


using namespace std;

/**
*@desc Lit les arguments donn�s au programme, d�tecte les options, pr�vient si une option inconnue est utilis�e
*@return Le nom du fichier entr�e en argument.
*/
char* lire_args(int argc, char* argv[]);

/**
*@desc Met en forme la r�ponse du programme.
*/
void reponse(vector<vector<int>>& clauses,vector<bool>& rep);
