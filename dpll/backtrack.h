#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include "checker.h"
#include "paris.h"
#include "deduction.h"
#include "graph.h"

bool backtrack(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV, bool nwl);

bool conflit_graph(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV);

int getUIP(vector<vector<int>>& graph);

void deduct_clause(vector<vector<int>>& graph, vector<vector<int>>& clauses, vector<int>& varsStates, int uip);

void construct_graph_recur(vector<vector<int>>& clauses,
						   vector<int>& deduction,
						   vector<vector<int>>& graph,
						   vector<int>& source_deduction,
						   int clause_id, int var_id);
