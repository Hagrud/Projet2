#include "parser.h"

pair<vector<vector<int>>,int> parse(const char* path)
{
    vector< vector<int> > vars;
    int V, val, Vmax = 0;
    unsigned int C = 0;
    string tmp;
    ifstream file(path);

    if(!file)
    {
        cout << "File " << path << " not found." << endl;
        return make_pair(vars, 0);
    }

    string line;

    do {
        getline(file, line);
    } while(line[0] == 'c');

    istringstream iss(line);
    iss >> tmp >> tmp >> V >> C;

    vars.resize(0);

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        vars.push_back({});
        if(line[0] == 'c')
        {
            continue;
        }

        istringstream iss(line);

        while(iss >> val && val != 0)
        {
            vars.back().push_back(val);
            Vmax = max(Vmax, abs(val) );
        }
    }

	if(vars.back().empty())
		vars.pop_back();

    if(C!=vars.size())
        cout << "Le fichier contient " << vars.size() << " clause(s) alors que " << C << " clause(s) étaient annoncées." << endl;
    if(V!=Vmax)
        cout << "Le fichier contient " << Vmax << " variable(s) alors que " << V << " variable(s) étaient annoncées." << endl;

    return make_pair(vars, Vmax);
}

