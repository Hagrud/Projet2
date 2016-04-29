#include <vector>

#include "../checker.h"
#include "../paris.h"
#include "../deduction.h"
#include "../backtrack.h"
#include "../dpll.h"

#include "../../objets/literal.h"

class solveur
{
    virtual vector<bool> solve(vector<vector<int>>& clauses, int nV);
};

class solveur_naif : public solveur
{
    vector<bool> solve(vector<vector<int>>& clauses, int nV);
};


