#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>

using namespace std;

/**
* @desc Vérifie qu'une instance de variables vérifie un problème de type SAT.
* @return True si toutes les clauses sont vérifiées.
*/
bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);

bool checkWithNull(vector<vector<int>>& clauses, vector<int>& varsStates);

unsigned int get_clause_issue_id();
