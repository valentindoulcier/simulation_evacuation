#ifndef PROCEDURES
#define PROCEDURES

#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/graph_utility.hpp>

#include <fstream>
#include <windows.h>
#include <vector>
#include <istream>

#include "Simulation.h"

using namespace std;

vector<string> liste_fichiers_du_dossier(char *);

Simulation construction_simulation(vector<string>);

Creneau_horaire * parserFichier(string);

void afficher_simulation(Simulation);

long lancer_flot_max(string);

LPCWSTR MultiCharToUniChar(char*);

string UniCharToMultiChar(wchar_t*);

#endif