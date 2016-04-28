#include "dpll.h"

vector<bool> dpll_naif(vector<vector<int>> clauses, int nV){
	vector<bool> varsStates(nV, true);

	dpll_rec(clauses, varsStates, nV, 0);

	return varsStates;
}

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos){
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

vector<bool> dpll(vector<vector<int>>& clauses, int nV, bool polarite_active){


    vector<int> paris;			        //Tableau des paris
    vector<vector<int>> deductions;		    					//Déductions en fonction des paris
	vector<int> source_deduction(nV, -1);		//id de la clause qui est source de la déduction
    vector<int> varsStates(nV, -1);		    //Valeur des variables (-1:null,0:false,1:true)
    vector<bool> varsStatesBool(nV, false);
    vector<bool> clauses_valides(clauses.size(), false);    //Liste des clauses validées
    vector<vector<int>> deductions_clauses;                 //Déduction des clauses valides a cause des paris.

    paris.resize(0);				        //On a aucuns paris
    deductions.resize(0);			        //et aucunes déductions
    deductions.push_back({});
    deductions_clauses.resize(0);
    deductions_clauses.push_back({});

	set_libre(nV);

    while(true){

        /** Temps on fait toutes les déductions possibles sur le paris. **/
        while(unitProp(clauses, paris, deductions, varsStates, clauses_valides,deductions_clauses, source_deduction) ||
              ((polarite_active || paris.size() == 0) && polarite_unique(clauses, paris, deductions, varsStates))){}

		//
		//cout << "paris : [ ";
		//for(int p:paris){cout << p << " ";} cout << "]" << endl;
		//cout << "state : [ ";
		//for(int p:varsStates){cout << p << " ";} cout << "]" << endl;
		//cout << "deduction : [ ";
		//for(int p:deductions.back()){cout << p << " ";} cout << "]" << endl;
		//

        if(backtrack(clauses, paris, deductions, varsStates, clauses_valides,deductions_clauses, source_deduction, varsStatesBool,
                     nV, polarite_active)){
            return varsStatesBool;
        }

        /** On fait un paris **/
        bool change = make_paris(varsStates, paris);

        if(change){
            deductions.push_back({});
            deductions_clauses.push_back({});
        }


        /** Si on n'a pas réussi a faire de paris le précédent était faux**/
        if(!change){

            /** On supprime les déductions associées **/
            for(int var:deductions.back()){
                varsStates[abs(var)-1] = -1;
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
                return varsStatesBool;
            }
        }
    }
}

