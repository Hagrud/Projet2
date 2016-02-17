#include <vector>
#include <iostream>


using namespace std;

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);

vector<bool> dpll(vector<vector<int>> clauses, int nV);
