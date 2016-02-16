#include "parser.h"

using namespace std;

vector< vector<int> > parse(const char* path)
{
    vector< vector<int> > vars;
    int V, C, val;
    string tmp;
    ifstream file(path);

    if(!file)
    {
	cout << "File " << path << " not found." << endl;
	return vars;
    }

    string line;

    do {
	getline(file, line);
    } while(line[0] == 'c');
    
    istringstream iss(line);
    iss >> tmp >> tmp >> V >> C;

    vars.resize(C);
    
    for(int i = 0; i < C; i++)
    {
	vars[i].resize(0);
	getline(file, line);

	if(line[0] == 'c')
	{
	    i--;
	    continue;
	}
	
	istringstream iss(line);

	while(iss >> val && val != 0)
	{
	    vars[i].push_back(val);
	}
    }

    return vars;
}

