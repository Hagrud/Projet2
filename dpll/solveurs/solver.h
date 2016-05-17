#include <vector>

#include "../checker.h"
#include "../paris.h"
#include "../deduction.h"
#include "../backtrack.h"
#include "../dpll.h"

#include "../../objets/literal.h"
#include "../../objets/clause.h"

/**
 * Classe du solveur.
 */
class solveur
{
    public:
	/**
	 * Résout l'instance de SAT.
	 * #clauses 	les clauses à valider.
	 * #nV			nombres de variables.
	 * @return 		une instance des variables valide si il en existe.
	 */
    virtual vector<bool> solve(vector<vector<int>>& clauses, int nV)=0;

    protected:
    /**
     * Retourne un vecteur d'entier à la place du vecteur de Literal.
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
};


