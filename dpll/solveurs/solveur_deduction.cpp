#include "solveur_deduction.h"

Solveur_deduction::Solveur_deduction(){}
Solveur_deduction::Solveur_deduction(Parieur p){
    parieur = p;
}

vector<bool> Solveur_deduction::solve(vector<vector<int>>& clauses_, int nV){

    vector<int> paris(1,0);

    vector<Clause*> clauses;
    clauses.resize(0);
    for(vector<int> c : clauses_){
        clauses.push_back(new Clause(c));
    }

    vector<Literal> literals;
    literals.resize(0);
    for(int i = 0;i<nV+1;i++){
        literals.push_back(Literal(i));
    }

	pre_solve(clauses, literals, paris);

    while(true){

		deduction(clauses, literals, paris);

        if(!checkWithNull(clauses, literals)){  //On verifie si on est pas dans une impasse.
            if(!backtrack(clauses, literals, paris)){
                return to_vector(literals);
            }
        }
        else{

            if(check(clauses, literals))
                return to_vector(literals);
        }

        if(!parieur.parier(literals, paris)){   //On fait un paris.

            if(!backtrack(clauses, literals, paris)){
                return to_vector(literals);
            }

        }

    }
}

bool Solveur_deduction::backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
    //cout << "backtack" << endl;
    if(paris.size()<=1){
        return false;
    }

    Literal &lit = literals[paris.back()];
    paris.pop_back();

    for(int deduction : lit.getDeductions()){
        Literal &ded = literals[deduction];
        ded.setFixed(false);
    }

    lit.clearDeduct();
    lit.setValue(!lit.getValue());
    lit.setPari(false);

    Literal &precedent = literals[paris.back()];
    precedent.addDeduct(lit.getId());
    //cout << "paris : [ "; for(auto p:paris){cout << p << " ";} cout << "]" << endl;
    //cout << "deduction : [ "; for(auto p:literals[paris.back()].getDeductions()){cout << p << " ";}cout << "]" << endl;
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
