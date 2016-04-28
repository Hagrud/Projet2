#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include "checker.h"
#include "paris.h"
#include "deduction.h"
#include "graph.h"

/**
*@desc fait le backtracking si necessaire.
*@return renvois True si le programme est fini (on a une clause satisfiable ou on est sur que ce n'est pas satisfiable).
*/
bool backtrack(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV, bool nwl);

/**
*@desc   Utilise un graphe des conflit et le clause learning pour faire le backtracking.
*@return renvois True si le programme est fini (on a une clause satisfiable ou on est sur que ce n'est pas satisfiable).
*/
bool conflit_graph(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV);

/**
*@desc   Chercher le point d'implication unique le plus proche du conflit (UIP).
*@return Un point d'implication unique.
*/
int getUIP(vector<vector<int>>& graph);

/**
*@desc   Déduit une nouvelle clause en fonction du conflit.
*/
void deduct_clause(vector<vector<int>>& graph, vector<vector<int>>& clauses, vector<int>& varsStates, int uip);

/**
*@desc   Construit le graphe du conflit.
*/
void construct_graph_recur(vector<vector<int>>& clauses,
						   vector<int>& deduction,
						   vector<int>& paris,
						   vector<vector<int>>& graph,
						   vector<int>& source_deduction,
						   int clause_id, int var_id);
