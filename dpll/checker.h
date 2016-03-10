#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>

using namespace std;

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);

bool checkWithNull(vector<vector<int>>& clauses, vector<int>& varsStates);
