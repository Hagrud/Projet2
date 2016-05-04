#include "graph.h"


static bool VOIR = true;

void check_conflict(vector<vector<int>>& graph, vector<int>& deduction, vector<int>& varsStates, vector<int>& paris, int uip){



	if(!VOIR){
		return;
	}


	string in;
	while(true){
		cout << "conflit : (g c t)" << endl;
		cin >> in;
		if(in == "g"){
			generate_conflict_graph(graph, deduction, varsStates, paris, uip);
			break;
		}
		else if(in == "c"){
			break;
		}
		else if(in == "t"){
			VOIR = false;
			break;
		}
		cout << "sortie non correct !" << endl;
	}

}


void generate_conflict_graph(vector<vector<int>>& graph, vector<int>& deduction, vector<int>& varsStates, vector<int>& paris, int uip){


	ofstream fichier("conflit_graph.dot", ios::out | ios::trunc);
	 if(fichier)
    {
                fichier << "digraph G {" << endl;
				fichier << "conflit  [style=filled,color=red];" << endl;

				for(int var:deduction){
					if(!graph[abs(var)].empty() && abs(var) != uip){
						fichier << var << " [style=filled,color=cyan];" << endl;
					}
				}
				fichier << uip << " [style=filled,color=yellow];" << endl;

            for(int sommet_id = 1; sommet_id<(int) graph.size(); sommet_id++){
					vector<int> sommet = graph[sommet_id];

					int sommet_value = sommet_id;
					if(varsStates[sommet_id-1]==0)
                        sommet_value = -sommet_id;



					for(int cible:sommet){

						if(cible==0)
							fichier << sommet_value << "->conflit;" << endl;
						else{
							cible = abs(cible);
							if(varsStates[cible-1]==0)
                       			cible = -abs(cible);
							if(varsStates[cible-1]==0)
                       			cible = -cible;
							fichier << sommet_value << "->" << cible << ";" << endl;
						}

					}
				}


				fichier << "}" << endl;
                fichier.close();
        }
        else
            cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void init_graph_cpp(bool voir){
	VOIR = voir;
}












