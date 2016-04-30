#include "solveur_deduction.h"


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


    while(true){

        Literal &last_paris = literals[paris.back()];
        while(dedUnitaire(clauses, literals, last_paris) || polarite_unique(clauses, literals, last_paris)){}

        if(!checkWithNull(clauses, literals)){  //On vérifie si on est pas dans une impasse.
            if(!backtrack(literals, paris)){
                return to_vector(literals);
            }
        }
        else{

            if(check(clauses, literals))
                return to_vector(literals);
        }

        if(!parieur.parier(literals, paris)){   //On fait un paris.

            if(!backtrack(literals, paris)){
                return to_vector(literals);
            }

        }

    }
}
