#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"
#include "paris.h"

using namespace std;

/**
*@desc Cherche une clause unitaire.
*@return True si la fonction a trouvé une clause unitaire.
*/
bool unitProp(vector<vector<int>>& clauses,
              vector<int>& paris,
              vector<vector<int>>& deductions,
              vector<int>& varsStates,
              vector<bool>& clauses_valides,
              vector<vector<int>>& deductions_clauses,
			  vector<int>& source_deduction);

/**
*@desc Cherche une variable qui a une polarité unique.
*@return True si la fonction a trouvé une variable qui a une polarité unique.
*/
bool polarite_unique(vector<vector<int>>& clauses,
                     vector<int>& paris,
                     vector<vector<int>>& deductions,
                     vector<int>& varsStates);


bool dedUnitaire(vector<Clause *>& clauses, vector<Literal>& literals, Literal &paris);
bool polarite_unique(vector<Clause *>& clauses, vector<Literal>& literals, Literal &paris);
