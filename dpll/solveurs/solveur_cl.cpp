#include "solveur_cl.h"

Solveur_cl::Solveur_cl(Parieur p) : Solveur_deduction(p){
  show_graph = true;
}

void Solveur_cl::deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
	Literal &last_paris = literals[paris.back()];
	while(dedUnitaire(clauses, literals, last_paris)){}
}


bool Solveur_cl::backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
  //cout << "backtrack cl" << endl;
	Literal& uip = literals[learn_clause(clauses, literals, paris)];

	if(uip.getId() == 0)
		return false;

	Clause* last = clauses.back();
	int max = 0;
	for(int var : last->getVariables()){
		if(abs(var) == uip.getId()){
			if(var<0)
				uip.setValue(false);
			else
				uip.setValue(true);
		}
		else if(literals[abs(var)].getLevel() > max)
			max = literals[abs(var)].getLevel();
	}

	while(paris.size() > (unsigned int)max+1){
		Solveur_deduction::backtrack(clauses, literals, paris);
	}

	Literal &lit = literals[paris.back()];
	paris.pop_back();

	for(int deduction : lit.getDeductions()){
	        Literal &ded = literals[deduction];
	        ded.setFixed(false);
	}

    lit.clearDeduct();
    lit.setFixed(false);
    lit.setPari(false);

    Literal &precedent = literals[paris.back()];
    precedent.addDeduct(uip.getId());
    uip.setLevel(precedent.getLevel());


    return true;
	//return Solveur_deduction::backtrack(clauses, literals, paris);
}

int Solveur_cl::learn_clause(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
  if(paris.size() == 1) //Un conflit sans paris -> non satisfiable.
      return 0;
  
  unsigned int conflit = get_clause_issue_id();
  
  /** Construction du graphe **/
  vector<vector<int>> graph(literals.size(), vector<int>());
  create_graph(clauses, literals, literals[paris.back()].getDeductions(),
               paris, graph, clauses[conflit], 0);

  //cout << "graph : ["; for(auto p:graph){cout << "[ "; for(auto c:p){cout << " " << c << " ";} cout << " ]" << endl;}cout << " ] " << endl;

  /** Recuperation de l'uip **/ 
  //cout << "pre uip" << endl;
  int uip = get_uip(graph,literals[paris.back()].getDeductions(), paris.back());
  //cout << "post uip" << endl;
  
  //cout << "uip : " << uip << endl;
  //cout << "deductions [ ";for(auto p : literals[paris.back()].getDeductions()){cout << " " << p << " ";}cout << " ]" << endl;

  /** Affichage **/
  afficher_graphe(literals, graph, literals[paris.back()].getDeductions(), uip, paris.back());
  
  /** Clause learning **/
  learn(clauses, graph, literals, literals[paris.back()].getDeductions(),uip);
  return uip;
}

void Solveur_cl::learn(vector<Clause*>& clauses, vector<vector<int>>& graph, vector<Literal>& literals, vector<int> deduction,int uip){
	vector<int> clause;
	clause.resize(0);
	vector<int> chemin;

	for(int i = 0; i <(int) graph.size(); i++){
		if(find(deduction.begin(), deduction.end(), i) != deduction.end() && i != uip){
			continue;
		}
		chemin.resize(0);

		if(found_chemin(graph, chemin, uip, i)){
			if(literals[i].getValue())
				clause.push_back(-i);
			else
				clause.push_back(i);

		}
	}

	cout << "learn : ["; for(auto p : clause){cout << " " << p << " ";}cout << " ]" <<endl;
	clauses.push_back(new Clause(clause));
}

void Solveur_cl::create_graph(vector<Clause*>& clauses, vector<Literal>& literals,
                  vector<int> deduction,
                  vector<int>& paris, vector<vector<int>>& graph,
                  Clause* clause, int var_id){


  
  /** Si la variables precedentes est un paris on stop **/
  if(clause == nullptr){
    if(find(deduction.begin(), deduction.end(), abs(var_id)) != deduction.end()){
      graph[abs(paris.back())].push_back(var_id);
    }
    return;
  }
  
  //variables backtracked
  if(literals[abs(var_id)].isBackTracked()){
	  graph[paris.back()].push_back(var_id);
	  return;
  }

  /** Pour chaque variables dans la clause en cause on va l'ajouter au graphe si besoin. **/
  
  for(int var:clause->getVariables()){
    if(abs(var)==abs(var_id)){continue;}
    //cout << var_id << "var in clause : " << var << endl;
    /** Si l'on a jamais vu la variable **/
    if(graph[abs(var)].empty()){
      graph[abs(var)].push_back(var_id);
      
      /** Si la variable fait partie des deductions on continue. **/
      if(find(deduction.begin(), deduction.end(), abs(var)) != deduction.end())
        create_graph(clauses, literals, deduction, 
                     paris, graph, literals[abs(var)].get_first_validate_clause(), var);
    }
    else{
      graph[abs(var)].push_back(var_id);
    }
  }
  
}

