#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Literal{
    public:
        Literal(int id);
        int getId();

    private:
        int id;
        vector<int> deduction;
        bool pari;
};
