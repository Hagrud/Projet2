#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"


using namespace std;

/**
* @desc Cherche r�cursivement sur toutes les instances possibles des variables une solution possible au probl�me SAT.
* @return True si l'instance est solution du probl�me.
*/
bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);

/**
* @desc Cherche un solution au probl�me SAT pos� dans clauses
* @return instance des variables solutions de SAT. (ou une instance non solution si il n'y a pas de solution.)
*/
vector<bool> dpll_naif(vector<vector<int>> clauses, int nV);

/**
*@desc Cherche une solution au probl�me SAT pos� dans clauses avec propagation unitaire et recherche de polarit� unique.
*@return instance des variables solutions de SAT. (ou une instance non solution si il n'y a pas de solution.
*/
vector<bool> dpll(vector<vector<int>>& clauses, int nV);

/**
*@desc Cherche une clause unitaire.
*@return True si la fonction a trouv� une clause unitaire.
*/
bool unitProp(vector<vector<int>>& clauses,
              vector<int>& paris,
              vector<vector<int>>& deductions,
              vector<int>& varsStates,
              vector<bool>& clauses_valides,
              vector<vector<int>>& deductions_clauses);

/**
*@desc Cherche une variable qui a une polarit� unique.
*@return True si la fonction a trouv� une variable qui a une polarit� unique.
*/
bool polarite_unique(vector<vector<int>>& clauses,vector<int>& paris,vector<vector<int>>& deductions,vector<int>& varsStates);


