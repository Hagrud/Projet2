#include "parieur.h"

bool Parieur::parier(vector<Literal>& literals, vector<int>& paris){
    for(Literal &lit : literals){
        if(!lit.isFixed()){
            //cout << "paris : " << lit.getId() << endl;
            paris.push_back(lit.getId());

            lit.setFixed(true);
            lit.setPari(true);
            lit.setValue(true);

            return true;
        }

    }
    return false;
}
