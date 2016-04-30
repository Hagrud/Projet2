#include "literal.h"


Literal::Literal(){
    id = 0;
    deductions.resize(0);
    pari=true;
    fixed=true;
}
Literal::Literal(int n){
    id = n;
    deductions.resize(0);
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
}

void Literal::setValue(bool b){
    value = b;
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


