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

#include <time.h>

#include "Replication.h"
#include "Parametres.h"
#include "Scenario.h"

using namespace std;


typedef struct _Analyse
{
	int nb_scenario;
	int intervalle_de_confiance;
	vector<float> moyenne;
} Analyse;


void lancer_menu();

void repliquer(int, int, Replication);

void creer_replication(int, int, Replication);

void creer_dossier_replication(int, int);

vector < list<int> > calculer_strategie(int, int, Replication);

void creer_fichiers(int, int, Replication, vector < list<int> >);

vector<string> liste_fichiers_du_dossier(char *);

Replication construction_replication(vector<string>);

Creneau_horaire * parserFichier(string);

void afficher_replication(Replication);

void enregistrer_replication(int, int, Replication);

long lancer_flot_max(string);

LPCWSTR MultiCharToUniChar(char*);

string UniCharToMultiChar(wchar_t*);

void Color(int, int);

bool Statistiques(vector<Scenario>, Analyse *);

#endif
