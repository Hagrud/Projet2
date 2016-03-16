#include "dpll.h"

static vector<vector<int>> clauses_masks_true;
static vector<vector<int>> clauses_masks_false;
static bool watchedL = false;


void init_dpll(vector<vector<int>> clauses, int nV, bool wl){
    watchedL = wl;

    for(auto clause:clauses){
        vector<int> mask_true(((nV-(nV%sizeof(int)))/sizeof(int))+1, 0);
        vector<int> mask_false(((nV-(nV%sizeof(int)))/sizeof(int))+1, 0);

        for(int var:clause){
            if(var>0){
                mask_true[(var-(var%sizeof(int)))/sizeof(int)] = mask_true[(var-(var%sizeof(int)))/sizeof(int)] + (1<<((var%sizeof(int))-1));
            }
            else{
                mask_false[((-var)-((-var)%sizeof(int)))/sizeof(int)] = mask_false[((-var)-((-var)%sizeof(int)))/sizeof(int)] + (1<<(((-var)%sizeof(int))-1));
            }
        }

        clauses_masks_false.push_back(mask_false);
        clauses_masks_true.push_back(mask_true);
    }

    //Description
    for(auto clause:clauses_masks_false){
        for(unsigned int i = 0;i<((nV-(nV%sizeof(int)))/sizeof(int))+1;i++){
            cout << "clause false " << i << " : " << clause[i] <<endl;
        }
    }
    for(auto clause:clauses_masks_true){
        for(unsigned int i = 0;i<((nV-(nV%sizeof(int)))/sizeof(int))+1;i++){
            cout << "clause true " << i << " : " << clause[i] <<endl;
        }
    }
}

/**
* @desc Cherche un solution au problème SAT posé dans clauses
* @return instance des variables solutions de SAT. (ou une instance non solution si il n'y a pas de solution.)
*/
vector<bool> dpll_naif(vector<vector<int>> clauses, int nV){
	vector<bool> varsStates(nV, true);

	dpll_rec(clauses, varsStates, nV, 0);

	return varsStates;
}

/**
* @desc Cherche récursivement sur toutes les instances possibles des variables une solution possible au problème SAT.
* @return True si l'instance est solution du problème.
*/
bool dpll_rec(vector<vector<int>>& clauses, vector<bool>& varsStates, int nV, int pos){
	//On vérifie si l'instance valide SAT.
	if(check(clauses, varsStates)){return true;}

    if(pos<nV){
        //On vérifie si l'instance de SAT est vérifiable en changeant seulement les variables suivantes.
        bool val = dpll_rec(clauses, varsStates, nV, pos+1);
		if(val){return true;}

	//Sinon on chance celle-ci
		varsStates[pos] = !varsStates[pos];
        val = dpll_rec(clauses, varsStates, nV, pos+1);
        if(val)
            return true;
        else{
            varsStates[pos] = true;
            return false;
        }
    }
    else{
        varsStates[pos] = !varsStates[pos];
        if(check(clauses, varsStates))
            return true;
        else{
            varsStates[pos] = true;
            return false;
        }
    }
	return false;
}

vector<bool> dpll(vector<vector<int>>& clauses, int nV){

    vector<int> paris;				//Tableau des paris
    vector<vector<int>> deductions;		//Déductions en fonction des paris
    vector<int> varsStates(nV, -1);		//Valeur des variables (-1:null,0:false,1:true)
    vector<bool> varsStatesBool(nV, false);

    paris.resize(0);				//On a aucuns paris
    deductions.resize(0);			//et aucunes déductions
    deductions.push_back({});

    while(true){
        while(unitProp(clauses, paris, deductions, varsStates)){}

        if(!checkWithNull(clauses, varsStates)){
		//cout<<"paris faux"<<endl;
            for(auto var:deductions.back()){
                varsStates[abs(var)-1] = -1;
            }

	    if(!paris.empty()){
            	deductions.pop_back();
            	cout<<paris.back()<<endl;
            	deductions.back().push_back(-paris.back());
            	paris.pop_back();
	    }
	    else{	//Faux alors qu'on a aucuns paris => pas satisfiable.
                for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
                return varsStatesBool;
	    }
        }else{
	            for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
		if(check(clauses,varsStatesBool)){return varsStatesBool;}
	}

        //for(auto p:varsStates){cout<<p<<" ";}
        //cout << endl;

        //Decide
        bool change = false;
        for(unsigned int varID = 0;varID<varsStates.size();varID++){
            if(varsStates[varID]==-1){
                paris.push_back(varID+1);
                varsStates[varID] = 1;
                change = true;
		//cout<<"paris : "<<varID+1<<endl;
                break;
            }
        }

        deductions.push_back({});

        if(!change){
            for(int i = 0;i<nV;i++){varsStatesBool[i]=(varsStates[i]==1);}
            return varsStatesBool;
        }
    }
}

bool unitProp(vector<vector<int>>& clauses,vector<int>& paris,vector<vector<int>>& deductions,vector<int>& varsStates){
    vector<int> vue(varsStates.size(), 0);
    vector<int> vue_en_cour(varsStates.size(), 0);

	for(auto vec:clauses){		// Pour chaque clause on vérifie si il ya une seul variable libre
            bool valid = false;
		for(auto var:vec){	//	si elle n'est pas satisfiable on la fixe.

			//La variable est libre
			if(varsStates[abs(var)-1]==-1){
				int compteur = 0;
				for(auto var2:vec){

					//On vérifie que c'est la seul
					if(varsStates[abs(var2)-1]==-1){
						compteur++;
						if(compteur>1){break;}
					}

					//On vérifie que la clause n'est pas déja satisfaite
					else if(varsStates[abs(var2)-1]==var2/abs(var2)){
						compteur=2;
					}

				}

				//On fixe la variable.
				if(compteur==1){
					if(var<0)
						varsStates[-var-1]=0;
					else
						varsStates[var-1]=1;
					deductions.back().push_back(var);
					return true;
				}
				break;

			}

			//On vérifie si la variable satisfait la clause.
			if((var>0&&varsStates[var-1]==1)||(var<0&&varsStates[-var-1]==0)){
                valid = true;
				break;
			}

			if(vue_en_cour[abs(var)-1]==0){
                if(var<0){
                    vue_en_cour[-var-1] = 2;
                }
                else{
                    vue_en_cour[var-1] = 1;
                }
			}
			else if(vue_en_cour[abs(var)-1]==1 && var<0){
                vue_en_cour[abs(var)-1] = 3;
			}
			else if(vue_en_cour[abs(var)-1]==2 && var>0){
                vue_en_cour[abs(var)-1] = 3;
			}
		}

        for(unsigned int i = 0;i<vue.size();i++){
            if(!valid && (vue_en_cour[i]==3 || vue_en_cour[i]+vue[i]==3))
                vue[i]=3;
            vue_en_cour[i] = 0;
            }
	}

    bool change = false;
    for(unsigned int i = 0;i<vue.size();i++){
        if(vue[i]==1 && varsStates[i]==-1){
            varsStates[i]=1;
            change = true;
        }

        else if(vue[i]==2 && varsStates[i]==-1){
            varsStates[i]=0;
            change = true;
        }
    }

	return change;
}
