#include <vector>
#include <iostream>
#include <stdlib.h>


using namespace std;

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);
