#include "solveur_deduction.h"


Solveur_deduction::Solveur_deduction(Parieur p){
    parieur = p;
}



vector<bool> Solveur_deduction::solve(vector<vector<int>>& clauses, int nV){
    vector<bool> varsStates(nV, false);

    vector<int> paris(1,0);


    vector<Literal> literals;
    literals.resize(0);
    for(int i = 0;i<nV+1;i++){
        literals.push_back(Literal(i));
    }


    while(true){

        //Deduction

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
