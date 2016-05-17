#ifndef DEF_SOLVEUR_DEDUCTION
#define DEF_SOLVEUR_DEDUCTION


#include "solver.h"

#include "../parieurs/parieur.h"
#include "../backtrack.h"
#include "../checker.h"

/**
 * R�sout l'instance de sat en faisant des paris et des d�ductions.
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
         * D�ductions � faire apr�s le premier paris.
         */
		virtual void deduction(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);

		/**
		 * Retour en arri�re lorsque l'on d�couvre qu'un paris est faux.
		 */
		virtual bool backtrack(vector<Clause*>& clauses, vector<Literal>& literals, vector<int>& paris);
		virtual ~Solveur_deduction(){}

	private:
		Parieur parieur;
};

#endif // DEF_SOLVEUR_DEDUCTION
