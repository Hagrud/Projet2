#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"
#include "paris.h"
#include "deduction.h"


using namespace std;

/**
* @desc Cherche récursivement sur toutes les instances possibles des variables une solution possible au problème SAT.
* @return True si l'instance est solution du problème.
*/
bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);

/**
* @desc Cherche un solution au problème SAT posé dans clauses
* @return instance des variables solutions de SAT. (ou une instance non solution si il n'y a pas de solution.)
*/
vector<bool> dpll_naif(vector<vector<int>> clauses, int nV);

/**
*@desc Cherche une solution au problème SAT posé dans clauses avec propagation unitaire et recherche de polarité unique.
*@return instance des variables solutions de SAT. (ou une instance non solution si il n'y a pas de solution.
*/
vector<bool> dpll(vector<vector<int>>& clauses, int nV, bool polarite_active);




