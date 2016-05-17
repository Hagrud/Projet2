#include "solveur_cl.h"

Solveur_cl::Solveur_cl(Parieur p, Smt s) : Solveur_deduction(p, s){
  show_graph = true;
}

void Solveur_cl::deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
	Literal &last_paris = literals[paris.back()];
	while(dedUnitaire(clauses, literals, last_paris)){}
}


bool Solveur_cl::backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
	//On r?cup?re l'uip et on apprend la nouvelle clause + affichage du graphe.
	Literal& uip = literals[learn_clause(clauses, literals, paris)];

	//Si l'uip est 0 on ne peut pas backtrack.
	if(uip.getId() == 0)
		return false;

	Clause* last = clauses.back();
	int max = 0;

	//On cherche le rang maximum de la nouvelle clause.
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

	//On d?truit toutes les d?ductions et les paris fait apr?s ce rang.
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
    uip.clearValidate_Clauses();
    uip.addValidate_Clause(last);


    return true;
}

int Solveur_cl::learn_clause(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
	//Un conflit sans paris -> non satisfiable.
  if(paris.size() == 1)
      return 0;
  
  //On r?cup?re la clause du conflit.
  unsigned int conflit = get_clause_issue_id();
  
  //On construit le graphe.
  vector<vector<int>> graph(literals.size(), vector<int>());
  create_graph(clauses, literals, literals[paris.back()].getDeductions(),
               paris, graph, clauses[conflit], 0);

  //On r?cup?re l'uip.
  int uip = get_uip(graph,literals[paris.back()].getDeductions(), paris.back());

  //On affiche le graphe.
  afficher_graphe(literals, graph, literals[paris.back()].getDeductions(), uip, paris.back());
  
  //On apprend la clause.
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

	vector<int> chemin;
	chemin.resize(0);
	found_chemin(graph, chemin, 0, paris);
	possible_uip = vector_and(chemin, possible_uip);
	int interdit;

	while(!possible_uip.empty()){
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
	for(int voisin : graph[sommet]){
		voisin = abs(voisin);

		if(voisin == 0)
			return true;
		if(voisin == interdit)
			continue;

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

	for(int u: a){
		if(find(b.begin(), b.end(), u) != b.end()){
			retour.push_back(u);
		}
	}

	return retour;
}

void Solveur_cl::afficher_graphe(vector<Literal>& literals, vector<vector<int>>& graph, vector<int> deduction, int uip, int paris){
  
  if(!show_graph){
    return;
  }
  
  /** Entr?e utilisateur **/
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
