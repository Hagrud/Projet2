#include "clause.h"

Clause::Clause(){
    variables.resize(0);
    valid = false;
}

Clause::Clause(vector<int> vars){
    variables = vars;
    valid = false;
}

vector<int> Clause::getVariables(){
    return variables;
}

bool Clause::isValid(){
    return valid;
}

void Clause::setValid(bool b){
    valid = b;
}
