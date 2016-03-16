#include "main.h"

typedef struct Option Option;
struct Option {
    string name;
    string id;
    bool active;
};

static Option options[] = {
    {"Dynamic Largest Individual Sum",                  "-dlis",    false},
    {"Maximum Occurrences in clauses of Minimum Size",  "-moms",    false},
    {"Random",                                          "-rand",    false},
    {"Tseitin",                                         "-tseitin", false},
    {"watched literals",                                "-wl",      false},
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
        return 1;
    }

    //vector<bool> rep = dpll_naif(clauses, parsed.second);


    //init_dpll(clauses,parsed.second,false);

    vector<bool> rep = dpll(clauses, parsed.second);

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
    else{cout << "s UNSATISFIABLE" << endl;}
}

char* lire_args(int argc, char* argv[]){
    char* file = "";                //nom du fichier a lire
    bool arg_valide = false;        //validité de l'argument lu

    for(int i = 1; i<argc; i++){//On lit tous les arguments sauf le nom du programme.
        arg_valide = false;

        if(argv[i][0] != '-'){  //Si l'argument n'est pas une option soit c'est le fichier soit c'est une erreur.
                file = argv[i];
                //cout << "Warning incorrect argument : " << argv[i] << " the file to read is already : " << file << endl;
        }
        else{
            Option *opt;
            for(opt = options; opt->name != ""; opt++){//On vérifie si l'argument est une option connu.
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


    return file;
}
