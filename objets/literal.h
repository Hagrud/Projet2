#ifndef DEF_LITERAL
#define DEF_LITERAL

#include <vector>
#include <iostream>
#include <stdlib.h>

#include "clause.h"


using namespace std;

class Literal{
    public:
        Literal();
        Literal(int id);
        int getId();

        bool isPari();
        void setPari(bool b);

        bool isFixed();
        void setFixed(bool b);

        bool getValue();
        void setValue(bool b);

        vector<int> getDeductions();
        void addDeduct(int dedu);
        void clearDeduct();

        void clearValidate_Clauses();
        void addValidate_Clause(Clause* clause);
        Clause* get_first_validate_clause();

        bool isBackTracked();
        void setBackTracked(bool b);

        void setLevel(int lvl);
        int getLevel();

    private:
        bool value = false;
        int id;
        vector<int> deductions;
        bool pari;
        bool fixed;
        vector<Clause*> validate_clauses;
        bool backtracked;

        int level = 0;
};

#endif
