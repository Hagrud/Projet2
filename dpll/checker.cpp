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

bool check(vector<Clause*>& clauses, vector<Literal>& literals){
    for(Clause* c:clauses){

        if(c->isValid())
            continue;

        vector<int> clause = c->getVariables();
        if(clause.empty()){return false;}

        bool state = false;
        for(int var:clause){
            if( (var>0) == (literals[abs(var)].getValue()) ){

                Literal &lit = literals[abs(var)];
                lit.addValidate_Clause(c);

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

bool checkWithNull(vector<Clause*>& clauses, vector<Literal>& literals){
    for(unsigned int id = 0; id<clauses.size(); id++){

		Clause* c = clauses[id];
        if(c->isValid())
            continue;

        vector<int> clause = c->getVariables();
        if(clause.empty()){return false;}

        bool state = false;
        for(int var:clause){
            if(((var>0) == (literals[abs(var)].getValue())) || !literals[abs(var)].isFixed()){

                if(literals[abs(var)].isFixed()){
                    Literal &lit = literals[abs(var)];
                    lit.addValidate_Clause(c);
                }

                state = true;
                break;
            }
        }
        if(!state){
			clause_issue = id;
            return false;
        }
    }
    return true;
}


unsigned int get_clause_issue_id(){
	return clause_issue;
}
