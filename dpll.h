#include <vector>
#include <iostream>
#include <stdlib.h>


using namespace std;

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);

vector<bool> dpll(vector<vector<int>>& clauses, int nV);

bool unitProp(vector<vector<int>>& clauses,vector<int>& paris,vector<vector<int>>& deductions,vector<int>& varsStates);

bool checkWithNull(vector<vector<int>>& clauses, vector<int>& varsStates);

vector<bool> dpll_naif(vector<vector<int>> clauses, int nV);
