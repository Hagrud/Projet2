#include "dpll.h"
#include "parser.h"

vector<bool> dpll_naif(vector<vector<int>> clauses, int nV){
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

vector<bool> dpll(vector<vector<int>>& clauses, int nV){
    vector<int> paris;
    vector<vector<int>> deductions;
    vector<int> varsStates(nV, -1);
    vector<bool> varsStatesBool(nV, false);
    paris.resize(0);
    deductions.resize(0);
    deductions.push_back({});
    while(true){
        cout << "unit" << endl;
        while(unitProp(clauses, paris, deductions, varsStates)){}
        cout << "/unit" << endl;

        cout << "check1" << endl;

        if(!checkWithNull(clauses, varsStates)){
            for(auto var:deductions.back()){
                varsStates[abs(var)] = -1;
            }
            deductions.pop_back();
            cout<<paris.back()<<endl;
            deductions.back().push_back(-paris.back());
            paris.pop_back();
        }
        cout << "/check1" << endl;

        for(auto p:varsStates){cout<<p<<" ";}
        cout << endl;

        //Decide
        bool change = false;
        for(int varID = 0;varID<varsStates.size();varID++){
            if(varsStates[varID]==-1){
                paris.push_back(varID+1);
                varsStates[varID] = 1;
                change = true;
                break;
            }
        }

        deductions.push_back({});

        if(!change){
            for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
            return varsStatesBool;
        }
    }
}

bool checkWithNull(vector<vector<int>>& clauses, vector<int>& varsStates){

    for(auto vec:clauses){
		bool state = false;
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

bool unitProp(vector<vector<int>>& clauses,vector<int>& paris,vector<vector<int>>& deductions,vector<int>& varsStates){
    for(auto p:varsStates){cout << p << " ";}cout<<endl;
	for(auto vec:clauses){
		for(auto var:vec){
            if(var<0){
                if(varsStates[-var-1]==-1){
                    int compteur = 0;
                    for(auto var2:vec){
                        if(varsStates[abs(var2)-1]==-1){compteur++;if(compteur>1){break;}}

                    }
                    if(compteur==1){
                            varsStates[-var-1] = 0;
                            cout<<"back"<<endl;
                            deductions.back().push_back(var);
                            cout<<"/back"<<endl;
                            return true;
                    }
                    break;
                }
                if(varsStates[-var-1]==0){
					break;
				}
            }
            else{
                if(varsStates[var-1]==-1){
                    int compteur = 0;
                    for(auto var2:vec){
                        if(varsStates[abs(var2)-1]==-1){compteur++;if(compteur>1){break;}}
                    }
                    if(compteur==1){
                            varsStates[var-1] = 1;
                            deductions.back().push_back(var);
                            return true;
                    }
                    break;
                }
                if(varsStates[var-1]==1){
					break;
				}
            }
		}
	}
	return false;
}


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

	//vector<bool> rep = dpll_naif(clauses, parsed.second);

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
