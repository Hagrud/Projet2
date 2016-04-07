#include "backtrack.h"

bool backtrack(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV, bool wl){


        /** On vérifie si le paris que l'on a fait est plausible. **/
        if(!checkWithNull(clauses, varsStates)){

            /** On supprime les déductions associées **/
            for(int var:deductions.back()){
                varsStates[abs(var)-1] = -1;
                source_deduction[abs(var)-1]=0;
				change_libre(1);
            }
            for(int clause_id:deductions_clauses.back()){
                clauses_valides[clause_id] = false;
            }

            /** Si on avait un paris il faut l'enlever **/
            if(!paris.empty()){
            	deductions.pop_back();
            	deductions.back().push_back(-paris.back());
				if(varsStates[paris.back()-1] == 0){
					 varsStates[paris.back()-1] = 1;
				}
				else{
                	varsStates[paris.back()-1] = 0; //WARNING POUR PLUS TARD
				}

            	paris.pop_back();
            }
            /** Sinon le problème n'est pas satisfiable. **/
            else{
                for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
                return true;
            }
        }
        /** Sinon on vérifie si l'instance en cours vérifie le problème SAT (si oui on retourne) **/
        else{
            for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
            if(check(clauses,varsStatesBool)){return true;}
        }
        return false;
}
