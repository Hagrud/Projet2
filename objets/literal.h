#ifndef DEF_LITERAL
#define DEF_LITERAL

#include <vector>
#include <iostream>
#include <stdlib.h>


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

    private:
        bool value;
        int id;
        vector<int> deductions;
        bool pari;
        bool fixed;
};

#endif
