#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"


using namespace std;

void init_dpll(vector<vector<int>> clauses, int nV, bool wl);

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);

vector<bool> dpll(vector<vector<int>>& clauses, int nV);

bool unitProp(vector<vector<int>>& clauses,vector<int>& paris,vector<vector<int>>& deductions,vector<int>& varsStates);

vector<bool> dpll_naif(vector<vector<int>> clauses, int nV);
