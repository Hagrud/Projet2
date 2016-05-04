#include "literal.h"


Literal::Literal(){
    id = 0;
    deductions.resize(0);
    validate_clauses.resize(0);
    pari=true;
    fixed=true;
}
Literal::Literal(int n){
    id = n;
    deductions.resize(0);
    validate_clauses.resize(0);
    pari = n==0;
    fixed = n==0;
}

int Literal::getId(){
    return id;
}

bool Literal::isFixed(){
    return fixed;
}

bool Literal::isPari(){
    return pari;
}

bool Literal::getValue(){
    return value;
}

void Literal::setPari(bool b){
    pari = b;
}

void Literal::setFixed(bool b){
    fixed = b;
    clearValidate_Clauses();
}

void Literal::setValue(bool b){
    value = b;
    clearValidate_Clauses();
}

vector<int> Literal::getDeductions(){
    return deductions;
}

void Literal::addDeduct(int dedu){
    deductions.push_back(dedu);
}

void Literal::clearDeduct(){
    deductions.resize(0);
}

void Literal::addValidate_Clause(Clause* clause){
    validate_clauses.push_back(clause);
    clause->setValid(true);
}

void Literal::clearValidate_Clauses(){
    for(Clause* clause : validate_clauses){
        clause->setValid(false);
    }
    validate_clauses.resize(0);
}

Clause* Literal::get_first_validate_clause(){
  if(validate_clauses.empty())
    return nullptr;
  return validate_clauses[0];
}
