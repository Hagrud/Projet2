#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"


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
vector<bool> dpll(vector<vector<int>>& clauses, int nV);

/**
*@desc Cherche une clause unitaire.
*@return True si la fonction a trouvé une clause unitaire.
*/
bool unitProp(vector<vector<int>>& clauses,
              vector<int>& paris,
              vector<vector<int>>& deductions,
              vector<int>& varsStates,
              vector<bool>& clauses_valides,
              vector<vector<int>>& deductions_clauses);

/**
*@desc Cherche une variable qui a une polarité unique.
*@return True si la fonction a trouvé une variable qui a une polarité unique.
*/
bool polarite_unique(vector<vector<int>>& clauses,vector<int>& paris,vector<vector<int>>& deductions,vector<int>& varsStates);


