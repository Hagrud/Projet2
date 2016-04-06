#include "paris.h"

static bool RANDP = false;
static bool MOMS = false;
static int libres;

void set_option(bool rand, bool moms){
	RANDP = rand;
	MOMS = moms;
}

void set_libre(int nV){
	libres = nV;
}

void change_libre(int n){
	libres = libres + n;
}

bool make_paris(vector<int>& varsStates, vector<int>& paris){
	if(RANDP){
		return rand_paris(varsStates, paris);
	}
	if(MOMS){
		//return moms_paris(varsStates, paris);
	}
	return basic_paris(varsStates, paris);
}

bool rand_paris(vector<int>& varsStates, vector<int>& paris){
	if(libres==0){return false;}

	int randvar = rand() % libres;
	int l = 0;
	for(unsigned int varID = 0;varID<varsStates.size();varID++){
		if(varsStates[varID]==-1){
			if(l==randvar){
				paris.push_back(varID+1);
				varsStates[varID] = rand() % 2;
				libres--;
				return true;
			}
			l++;
		}
	}
	return true;
}

bool basic_paris(vector<int>& varsStates, vector<int>& paris){
	for(unsigned int varID = 0;varID<varsStates.size();varID++){
		if(varsStates[varID]==-1){
			paris.push_back(varID+1);
			varsStates[varID] = 1;
			return true;
			break;
		}
	}
	return false;
}
