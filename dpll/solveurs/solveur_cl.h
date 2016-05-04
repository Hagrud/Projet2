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
		
		void create_graph(vector<Clause*>& clauses, 
                      vector<Literal>& literals,
                      vector<int> deduction,
                      vector<int>& paris,
                      vector<vector<int>>& graph,
                      Clause* clause_id, int var_id);
		
		void afficher_graphe(vector<Literal>& literals, vector<vector<int>>& graph, vector<int> deduction, int uip);

	private:
		bool show_graph;
};

#endif // DEF_SOLVEUR_CL
