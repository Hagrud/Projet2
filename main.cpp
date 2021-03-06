#include "main.h"

typedef struct Option Option;
struct Option {
    string name;
    string id;
    bool active;
};

static Option options[] = {
    {"Dynamic Largest Individual Sum",                  "-dlis",   		false},
    {"Maximum Occurrences in clauses of Minimum Size",  "-moms",    	false},
    {"Random",                                          "-rand",    	false},
    {"Tseitin",                                         "-tseitin", 	false},
	  {"Exploration de conflit",							            "-cl-interac",false},
	  {"Satisfiability Modulo Theories",                  "-smt",       false},
    {"watched literals",                                "-wl",      	false},
    {"", "", false}};


int main(int argc, char* argv[]){

    if(argc<=1){
            cout << "no input file" << endl;
            return 1;
    }

    char* file = lire_args(argc, argv);

    pair<vector<vector<int>>,int> parsed = parse(file);
    vector<vector<int>> clauses = parsed.first;

    if(parsed.second==0){   //Si on n'a pas de variable il y a une erreur.
		cout << "s SATISFIABLE" << endl;
        return 0;
    }

    
    Parieur *parieur;
    solveur *solveur;

    if(get_option("rand")){
    	parieur = new Parieur_rand();
    }
    else{
    	parieur = new Parieur();
    }

    if(get_option("cl-interac")){
      solveur = new Solveur_cl(*parieur, *(new Smt()));
    }
    else{
      solveur = new Solveur_deduction(*parieur, *(new Smt()));
    }

    vector<bool> rep = solveur->solve(clauses, parsed.second);

    reponse(clauses, rep);

    return 0;
}

void reponse(vector<vector<int>>& clauses,vector<bool>& rep){
    if(check(clauses, rep)){
        cout << "s SATISFIABLE" << endl;
        for(unsigned int i = 0;i<rep.size();i++){
            if(rep[i])
                cout << i+1 << " ";
            else
                cout << "-" << i+1 << " ";
        }
        cout << 0 << endl;
    }
    else{
        cout << "s UNSATISFIABLE" << endl;
    }
}

char* lire_args(int argc, char* argv[]){
    char* file;                //nom du fichier a lire
    bool arg_valide = false;        //validit? de l'argument lu

    for(int i = 1; i<argc; i++){//On lit tous les arguments sauf le nom du programme.
        arg_valide = false;

        if(argv[i][0] != '-'){  //Si l'argument n'est pas une option soit c'est le fichier soit c'est une erreur.
                file = argv[i];
                //cout << "Warning incorrect argument : " << argv[i] << " the file to read is already : " << file << endl;
        }
        else{
            Option *opt;
            for(opt = options; opt->name != ""; opt++){//On v?rifie si l'argument est une option connu.
                if(opt->id == argv[i]){
                    opt->active = true;
                    arg_valide = true;
                }
            }

            if(!arg_valide){
                cout << "Warning unknown command : " << argv[i] << endl;
            }
        }
    }

    Option *opt;
    for(opt = options; opt->name != ""; opt++){
        if(opt->active){
            cout << "Option : " << opt->name << " activated" << endl;
        }
    }

    if(options[3].active)
    {
	file = create_tseitin(file);
    }

    return file;
}

char* format_file(char* file)
{
    ifstream inStream(file);

    strcat(file, ".tmp");
    ofstream outStream(file);

    string line;
    vector<string> lines;

    while(getline(inStream, line))
    {
	lines.push_back(line);
    }

    for(int i = 0; i < (int)lines.size() - 1; i++)
    {
	lines[i].push_back('\n');
    }

    for(int i = 0; i < (int)lines.size(); i++)
    {
	outStream << lines[i];
    }

    return file;
}

char* create_tseitin(char* file)
{
    file = format_file(file);
    
    freopen(file, "r", stdin);

    yyparse();

    strcat(file, ".cnf");

    ofstream myfile;
    myfile.open(file);

    int var_count = 0, cur_var_count = 0, clause_count = 0;

    vector<Expr*> exprs;

    set<int> vars;

    res->get_vars(vars);

    int max_var = 0;
    for(auto it : vars)
	max_var = max(it, max_var);

    Expr * var = res->tseitin(max_var, exprs);
    exprs.push_back(var);

    string result;
    for(int i = 0; i < (int)exprs.size(); i++)
    {
	clause_count++;

	result += exprs[i]->to_cnf(cur_var_count, clause_count);
	var_count = max(cur_var_count, var_count);
	cur_var_count = 0;

	result += "\n";
    }



    for(int i = 0; i < (int)result.size() - 1; i++)
    {
	if(result[i] == '-' && result[i+1] == '-')
	{
	    result.erase(i, 1);
	}

    }

    myfile << "p cnf " << var_count << " " << clause_count << endl;
    myfile << result;
    
    return file;
}

void yyerror(const char *s) {
    cout << "EEK, parse error!  Message: " << s << endl;
    // might as well halt now:
    exit(-1);
}

bool get_option(string option){
	option = "-" + option;
	Option *opt;
    for(opt = options; opt->name != ""; opt++){//On v?rifie si l'argument est une option connu.
    	if(opt->id == option){
        	return opt->active;
		}
	}
	return false;
}
