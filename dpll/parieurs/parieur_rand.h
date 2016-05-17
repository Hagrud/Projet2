#ifndef PARIEUR_RAND_H_
#define PARIEUR_RAND_H_

#include <vector>
#include "parieur.h"
#include <stdlib.h>
#include <cstdlib>

#include "../../objets/literal.h"

using namespace std;

class Parieur_rand : public Parieur
{
    public:
        bool parier(vector<Literal>& literals, vector<int>& paris);
};



#endif /* PARIEUR_RAND_H_ */
