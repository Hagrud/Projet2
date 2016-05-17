#include <vector>

#include "../checker.h"
#include "../deduction.h"

#include "../../objets/literal.h"
#include "../../objets/clause.h"

/**
 * Classe du solveur.
 */
class solveur
{
    public:
	/**
	 * R?sout l'instance de SAT.
	 * #clauses 	les clauses ? valider.
	 * #nV			nombres de variables.
	 * @return 		une instance des variables valide si il en existe.
	 */
    virtual vector<bool> solve(vector<vector<int>>& clauses, int nV)=0;

    protected:
    /**
     * Retourne un vecteur d'entier ? la place du vecteur de Literal.
     */
    vector<bool> to_vector(vector<Literal>& literals);
};


/**
 * Dpll "bourrin"
 */
class solveur_naif : public solveur
{
    public:
    vector<bool> solve(vector<vector<int>>& clauses, int nV);
    bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos);
};


