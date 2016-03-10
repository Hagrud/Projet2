#include "checker.h"

/**
* @desc Vérifie qu'une instance de variables vérifie un problème de type SAT.
* @return True si toutes les clauses sont vérifiées.
*/
bool check(vector<vector<int>>& clauses, vector<bool>& varsStates){
	//Pour chaque clauses on vérifie si elle est vérifié ou non.
	for(auto vec:clauses){
		bool state = false;
		if(vec.empty()){continue;}
		for(auto var: vec){
			if(var<0){
				if(!varsStates[-var-1]){
					state = true;
					break;
				}
			}
			else{
				if(varsStates[var-1]){
					state = true;
					break;
				}
			}
		}
		if(!state){return false;}
	}
	return true;
}

bool checkWithNull(vector<vector<int>>& clauses, vector<int>& varsStates){
    for(auto vec:clauses){
		bool state = false;
		if(vec.empty()){continue;}
		for(auto var: vec){
			if(var<0){
				if(varsStates[-var-1] == -1 || varsStates[-var-1]==0){
					state = true;
					break;
				}
			}
			else{
				if(varsStates[var-1] == -1 || varsStates[var-1]==1){
					state = true;
					break;
				}
			}
		}
		if(!state){return false;}
	}
	return true;
}