int Solveur_cl::get_uip(vector<vector<int>>& graph, vector<int> possible_uip, int paris){

	//cout << "graph : [ "; for(auto c : graph){cout << " [ "; for(auto p : c){cout << " " << p << " ";}cout << " ]" << endl;}cout << " ]" << endl;

	vector<int> chemin;
	chemin.resize(0);
	found_chemin(graph, chemin, 0, paris);	//Probl?me sur le found chemin
	possible_uip = vector_and(chemin, possible_uip);
	int interdit;

	while(!possible_uip.empty()){
		//cout << "possible [ "; for(auto p : possible_uip){cout << " " << p << " ";}cout << "]" << endl;
		interdit = possible_uip.back();
		chemin.resize(0);
		if(!found_chemin(graph, chemin, interdit, paris)){
			return interdit;
		}
		possible_uip = vector_and(chemin, possible_uip);
	}

	return paris;
}

bool Solveur_cl::found_chemin(vector<vector<int>>& graph, vector<int>& chemin, int interdit, int sommet){
	//cout << "found chemin" << endl;
	//cout << "sommet : " << sommet << endl;
	for(int voisin : graph[sommet]){
		voisin = abs(voisin);
		//cout << sommet << " : voisin : " << voisin << endl;
		if(voisin == 0)
			return true;
		if(voisin == interdit)
			continue;

		//Devrait pas arriver
		//if(find(chemin.begin(), chemin.end(), voisin) != chemin.end())
		//	continue;

		chemin.push_back(voisin);

		if(found_chemin(graph, chemin, interdit, voisin))
			return true;

		chemin.pop_back();
	}

	return false;
}

vector<int> Solveur_cl::vector_and(vector<int> a, vector<int> b){
	vector<int> retour;
	retour.resize(0);

	//cout << "a [ "; for(auto p : a){cout << " " << p << " ";}cout << "]" << endl;
	//cout << "b [ "; for(auto p : b){cout << " " << p << " ";}cout << "]" << endl;

	for(int u: a){
		if(find(b.begin(), b.end(), u) != b.end()){
			retour.push_back(u);
		}
	}

	//cout << "r [ "; for(auto p : retour){cout << " " << p << " ";}cout << "]" << endl;
	return retour;
}

void Solveur_cl::afficher_graphe(vector<Literal>& literals, vector<vector<int>>& graph, vector<int> deduction, int uip, int paris){
  
  //cout << "deductions : ["; for(auto p : deduction){cout << " " << p << " ";}
  if(!show_graph){
    return;
  }
  
  /** Entrée utilisateur **/
  string in;
  while(true){
    cout << "conflit : (g c t)" << endl;
    cin >> in;
    if(in == "g"){
      break;
    }
    else if(in == "c"){
      return;
    }
    else if(in == "t"){
      show_graph = false;
      return;
    }
    cout << "sortie non correct !" << endl;
  }
  
  /** Création du graph **/
  
  ofstream fichier("conflit_graph.dot", ios::out | ios::trunc);
  if(fichier)
  {
    fichier << "digraph G {" << endl;
    fichier << "conflit  [style=filled,color=red];" << endl;
    
    if(paris != uip){
      if(!literals[paris].getValue())
        paris = - paris;
      fichier << paris << " [style=filled,color=blue];" << endl;
    }
    
    for(int var:deduction){
      if(!graph[abs(var)].empty() && abs(var) != uip){
        if(literals[var].getValue())
          fichier << var << " [style=filled,color=cyan];" << endl;
        else
          fichier << -var << " [style=filled,color=cyan];" << endl;
      }
    }
    if(!literals[uip].getValue())
      uip = -uip;
    fichier << uip << " [style=filled,color=yellow];" << endl;
    
    for(int sommet_id = 1; sommet_id<(int) graph.size(); sommet_id++){
      vector<int> sommet = graph[sommet_id];
      
      int sommet_value = sommet_id;
      if(!literals[sommet_id].getValue())
        sommet_value = -sommet_id;
      
      
      
      for(int cible:sommet){
        
        if(cible==0)
          fichier << sommet_value << "->conflit;" << endl;
        else{
          cible = abs(cible);
          if(!literals[cible].getValue())
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
