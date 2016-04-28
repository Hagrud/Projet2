#include "solver.h"


vector<bool> solveur_naif::solve(vector<vector<int>>& clauses, int nV){
	vector<bool> varsStates(nV, true);

	dpll_rec(clauses, varsStates, nV, 0);

	return varsStates;
}

/**
vector<bool> solveur_2::solve(vector<vector<int>>& clauses, int nV){
    vector<Literal> literals;
    literals.resize(0);
    for(int i = 0;i<nV;i++){
        literals.push_back(Literal(i));
    }


    vector<bool> varsStates(nV, true);
    return varsStates;
}**/
