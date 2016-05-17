#include "parieur_rand.h"

bool Parieur_rand::parier(vector<Literal>& literals, vector<int>& paris){

	int nb = 0;
	for(Literal &lit : literals){
		if(lit.getId() == 0)
			continue;

		if(!lit.isFixed())
			nb++;
	}

	if(nb==0)
		return false;

	int randvar = rand() % nb;

    for(Literal &lit : literals){
    	if(lit.isFixed()){
    		continue;
    	}
    	else if(randvar == 0){
            paris.push_back(lit.getId());

            lit.setFixed(true);
            lit.setPari(true);
            lit.setValue(true);

            lit.setLevel(literals[paris[paris.size()-2]].getLevel() + 1);

            return true;
        }
    	else{
    		randvar--;
    	}

    }
    return false;
}
