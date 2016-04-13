#include "graph.h"


static bool VOIR = true;

void check_conflict(){

	if(!VOIR){
		return;
	}		


	string in;
	while(true){
		cout << "conflit : (g c t)" << endl;
		cin >> in;
		if(in == "g"){
			generate_conflict_graph();
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


void generate_conflict_graph(){

}

void init_graph_cpp(bool voir){
	VOIR = voir;
}
