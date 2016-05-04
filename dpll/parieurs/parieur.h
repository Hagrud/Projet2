#ifndef DEF_PARIEUR
#define DEF_PARIEUR


#include <vector>

#include "../../objets/literal.h"

using namespace std;

class Parieur
{
    public:
        bool parier(vector<Literal>& literals, vector<int>& paris);
};

#endif // DEF_PARIEUR
