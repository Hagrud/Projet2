#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>

#include "../objets/literal.h"
#include "../objets/clause.h"

using namespace std;

/**
* @desc V?rifie qu'une instance de variables v?rifie un probl?me de type SAT.
* @return True si toutes les clauses sont v?rifi?es.
*/
bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);

bool check(vector<Clause*>& clauses, vector<Literal>& literals);

bool checkWithNull(vector<Clause*>& clauses, vector<Literal>& literals);

unsigned int get_clause_issue_id();
