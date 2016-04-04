#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;


void set_rand(bool rando);

bool make_paris(vector<int>& varsStates, vector<int>& paris);

bool rand_paris(vector<int>& varsStates, vector<int>& paris);

bool basic_paris(vector<int>& varsStates, vector<int>& paris);

void change_libre(int n);

void set_libre(int nV);

