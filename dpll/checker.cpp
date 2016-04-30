#include "checker.h"

static unsigned int clause_issue = 0;
//static int var_issue = 0;

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates){
	//Pour chaque clauses on vérifie si elle est vérifié ou non.
	for(auto vec:clauses){
		bool state = false;
		if(vec.empty()){return false;}
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

    for(unsigned int clause_id = 0; clause_id<clauses.size(); clause_id++){
		vector<int> vec = clauses[clause_id];
		bool state = false;
		if(vec.empty()){return false;}
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
		if(!state){
			clause_issue = clause_id;
			return false;
		}
	}
	return true;
}

bool check(vector<vector<int>>& clauses, vector<Literal>& literals){
    for(vector<int> clause:clauses){

        if(clause.empty()){return false;}

        bool state = false;
        for(int var:clause){
            if( (var>0) == (literals[abs(var)].getValue()) ){
                state = true;
                break;
            }
        }
        if(!state){
            return false;
        }
    }
    return true;
}

bool checkWithNull(vector<vector<int>>& clauses, vector<Literal>& literals){
    for(vector<int> clause:clauses){

        if(clause.empty()){return false;}

        bool state = false;
        for(int var:clause){
            if(((var>0) == (literals[abs(var)].getValue())) || !literals[abs(var)].isFixed()){
                state = true;
                break;
            }
        }
        if(!state){
            return false;
        }
    }
    return true;
}


unsigned int get_clause_issue_id(){
	return clause_issue;
}
