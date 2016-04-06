#include "deduction.h"


bool unitProp(vector<vector<int>>& clauses,
              vector<int>& paris,vector<vector<int>>& deductions,
              vector<int>& varsStates,
              vector<bool>& clauses_valides,
              vector<vector<int>>& deductions_clauses,
			  vector<int>& source_deduction){

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
					change_libre(-1);
					source_deduction[abs(var)-1] = clause_id;
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
                     vector<int>& varsStates,
					 vector<int>& source_deduction){

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
			change_libre(-1);
            change = true;
        }
        else if(!var_true[i] && var_false[i]){
            deductions.back().push_back(-i-1);
            varsStates[i] = 0;
			change_libre(-1);
            change = true;
        }
    }

    return change;
}
