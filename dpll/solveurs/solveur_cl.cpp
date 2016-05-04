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
	learn_clause(clauses, literals, paris);
	return Solveur_deduction::backtrack(clauses, literals, paris);
}

void Solveur_cl::learn_clause(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris){
  if(paris.size() == 1) //Un conflit sans paris -> non satisfiable.
      return;
  
  unsigned int conflit = get_clause_issue_id();
  
  /** Construction du graphe **/
  vector<vector<int>> graph(literals.size(), vector<int>());
  create_graph(clauses, literals, literals[paris.back()].getDeductions(),
               paris, graph, clauses[conflit], 0);

  /** Recuperation de l'uip **/ 
  int uip = abs(paris.back());
  
  /** Affichage **/
  afficher_graphe(literals, graph, literals[paris.back()].getDeductions(), uip);
  
  /** Clause learning **/
  
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




void Solveur_cl::afficher_graphe(vector<Literal>& literals, vector<vector<int>>& graph, vector<int> deduction, int uip){
  
  cout << "deductions : ["; for(auto p : deduction){cout << " " << p << " ";}
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
    
    for(int var:deduction){
      if(!graph[abs(var)].empty() && abs(var) != uip){
        if(literals[var].getValue())
          fichier << var << " [style=filled,color=cyan];" << endl;
        else
          fichier << -var << " [style=filled,color=cyan];" << endl;
      }
    }
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
