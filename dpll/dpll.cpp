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

vector<bool> dpll(vector<vector<int>>& clauses, int nV){


    vector<int> paris;				        //Tableau des paris
    vector<vector<int>> deductions;		    //Déductions en fonction des paris
    vector<int> varsStates(nV, -1);		    //Valeur des variables (-1:null,0:false,1:true)
    vector<bool> varsStatesBool(nV, false);
    vector<bool> clauses_valides(clauses.size(), false);    //Liste des clauses validées
    vector<vector<int>> deductions_clauses;                 //Déduction des clauses valides a cause des paris.

    paris.resize(0);				        //On a aucuns paris
    deductions.resize(0);			        //et aucunes déductions
    deductions.push_back({});
    deductions_clauses.resize(0);
    deductions_clauses.push_back({});

    while(true){

        /** Temps on fait toutes les déductions possibles sur le paris. **/
        while(unitProp(clauses, paris, deductions, varsStates, clauses_valides,deductions_clauses) || polarite_unique(clauses, paris, deductions, varsStates)){}

        /** On vérifie si le paris que l'on a fait est plausible. **/
        if(!checkWithNull(clauses, varsStates)){

            /** On supprime les déductions associées **/
            for(int var:deductions.back()){
                varsStates[abs(var)-1] = -1;
            }
            for(int clause_id:deductions_clauses.back()){
                clauses_valides[clause_id] = false;
            }

            /** Si on avait un paris il faut l'enlever **/
            if(!paris.empty()){
            	deductions.pop_back();
            	deductions.back().push_back(-paris.back());
                varsStates[paris.back()-1] = 0; //WARNING POUR PLUS TARD
            	paris.pop_back();
            }
            /** Sinon le problème n'est pas satisfiable. **/
            else{
                for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
                return varsStatesBool;
            }
        }
        /** Sinon on vérifie si l'instance en cours vérifie le problème SAT (si oui on retourne) **/
        else{
            for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
            if(check(clauses,varsStatesBool)){return varsStatesBool;}
        }

        /** On fait un paris **/
        bool change = false;
        for(unsigned int varID = 0;varID<varsStates.size();varID++){
            if(varsStates[varID]==-1){
                paris.push_back(varID+1);
                varsStates[varID] = 1;
                change = true;
                break;
            }
        }
        if(change){
            deductions.push_back({});
            deductions_clauses.push_back({});
        }


        /** Si on n'a pas réussi a faire de paris le précédent était faux**/
        if(!change){

            /** On supprime les déductions associées **/
            for(int var:deductions.back()){
                varsStates[abs(var)-1] = -1;
            }
            for(int clause_id:deductions_clauses.back()){
                clauses_valides[clause_id] = false;
            }

            /** Si on avait un paris il faut l'enlever **/
            if(!paris.empty()){
            	deductions.pop_back();
            	deductions.back().push_back(-paris.back());
            	varsStates[paris.back()-1] = 0;//WARNING POUR PLUS TARD
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

bool unitProp(vector<vector<int>>& clauses,
              vector<int>& paris,vector<vector<int>>& deductions,
              vector<int>& varsStates,
              vector<bool>& clauses_valides,
              vector<vector<int>>& deductions_clauses){

    vector<int> vue(varsStates.size(), 0);
    vector<int> vue_en_cour(varsStates.size(), 0);


    /** On va vérifier chaque clause une par une. **/
    vector<int> clause;
	for(unsigned int clause_id = 0;clause_id < clauses.size(); clause_id++){

        /** Si la clause est déja validé on ne la traite pas **/
        if(!clauses_valides[clause_id])
            continue;

        clause = clauses[clause_id];

        /** On vérifie si la clause est "unitaire" **/
		for(int var:clause){

			/** On vérifie le nombre de variable libre **/
			if(varsStates[abs(var)-1]==-1){
				int compteur = 0;
				for(auto var2:clause){
					if(varsStates[abs(var2)-1]==-1){
						compteur++;
						if(compteur>1){break;}
					}

					/** On vérifie au passage si la clause n'est pas déjà satisfaite **/
					else if(varsStates[abs(var2)-1]==var2/abs(var2)){
						compteur=2;
						clauses_valides[clause_id] = true;
						deductions_clauses.back().push_back(clause_id);
					}

				}

				/** On fixe la variable si on a une clause unitaire **/
				if(compteur==1){
					if(var<0)
						varsStates[-var-1]=0;
					else
						varsStates[var-1]=1;
					deductions.back().push_back(var);
                    clauses_valides[clause_id] = true;
                    deductions_clauses.back().push_back(clause_id);
					return true;
				}
				break;

			}

			/** On vérifie au passage si la clause n'est pas déjà satisfaite **/
			if((var>0&&varsStates[var-1]==1)||(var<0&&varsStates[-var-1]==0)){
                clauses_valides[clause_id] = true;
                deductions_clauses.back().push_back(clause_id);
				break;
			}
		}
	}

	return false;
}

bool polarite_unique(vector<vector<int>>& clauses,
                     vector<int>& paris,
                     vector<vector<int>>& deductions,
                     vector<int>& varsStates){

    vector<bool> var_true(varsStates.size(), false);    //Liste des variables qui apparaissent avec la polarité positive.
    vector<bool> var_false(varsStates.size(), false);   //Liste des variables qui apparaissent avec la polarité négative.

    /** Lecture de chaques variables. **/
    for(vector<int> clause:clauses){
        for(int var:clause){
            /** Si une variable n'est pas fixée on l'enregistre. **/
            if(varsStates[abs(var)-1]==-1){
                if(var>0){
                    var_true[var-1]=true;
                }
                else{
                    var_false[-var-1]=true;
                }
            }
        }
    }

    /** On vérifie si des variables ne sont vuent qu'avec une seule polaritée. **/
    bool change = false;
    for(unsigned int i = 0;i<var_true.size();i++){
        if(var_true[i] && !var_false[i]){
            deductions.back().push_back(i+1);
            varsStates[i] = 1;
            change = true;
        }
        else if(!var_true[i] && var_false[i]){
            deductions.back().push_back(-i-1);
            varsStates[i] = 0;
            change = true;
        }
    }

    return change;
}
