#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"
#include "paris.h"
#include "deduction.h"

bool backtrack(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV, bool wl);
