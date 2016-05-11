#ifndef DEF_SOLVEUR_CL
#define DEF_SOLVEUR_CL


#include "solveur_deduction.h"

#include "../parieurs/parieur.h"
#include "../backtrack.h"
#include "../checker.h"
#include "../graph.h"

class Solveur_cl : public Solveur_deduction
{
    public:
    	Solveur_cl(Parieur p);
		void deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);

	protected:
		bool backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		void learn_clause(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		void learn(vector<Clause*>& clauses, vector<vector<int>>& graph, vector<Literal>& literals,vector<int> deduction, int uip);
		
		void create_graph(vector<Clause*>& clauses, 
                      vector<Literal>& literals,
                      vector<int> deduction,
                      vector<int>& paris,
                      vector<vector<int>>& graph,
                      Clause* clause_id, int var_id);
		
	private:
		int get_uip(vector<vector<int>>& graph, vector<int> possible_uip,int paris);
		bool found_chemin(vector<vector<int>>& graph, vector<int>& chemin, int interdit, int sommet);
		vector<int> vector_and(vector<int> a, vector<int> b);
		void afficher_graphe(vector<Literal>& literals, vector<vector<int>>& graph, vector<int> deduction, int uip, int paris);

	private:
		bool show_graph;
};

#endif // DEF_SOLVEUR_CL
