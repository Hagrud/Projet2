#include "solver.h"


class Solveur_deduction : public solveur
{
    vector<bool> solve(vector<vector<int>>& clauses, int nV);
    void pre_solve();
};
