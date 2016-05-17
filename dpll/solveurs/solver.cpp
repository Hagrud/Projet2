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

bool solveur_naif::dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos){
  //On vérifie si l'instance valide SAT.
  if(check(clauses, varsStates)){return true;}
  
  if(pos<nV){
    //On vérifie si l'instance de SAT est vérifiable en changeant seulement les variables suivantes.
    bool val = dpll_rec(clauses, varsStates, nV, pos+1);
    if(val){return true;}
    
    //Sinon on chance celle-ci
    varsStates[pos] = !varsStates[pos];
    val = dpll_rec(clauses, varsStates, nV, pos+1);
    if(val)
      return true;
    else{
      varsStates[pos] = true;
      return false;
    }
  }
  else{
    varsStates[pos] = !varsStates[pos];
    if(check(clauses, varsStates))
      return true;
    else{
      varsStates[pos] = true;
      return false;
    }
  }
  return false;
}
