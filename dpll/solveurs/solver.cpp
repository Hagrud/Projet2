#include "solver.h"

vector<bool> solveur::to_vector(vector<Literal>& literals){
    vector<bool> varsStates;
    varsStates.resize(0);

    for(Literal lit : literals){
        if(lit.getId() == 0)
            continue;

        varsStates.push_back(lit.getValue());
    }

    return varsStates;
}


vector<bool> solveur_naif::solve(vector<vector<int>>& clauses, int nV){
	vector<bool> varsStates(nV, true);

	dpll_rec(clauses, varsStates, nV, 0);

	return varsStates;
}
