#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

void init_graph_cpp(bool voir);

void generate_conflict_graph(vector<vector<int>>& graph, vector<int>& deduction, vector<int>& varsStates, vector<int>& paris, int uip);

void check_conflict(vector<vector<int>>& graph, vector<int>& deduction, vector<int>& varsStates, vector<int>& paris, int uip);
