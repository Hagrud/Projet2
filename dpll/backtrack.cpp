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
                source_deduction[abs(var)-1]=-1;
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

    if(paris.empty())
        return true;

	unsigned int conflit = get_clause_issue_id();

    //cout << "source_deduction = [";
    //for(int p:source_deduction){cout << p << " ";} cout << "]" << endl;

    /** Construction du graphe **/
	vector<vector<int>> graph(nV+1, vector<int>());
	construct_graph_recur(clauses, deductions.back(), paris,  graph, source_deduction, conflit, 0);

    /** Récupération de l'uip **/
    int uip = abs(paris.back());     //getUIP(graph);

    /** Affichage du graphe (si besoin) **/
	check_conflict(graph, deductions.back(), varsStates, paris,  uip);

    //cout << "deduction = [";
    //for(int p:deductions.back()){cout << p << " ";} cout << "]" << endl;
    //cout << "clause conflit = [";
    //for(int p:clauses[conflit]){cout << p << " ";} cout << "]" << endl;
    //cout << "graph = [";
    //for(auto d:graph){cout << endl << " [";for(int p:d){cout << " " << p << " ";}cout << "]";}cout <<"]";

	/** Clause learning **/
	if(deductions.back().size() != 0){   //On ajoute pas de clause si on a eu aucunes déductions avant le conflit.
    //        deduct_clause(graph, clauses, varsStates, uip);
    //        clauses_valides.push_back(false);
	}


	return true;
}


int getUIP(vector<vector<int>>& graph){
    //TODO
    return 0;
}

void deduct_clause(vector<vector<int>>& graph, vector<vector<int>>& clauses, vector<int>& varsStates,int uip){
    vector<int> a_voir;
    vector<int> vue;
    vector<int> clause;

    clause.resize(0);
    a_voir.resize(0);
    vue.resize(0);

    a_voir.push_back(uip);
    vue.push_back(0);
    while(!a_voir.empty()){
        int sommet  = a_voir.back();
        a_voir.pop_back();
        if(!(find(vue.begin(), vue.end(), sommet) != vue.end())){
            vue.push_back(sommet);
            for(int voisin:graph[sommet]){
                    a_voir.push_back(voisin);
            }
        }
    }

    for(unsigned int sommet_id = 1; sommet_id<graph.size(); sommet_id++){
        for(int sommet:graph[sommet_id]){
                if((find(vue.begin(), vue.end(), -sommet) != vue.end()) && sommet_id != (unsigned) uip){
                    if(varsStates[sommet_id]==0)
                        clause.push_back(sommet_id);
                    else
                        clause.push_back(-sommet_id);
                    break;
                }
        }
    }
    clause.push_back(-uip);

    //cout << "vue : [ ";
    //for(int p:vue){cout << p << " ";} cout << "]" << endl;
    //cout << "uip = " << uip << endl;
    //cout << "graph = [";
    //for(auto d:graph){cout << endl << " [";for(int p:d){cout << " " << p << " ";}cout << "]";}cout <<"]";
    //cout << "add clause : [ ";
    //for(int p:clause){cout << p << " ";} cout << "]" << endl;

    clauses.push_back(clause);
}

void construct_graph_recur(vector<vector<int>>& clauses,
						   vector<int>& deduction,
						   vector<int>& paris,
						   vector<vector<int>>& graph,
						   vector<int>& source_deduction,
						   int clause_id, int var_id){

    //cout << "var id : " << var_id << endl;
    /** Si la variables précédentes est un paris on stop **/
	if(clause_id == -1){
		if(find(deduction.begin(), deduction.end(), -var_id) != deduction.end()){
			graph[abs(paris.back())].push_back(var_id);
		}
		return;
	}

    /** Pour chaque variables dans la clause en cause on va l'ajouter au graphe si besoin. **/
    //cout << "clause : [ ";
    //for(int p:clauses[clause_id]){cout << p << " ";} cout << "]" << endl;

	for(int var:clauses[clause_id]){
		if(abs(var)==abs(var_id)){continue;}
        //cout << var_id << "var in clause : " << var << endl;
        /** Si l'on a jamais vu la variable **/
		if(graph[abs(var)].empty()){
				graph[abs(var)].push_back(var_id);

                /** Si la variable fait partie des déductions on continue. **/
				if(find(deduction.begin(), deduction.end(), -var) != deduction.end())
					construct_graph_recur(clauses, deduction, paris, graph, source_deduction, source_deduction[abs(var)-1], var);
		}
		else{
				graph[abs(var)].push_back(var_id);
		}
	}
}
