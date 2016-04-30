#include <vector>

#include "../checker.h"
#include "../paris.h"
#include "../deduction.h"
#include "../backtrack.h"
#include "../dpll.h"

#include "../../objets/literal.h"

class solveur
{
    public:
    virtual vector<bool> solve(vector<vector<int>>& clauses, int nV)=0;

    protected:
    vector<bool> to_vector(vector<Literal>& literals);
};

class solveur_naif : public solveur
{
    public:
    vector<bool> solve(vector<vector<int>>& clauses, int nV);
};


