#include "backtrack.h"

bool backtrack(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV, bool nwl){

        /** On vérifie si le paris que l'on a fait est plausible. **/
        if(!checkWithNull(clauses, varsStates)){
			if(!nwl){
				conflit_graph(clauses, paris, deductions, varsStates, clauses_valides, deductions_clauses,
			   source_deduction, varsStatesBool, nV);
			}

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

bool conflit_graph(vector<vector<int>>& clauses,    vector<int>& paris,
               vector<vector<int>>& deductions, vector<int>& varsStates,
               vector<bool>& clauses_valides,   vector<vector<int>>& deductions_clauses,
			   vector<int>& source_deduction,   vector<bool>& varsStatesBool,
			   int nV){
	unsigned int conflit = get_clause_issue_id();
	//int var_conflict = 0;

	//for(int var:clauses[conflit]){
	//	cout << var << endl;
	//	if(find(deductions.back().begin(), deductions.back().end(), -var) != deductions.back().end()){
	//		var_conflict = var;
	//		break;
	//	}
	//}

	vector<vector<int>> graph(nV+1, vector<int>());
	construct_graph_recur(clauses, deductions.back(), graph, source_deduction, conflit, 0);
	check_conflict(graph, deductions.back(), paris, varsStates);
	//cout << "var conflict :: " << var_conflict << endl;
	return true;
}

void construct_graph_recur(vector<vector<int>>& clauses, 
						   vector<int>& deduction, 
						   vector<vector<int>>& graph,
						   vector<int>& source_deduction, 
						   int clause_id, int var_id){

	if(clause_id == -1){return;}

	for(int var:clauses[clause_id]){
		if(graph[abs(var)].empty()){			
				graph[abs(var)].push_back(var_id);

				if(find(deduction.begin(), deduction.end(), -var) != deduction.end())
					construct_graph_recur(clauses, deduction, graph, source_deduction, source_deduction[abs(var)-1], var);
		}
		else{
				graph[abs(var)].push_back(var_id);
		}
	}
}
