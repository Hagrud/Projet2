#include "expr.hpp"

using namespace std;

/***********************************/
/*********  Conjonction   **********/
/***********************************/

EConjonction::EConjonction(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EConjonction::to_string()
{
    return "(" + op1->to_string() + " /\\ " +  op2->to_string() + ")";
}

bool EConjonction::eval()
{
    return op1->eval() & op2->eval();
}

/***********************************/
/*********  Disjonction   **********/
/***********************************/

EDisjonction::EDisjonction(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EDisjonction::to_string()
{
    return "(" + op1->to_string() + " \\/ " +  op2->to_string() + ")";
}

bool EDisjonction::eval()
{
    return op1->eval() | op2->eval();
}

/***********************************/
/************  Xor   ***************/
/***********************************/

EXor::EXor(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EXor::to_string()
{
    return "(" + op1->to_string() + " X " +  op2->to_string() + ")";
}

bool EXor::eval()
{
    return op1->eval() ^ op2->eval();
}

/***********************************/
/**********   Implique  ************/
/***********************************/

EImplique::EImplique(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EImplique::to_string()
{
    return "(" + op1->to_string() + " => " +  op2->to_string() + ")";
}

bool EImplique::eval()
{
    return op1->eval() == op2->eval() | op2->eval();
}

/***********************************/
/*********   Equivalent  ***********/
/***********************************/

EEquivalent::EEquivalent(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EEquivalent::to_string()
{
    return "(" + op1->to_string() + " <=> " +  op2->to_string() + ")";
}

bool EEquivalent::eval()
{
    return op1->eval() == op2->eval();
}

/***********************************/
/**********  Negation   ************/
/***********************************/

ENegation::ENegation(Expr * e1) : op1(e1) {}

string ENegation::to_string()
{
    return "(~" +  op1->to_string() + ")";
}

bool ENegation::eval()
{
    return ~op1->eval();
}

/***********************************/
/**********  Variables   ***********/
/***********************************/

EVariable::EVariable(int val) : value(val) {}

string EVariable::to_string()
{
    ostringstream oss;
    oss << value;
    string result = oss.str();
    return result;
}

bool EVariable::eval()
{
    return false;
}
