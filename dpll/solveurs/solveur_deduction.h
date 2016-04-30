#ifndef DEF_SOLVEUR
#define DEF_SOLVEUR


#include "solver.h"

#include "../parieurs/parieur.h"
#include "../backtrack.h"
#include "../checker.h"

class Solveur_deduction : public solveur
{
    public:
        Solveur_deduction(Parieur p);
        vector<bool> solve(vector<vector<int>>& clauses, int nV);
        void pre_solve();

    private:
        Parieur parieur;
};

#endif // DEF_SOLVEUR
