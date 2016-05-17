#include "deduction.h"


bool dedUnitaire(vector<Clause *>& clauses, vector<Literal>& literals, Literal &paris){
    for(Clause* clause : clauses){
        if(clause->isValid())
            continue;

        vector<int> vars = clause->getVariables();
        int compteur = 0;
        int id = 0;

        for(int var : vars){

            if(!literals[abs(var)].isFixed()){
                compteur++;

                if(compteur>1)
                    break;

                id = var;
            }
            else if(literals[abs(var)].getValue() == (var>0)){
                compteur=2;

                Literal &lit = literals[abs(var)];
                lit.addValidate_Clause(clause);

                break;
            }
        }

        if(compteur==1){
            Literal &lit = literals[abs(id)];
            lit.setValue(id>0);
            lit.setFixed(true);

            lit.addValidate_Clause(clause);

            paris.addDeduct(lit.getId());
            lit.setLevel(paris.getLevel());

            //cout << paris.getId() <<  " deduit : " << lit.getId() << endl;
            return true;
        }

    }
    return false;
}

bool polarite_unique(vector<Clause *>& clauses, vector<Literal>& literals, Literal &paris){

    vector<bool> var_true(literals.size(), false);    //Liste des variables qui apparaissent avec la polarité positive.
    vector<bool> var_false(literals.size(), false);   //Liste des variables qui apparaissent avec la polarité négative.

    for(Clause* clause : clauses){
        vector<int> vars = clause->getVariables();
        for(int var : vars){
            if(!literals[abs(var)].isFixed()){
                if(var>0)
                    var_true[abs(var)] = true;
                else
                    var_false[abs(var)] = true;
            }
        }
    }

    /** On vérifie si des variables ne sont vuent qu'avec une seule polaritée. **/
    bool change = false;
    for(unsigned int i = 1;i<var_true.size();i++){
        if(var_true[i] && !var_false[i]){
            paris.addDeduct(i);

            Literal &lit = literals[i];
            lit.setValue(true);
            lit.setFixed(true);

            change = true;
        }
        else if(!var_true[i] && var_false[i]){
            paris.addDeduct(i);

            Literal &lit = literals[i];
            lit.setValue(false);
            lit.setFixed(true);

            change = true;
        }
    }

    return change;

}