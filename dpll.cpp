#include <vector>
#include <iostream>
#include "parser.h"

using namespace std;

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);
bool check(vector<vector<int>>& clauses, vector<bool>& varsStates);
vector<bool> dpll(vector<vector<int>> clauses, int nV);

vector<bool> dpll(vector<vector<int>> clauses, int nV){
	vector<bool> varsStates(nV, true);

	dpll_rec(clauses, varsStates, nV, 0);

	//varsStates[i];
	//varsStates.push_back(k);
	return varsStates;
}

bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos){

	if(check(clauses, varsStates)){return true;}

	if(pos<nV-1){
		bool val = dpll_rec(clauses, varsStates, nV, pos+1);
		if(val){return true;}

		if(varsStates[pos]){
			varsStates[pos] = false;
			dpll_rec(clauses, varsStates, nV, pos);
		}
		else{
			varsStates[pos] = true;
			return false;
		}
	}
	return false;
}

bool check(vector<vector<int>>& clauses, vector<bool>& varsStates){
	for(auto vec:clauses){

        for(auto b:vec){
            cout << b << " ";
        }
        cout << endl;

		bool state = false;
		for(auto var: vec){
            cout << var << endl;
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

int main(){
	vector<vector<int>> clauses = parse("test.cnf");
	vector<bool> rep = dpll(clauses, 3);

	for(vector<int> clause:clauses){
        for(auto b:clause){
            cout << b << " ";
        }
        cout << endl;
	}

    cout << "END CHECK !" << endl;
    if(check(clauses, rep)){
        cout << "accepted output :" << endl;
        for(auto b:rep){
            cout << b << endl;
        }
    }
    else{ cout << "no possible output :" << endl;}


	return 0;
}
