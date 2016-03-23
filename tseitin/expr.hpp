#ifndef DEF_EXPR
#define DEF_EXPR

#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <set>

using namespace std;

/***********************************/
/*********  Expressions   **********/
/***********************************/

class Expr
{
public:
    Expr(){}
    virtual std::string to_string()=0;
    virtual std::string to_cnf()=0;
    virtual int eval()=0;
    virtual Expr * tseitin(int max_var, vector<Expr*>& exprs)=0;
    virtual void get_vars(set<Expr*>& vars)=0;
};

/***********************************/
/**********  Constants   ***********/
/***********************************/

class EConst : public Expr
{
public:
    EConst(int val); 
    virtual std::string to_string();
    virtual std::string to_cnf();
    virtual int eval();
    virtual Expr * tseitin(int max_var, vector<Expr*>& exprs);
    virtual void get_vars(set<Expr*>& vars);
    static int nb_var;
private:
    int value;
};

/***********************************/
/**********  Additions   ***********/
/***********************************/

class EOr : public Expr
{
public:
    EOr(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual std::string to_cnf();
    virtual int eval();
    virtual Expr * tseitin(int max_var, vector<Expr*>& exprs);
    virtual void get_vars(set<Expr*>& vars);
private:
    Expr * op1, * op2;
};

/***********************************/
/********  Multiplications  ********/
/***********************************/

class EAnd : public Expr
{
public:
    EAnd(Expr * e1, Expr * e2);
    virtual std::string to_string();
    virtual std::string to_cnf();
    virtual int eval();
    virtual Expr * tseitin(int max_var, vector<Expr*>& exprs);
    virtual void get_vars(set<Expr*>& vars);
private:
    Expr * op1, * op2;
};

/***********************************/
/*********  Soustractions  *********/
/***********************************/

class ENeg : public Expr
{
public:
    ENeg(Expr * e1);
    virtual std::string to_string();
    virtual std::string to_cnf();
    virtual int eval();
    virtual Expr * tseitin(int max_var, vector<Expr*>& exprs);
    virtual void get_vars(set<Expr*>& vars);
private:
    Expr * op1;
};


#endif // ! DEF_EXPR
