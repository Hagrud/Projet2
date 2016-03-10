#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "dpll/dpll.h"


using namespace std;

char* lire_args(int argc, char* argv[]);

void reponse(vector<vector<int>>& clauses,vector<bool>& rep);
