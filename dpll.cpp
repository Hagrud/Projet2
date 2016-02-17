#include "dpll.h"
#include "parser.h"

vector<bool> dpll(vector<vector<int>> clauses, int nV){
	vector<bool> varsStates(nV, true);

	dpll_rec(clauses, varsStates, nV, 0);

	return varsStates;
}

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos){

	if(check(clauses, varsStates)){return true;}

    if(pos<nV){
        bool val = dpll_rec(clauses, varsStates, nV, pos+1);
		if(val){return true;}

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

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates){
	for(auto vec:clauses){

		bool state = false;
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

void decide(vector<vector<int>>& clauses, vector<bool>& varStates){}


int main(int argc, char* argv[]){

    if(argc<=1){
            cout << "no input file" << endl;
            return 0;
    }

    pair<vector<vector<int>>,int> parsed = parse(argv[1]);
	vector<vector<int>> clauses = parsed.first;
	if(parsed.second==0){
        return 1;
	}

	vector<bool> rep = dpll(clauses, parsed.second);

    if(check(clauses, rep)){
        cout << "s SATISFIABLE" << endl;
        for(unsigned int i = 0;i<rep.size();i++){
            if(rep[i])
                cout << i+1 << " ";
            else
                cout << "-" << i+1 << " ";
        }
        cout << 0 << endl;
    }
    else{cout << "s UNSATISFIABLE" << endl;}


	return 0;
}
