#include "parieur.h"

bool Parieur::parier(vector<Literal>& literals, vector<int>& paris){
    for(Literal &lit : literals){
        if(!lit.isFixed()){

            paris.push_back(lit.getId());

            lit.setFixed(true);
            lit.setPari(true);
            lit.setValue(true);

            lit.setLevel(literals[paris[paris.size()-2]].getLevel() + 1);

            return true;
        }

    }
    return false;
}
