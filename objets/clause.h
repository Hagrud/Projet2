#ifndef DEF_CLAUSE
#define DEF_CLAUSE

#include <vector>
#include <iostream>
#include <stdlib.h>


using namespace std;

class Clause{
    public:
        Clause();
        Clause(vector<int> vars);

        vector<int> getVariables();

        bool isValid();
        void setValid(bool b);


    private:
        vector<int> variables;
        bool valid;
};

#endif //DEF_CLAUSE
