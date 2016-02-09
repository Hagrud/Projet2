#ifndef DEF_EXPR
#define DEF_EXPR

#include <iostream>
#include <sstream> 
#include <string>

/***********************************/
/*********  Expressions   **********/
/***********************************/

class Expr
{
public:
    Expr(){}
    virtual std::string to_string()=0;
    virtual bool eval()=0;
};

/***********************************/
/*********  Conjonction   **********/
/***********************************/

class EConjonction : public Expr
{
public:
    EConjonction(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual bool eval();
private:
    Expr * op1, * op2;
};

/***********************************/
/*********  Disjonction   **********/
/***********************************/

class EDisjonction : public Expr
{
public:
    EDisjonction(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual bool eval();
private:
    Expr * op1, * op2;
};

/***********************************/
/*************  Xor   **************/
/***********************************/

class EXor : public Expr
{
public:
    EXor(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual bool eval();
private:
    Expr * op1, * op2;
};

/***********************************/
/**********  Implique   ************/
/***********************************/

class EImplique : public Expr
{
public:
    EImplique(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual bool eval();
private:
    Expr * op1, * op2;
};

/***********************************/
/*********  Equivalent   ***********/
/***********************************/

class EEquivalent : public Expr
{
public:
    EEquivalent(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual bool eval();
private:
    Expr * op1, * op2;
};

/***********************************/
/**********  Negation   ************/
/***********************************/

class ENegation : public Expr
{
public:
    ENegation(Expr * e1);
    virtual std::string to_string();
    virtual bool eval();
private:
    Expr * op1;
};

/***********************************/
/**********  Variable   ************/
/***********************************/

class EVariable : public Expr
{
public:
    EVariable(int val); 
    virtual std::string to_string();
    virtual bool eval();
private:
    int value;
};
#endif // ! DEF_EXPR
