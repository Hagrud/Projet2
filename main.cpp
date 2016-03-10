#include "main.h"

typedef struct Option Option;
struct Option {
    string name;
    string id;
    bool active;
};

static Option options[] = {
    {"Tseitin", "-tseitin",false},
    {"watched literals", "-wl",false},
    {"Maximum Occurrences in clauses of Minimum Size", "-moms",false},
    {"Random", "-rand",false},
    {"Dynamic Largest Individual Sum", "-dlis",false},
    {"", "", false}};


int main(int argc, char* argv[]){

    if(argc<=1){
            cout << "no input file" << endl;
            return 1;
    }

    char* file = lire_args(argc, argv);

    pair<vector<vector<int>>,int> parsed = parse(file);
    vector<vector<int>> clauses = parsed.first;

    if(parsed.second==0){
        return 1;
    }

    //vector<bool> rep = dpll_naif(clauses, parsed.second);

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
    char* file = nullptr;
    for(int i = 1; i<argc; i++){
        if(argv[i][0] != '-' && file==nullptr){
            file = argv[i];
        }
        Option *opt;
        for(opt = options; opt->name != ""; opt++){
            if(opt->id == argv[i]){
                opt->active = true;
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
