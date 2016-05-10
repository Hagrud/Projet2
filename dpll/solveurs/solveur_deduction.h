#ifndef DEF_SOLVEUR_DEDUCTION
#define DEF_SOLVEUR_DEDUCTION


#include "solver.h"

#include "../parieurs/parieur.h"
#include "../backtrack.h"
#include "../checker.h"

class Solveur_deduction : public solveur
{
    public:
        Solveur_deduction();
        Solveur_deduction(Parieur p);
        vector<bool> solve(vector<vector<int>>& clauses, int nV);


	protected:
        void pre_solve(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		virtual void deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		virtual bool backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		virtual ~Solveur_deduction(){}

	private:
		Parieur parieur;
};

#endif // DEF_SOLVEUR_DEDUCTION
