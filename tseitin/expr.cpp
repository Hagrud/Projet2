#include "expr.hpp"

using namespace std;

/***********************************/
/**********  Constants   ***********/
/***********************************/

EConst::EConst(int val) : value(val) {
    cout << "creating " << val << endl;
}

string EConst::to_string()
{
    ostringstream oss;
    oss << value;
    string result = oss.str();
    return result;
}

string EConst::to_cnf(int& var_count, int& clause_count)
{
    var_count = value;
    ostringstream oss;
    oss << value;
    string result = oss.str();
    return result;
}

int EConst::eval()
{
    return value;
}

Expr * EConst::tseitin(int& max_var, vector<Expr*>& exprs)
{
    cout << "ECONST : ";
    max_var++;
    
    Expr* xi = new EConst(max_var);

    Expr * xin = new ENeg(xi);

    Expr * thisn = new ENeg(this);
    
    exprs.push_back(
	new EAnd(
	    new EOr(
		xin,
		this
		),
	    new EOr(
		xi,
		thisn
		)
	    )
	);

    return xi;
}

void EConst::get_vars(set<int>& vars)
{
    vars.insert(value);
}

/***********************************/
/**********  Additions   ***********/
/***********************************/

EOr::EOr(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EOr::to_string()
{
    return "(" + op1->to_string() + " \\/ " +  op2->to_string() + ")";
}

string EOr::to_cnf(int& var_count, int& clause_count)
{
    return op1->to_cnf(var_count, clause_count) + " " + op2->to_cnf(var_count, clause_count);
}

int EOr::eval()
{
    return op1->eval() || op2->eval();
}

Expr * EOr::tseitin(int& max_var, vector<Expr*>& exprs)
{
    cout << "EOR : ";
    max_var++;

    Expr* xi = new EConst(max_var);

    Expr * xin = new ENeg(xi);
    
    Expr * op1t = op1->tseitin(max_var, exprs);
    Expr * op2t = op2->tseitin(max_var, exprs);

    Expr * op1tn = new ENeg(op1t);
    Expr * op2tn = new ENeg(op2t);
        
    exprs.push_back(
	new EAnd(
	    new EAnd(
		new EOr(
		    new EOr(
			xin,
			op1t
			),
		    op2t
		    ),
		new EOr(
		    xi,
		    op1tn
		    )
		),
	    new EOr(
		xi,
		op2tn
		)
	    )
	);

    return xi;
		    
}

void EOr::get_vars(set<int>& vars)
{
    op1->get_vars(vars);
    op2->get_vars(vars);
}

/***********************************/
/********  Multiplications   *******/
/***********************************/

EAnd::EAnd(Expr * e1, Expr * e2) : op1(e1), op2(e2) {}

string EAnd::to_string()
{
    return "(" + op1->to_string() + " /\\ " +  op2->to_string() + ")";
}

string EAnd::to_cnf(int& var_count, int& clause_count)
{
    clause_count++;
    return op1->to_cnf(var_count, clause_count) + "\n" + op2->to_cnf(var_count, clause_count);
}

int EAnd::eval()
{
    return op1->eval() && op2->eval();
}

Expr * EAnd::tseitin(int& max_var, vector<Expr*>& exprs)
{
    cout << "EAND : ";
    max_var++;

    Expr* xi = new EConst(max_var);

    Expr * xin = new ENeg(xi);

    Expr * op1t = op1->tseitin(max_var, exprs);
    Expr * op2t = op2->tseitin(max_var, exprs);

    Expr * op1tn = new ENeg(op1t);
    Expr * op2tn = new ENeg(op2t);
        
    exprs.push_back(
	new EAnd(
	    new EAnd(
		new EOr(
		    xin,
		    op1t
		    ),
		new EOr(
		    xin,
		    op2t
		    )
		),
	    new EOr(
		new EOr(
		    xi,
		    op1tn
		    ),
		op2tn
		)
	    )
	);

    return xi;
}

void EAnd::get_vars(set<int>& vars)
{
    op1->get_vars(vars);
    op2->get_vars(vars);
}

/***********************************/
/*********  Soustractions   ********/
/***********************************/

ENeg::ENeg(Expr * e1) : op1(e1) {}

string ENeg::to_string()
{
    return "(-" + op1->to_string() + ")";
}

string ENeg::to_cnf(int& var_count, int& clause_count)
{
    return "-" + op1->to_cnf(var_count, clause_count);
}

int ENeg::eval()
{
    return !op1->eval();
}

Expr * ENeg::tseitin(int& max_var, vector<Expr*>& exprs)
{
    cout << "ENEG : ";
    max_var++;    

    Expr* xi = new EConst(max_var);

    Expr * xin = new ENeg(xi);

    Expr * op1t = op1->tseitin(max_var, exprs);

    Expr * op1tn = new ENeg(op1t);
        
    exprs.push_back(
	new EAnd(
	    new EOr(
		xin,
		op1tn
		),
	    new EOr(
		xi,
		op1t
		)
	    )
	);

    return xi;
}

void ENeg::get_vars(set<int>& vars)
{
    op1->get_vars(vars);
}
