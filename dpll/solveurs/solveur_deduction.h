#ifndef DEF_SOLVEUR_DEDUCTION
#define DEF_SOLVEUR_DEDUCTION


#include "solver.h"

#include "../parieurs/parieur.h"
#include "../backtrack.h"
#include "../checker.h"

/**
 * Résout l'instance de sat en faisant des paris et des déductions.
 */
class Solveur_deduction : public solveur
{
    public:
        Solveur_deduction();
        Solveur_deduction(Parieur p);
        vector<bool> solve(vector<vector<int>>& clauses, int nV);


	protected:
        /**
         * Deductions avant le premier paris.
         */
        void pre_solve(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);

        /**
         * Déductions à faire après le premier paris.
         */
		virtual void deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);

		/**
		 * Retour en arrière lorsque l'on découvre qu'un paris est faux.
		 */
		virtual bool backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		virtual ~Solveur_deduction(){}

	private:
		Parieur parieur;
};

#endif // DEF_SOLVEUR_DEDUCTION
