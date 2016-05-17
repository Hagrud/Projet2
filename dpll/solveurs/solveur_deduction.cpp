#include "solveur_deduction.h"

Solveur_deduction::Solveur_deduction(){}
Solveur_deduction::Solveur_deduction(Parieur p, Smt s){
    parieur = p;
    smt = s;
}

vector<bool> Solveur_deduction::solve(vector<vector<int>>& clauses_, int nV){

	//Initialisation des paris
    vector<int> paris(1,0);

    //Initialisation des clauses
    vector<Clause*> clauses;
    clauses.resize(0);
    for(vector<int> c : clauses_){
        clauses.push_back(new Clause(c));
    }

    //Initialisations des variables.
    vector<Literal> literals;
    literals.resize(0);
    for(int i = 0;i<nV+1;i++){
        literals.push_back(Literal(i));
    }

	pre_solve(clauses, literals, paris);

    while(true){

		deduction(clauses, literals, paris);

		//Temps qu'on est dans une impasse on backtrack.
        while(!checkWithNull(clauses, literals)){
            if(!backtrack(clauses, literals, paris)){
                return to_vector(literals);
            }
            deduction(clauses, literals, paris);
        }

        //Si l'instance qu'on ? est valide on retourne.
        if(check(clauses, literals)){
            if(!smt.valid(to_vector(literals))){
              addReverse(clauses, literals);
            }
            else{
              return to_vector(literals);
            }
        }

        if(!parieur.parier(literals, paris)){   //On fait un paris.

        	//Si on a pas pu faire de paris on retourne en arriere
            if(!Solveur_deduction::backtrack(clauses, literals, paris)){
                return to_vector(literals);
            }
        }

    }

    return to_vector(literals);
}

bool Solveur_deduction::backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){

	//Si on a pas de paris on ne peut pas backtrack.
    if(paris.size()<=1){
        return false;
    }

    Literal &lit = literals[paris.back()];
    paris.pop_back();

    //On supprime toutes les d?ductions.
    for(int deduction : lit.getDeductions()){
        Literal &ded = literals[deduction];
        ded.setFixed(false);
    }

    lit.clearDeduct();
    lit.setValue(!lit.getValue());
    lit.setPari(false);
    lit.setBackTracked(true);

    Literal &precedent = literals[paris.back()];
    precedent.addDeduct(lit.getId());
    lit.setLevel(precedent.getLevel());

    return true;
}

void Solveur_deduction::pre_solve(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
	Literal &last_paris = literals[paris.back()];
    while(dedUnitaire(clauses, literals, last_paris) || polarite_unique(clauses, literals, last_paris)){}
}

void Solveur_deduction::deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
	Literal &last_paris = literals[paris.back()];
    while(dedUnitaire(clauses, literals, last_paris) || polarite_unique(clauses, literals, last_paris)){}
}

void Solveur_deduction::addReverse(vector<Clause*>& clauses, vector<Literal>& literals){
  vector<int> n_clause;
  n_clause.resize(0);
  
  for(Literal &lit : literals){
    if(lit.getId() == 0)
      continue;
    
    if(lit.getValue())
      n_clause.push_back(-lit.getId());
    else{
      n_clause.push_back(lit.getId());
    }
  }
  
  clauses.push_back(new Clause(n_clause));
  
}

