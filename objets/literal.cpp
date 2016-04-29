#include "literal.h"

Literal::Literal(int n){
    id = n;
    deduction.resize(0);
    pari = false;
    fixed = false;
}

int Literal::getId(){
    return id;
}


