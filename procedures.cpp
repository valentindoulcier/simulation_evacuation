#include "procedures.h"



void lancer_menu()
{
	int nb_solutions = -1;
	int strategie = -1;
	bool menu_valide = false;

	cerr << "Bonjour et bienvenue :)" << endl << endl << endl;
	cerr << "\tCombien de simulation(s) voulez-vous generer ?! ";
	cin >> nb_solutions;
	
	while(!menu_valide)
	{
		cerr << "\tVoulez-vous avancer (0), retarder (1), aleatoirer (2) ?! ";
		cin >> strategie;
		if(strategie == 0 || strategie == 1 || strategie == 2)
		{
			menu_valide = true;
		}
	}


	switch(strategie)
	{
		case 0:
			cerr << endl << "Vous avez choisi de tester une strategie d'avancement\nsur un echantillon de " << nb_solutions << " simulations." << endl;
			break;

		case 1:
			cerr << endl << "Vous avez choisi de tester une strategie de retardement\nsur un echantillon de " << nb_solutions << " simulations." << endl;
			break;

		case 2:
			cerr << endl << "Vous avez choisi de tester une strategie aléatoire\nsur un echantillon de " << nb_solutions << " simulations." << endl;
			break;

		default: break;
	}

	system("pause");
}



void simuler(int nb_simul, vector<Simulation> mesSimulations)
{
	for(int i = 0; i < nb_simul; ++i)
	{
		creer_simulation(i, mesSimulations);
	}
}


void creer_simulation(int iPos, vector<Simulation> mesSimulations)
{
	creer_dossier_simul(iPos);
	creer_fichiers(iPos, mesSimulations, calculer_strategie(mesSimulations));
}


void creer_dossier_simul(int iPos)
{
	char nom_dossier[27];

	sprintf(nom_dossier,"./DATA_GENERATED/Simul_%i", iPos + 1);
	
	//RemoveDirectory(MultiCharToUniChar(nom_dossier));

	CreateDirectory(MultiCharToUniChar(nom_dossier), NULL);
}



// Fonction qui construit une matrice de la population de la simulation initiale et qui retourne une nouvelle matrice.
int ** calculer_strategie(vector<Simulation> mesSimulations)
{
	int ratio = 2;
	
	cout << "SOLUTION MERE" << endl << endl;

	int ** monTab;

	//Déclaration de mon tableau
	monTab = new int* [mesSimulations.at(0).getMax_batiment()];
	for(int i = 0; i < (signed)mesSimulations.at(0).getMax_batiment(); ++i)
		monTab[i] = new int [mesSimulations.at(0).getCreneau_horaire().size()];
	
	//Remplissage de mon tableau
		//Initialisation à 0
	for(int i = 0; i < (signed)mesSimulations.at(0).getMax_batiment(); ++i)
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().size(); ++j)
			monTab[i][j] = 0;

		//Remplissage réel
	int indice = -1;
	for (int i = 0; i < (signed)mesSimulations.at(0).getCreneau_horaire().size(); ++i)
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().at(i)->batiment.size(); ++j)
		{
			indice = mesSimulations.at(0).indice(mesSimulations.at(0).getCreneau_horaire().at(i)->batiment.at(j)->numero_batiment);
			monTab[indice][i] = mesSimulations.at(0).getCreneau_horaire().at(i)->batiment.at(j)->population;
		}


	//Affichage de mon tableau
	for(int i = 0; i < (signed)mesSimulations.at(0).getMax_batiment(); ++i)
	{
		cout << endl << "\t";
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().size(); ++j)
			cout << "\t" << monTab[i][j];
	}
	cout << endl << endl;


	cout << "SOLUTION 1" << endl << endl;
	
	int ** monTabSolution;

	//Déclaration de mon tableau
	monTabSolution = new int* [mesSimulations.at(0).getMax_batiment()];
	for(int i = 0; i < (signed)mesSimulations.at(0).getMax_batiment(); ++i)
		monTabSolution[i] = new int [mesSimulations.at(0).getCreneau_horaire().size() + 1]; // ON NE CREE QU'UN CRENEAU HORAIRE EN PLUS


	//Remplissage de mon tableau
	for(int i = 0; i < (signed)mesSimulations.at(0).getMax_batiment(); ++i)
	{
		monTabSolution[i][0] = (monTab[i][0] / ratio);
		
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().size() - 1; ++j)
		{
			monTabSolution[i][j + 1] = (monTab[i][j] / ratio) + (monTab[i][j + 1] / ratio);
		}
		monTabSolution[i][mesSimulations.at(0).getCreneau_horaire().size()] = (monTab[i][mesSimulations.at(0).getCreneau_horaire().size() - 1] / ratio);
	}

	//Affichage de mon tableau
	for(int i = 0; i < (signed)mesSimulations.at(0).getMax_batiment(); ++i)
	{
		cout << endl;
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().size() + 1; ++j)
			cout << "\t" << monTabSolution[i][j];
	}
	cout << endl << endl;

	/*
	cout << "SOLUTION 2" << endl << endl;


	vector < list<float> > monVector;
	//monVector.at(0).push_front(5);
	//monVector.at(0).front();


	//Calcul de ma nouvelle stratégie

	for(int i = 0; i < (signed)mesSimulations.at(0).getCreneau_horaire().at(0)->batiment.size(); ++i)
	{
		monVector.at(i).push_back(monTab[i][0] / ratio);
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().size() - 1; ++j)
		{
			monVector.at(i).push_back(c);
		}
		monVector.at(i).push_back(monTab[i][mesSimulations.at(0).getCreneau_horaire().size()] / ratio);
	}


	//Affichage de ma nouvelle stratégie

	for(int i = 0; i < (signed)mesSimulations.at(0).getCreneau_horaire().at(0)->batiment.size(); ++i)
	{
		cout << endl;
		for (int j = 0; j < (signed)mesSimulations.at(0).getCreneau_horaire().size() + 1; ++j)
			cout << "\t" << monVector.at(i).at(j);
	}
	cout << endl << endl;
	*/

	return monTabSolution;
}

void creer_fichiers(int iPos, vector<Simulation> mesSimulations, int ** monTabSolution)
{
	char nom_fichier[42];

	for(int i = 0; i < (signed)mesSimulations.at(0).getCreneau_horaire().size() + 1; ++i)	// CRACRA !!!!!!!!!!!!!!!!!!!!!!!!!!!! Mettre taille vector
	{
		sprintf(nom_fichier,"./DATA_GENERATED/Simul_%i/sample_%i.max", iPos + 1, i);
	
		ofstream fichier(nom_fichier, ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
 
		if(fichier)
		{
			string nom = "Valentin";
			int age = 22;
			fichier << mesSimulations.at(0).getCreneau_horaire().at(0)->debut;
			
			for(int j = 0; j < (signed)mesSimulations.at(0).getMax_batiment(); ++j)
				fichier << "A MOI DE JOUERRRRRRRRRRRRRRRRRRRR\n";

			fichier << mesSimulations.at(0).getCreneau_horaire().at(0)->fin;
 
			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}

	
}


vector<string> liste_fichiers_du_dossier(char * path)
{
	string chemin = path;
	chemin.erase(std::remove(chemin.begin(), chemin.end(), '*'), chemin.end());

	vector<string> liste_fichiers;

	WIN32_FIND_DATA File;
    HANDLE hSearch;
	    
    hSearch = FindFirstFile(MultiCharToUniChar(path), &File);
    if (hSearch != INVALID_HANDLE_VALUE)
    {
        do {
			if (UniCharToMultiChar(File.cFileName) != "." && UniCharToMultiChar(File.cFileName) != "..")
				liste_fichiers.push_back(chemin + UniCharToMultiChar(File.cFileName));
        } while (FindNextFile(hSearch, &File));
        
        FindClose(hSearch);
    }

	return liste_fichiers;
}


Simulation construction_simulation(vector<string> listeFichiers)
{
	Simulation maSimulation;

	for (int i = 0; i < (signed)listeFichiers.size(); i++)
		maSimulation.setCreneauHoraire(parserFichier(listeFichiers.at(i)));
	
	//maSimulation.getCreneau_horaire().at(maSimulation.getCreneau_horaire().size() - 1)->batiment.size()
	for (int i = 0; i < (signed)maSimulation.getCreneau_horaire().size(); i++)
		if(maSimulation.getSimulationValide() == true)
			if(maSimulation.getCreneau_horaire().at(i)->valide == false)
				maSimulation.setValide(false);

	//Je mets à jour le nombre max de batiment
	for(int j = 0; j < (signed)maSimulation.getCreneau_horaire().size(); ++j)
		for(int k = 0; k < (signed)maSimulation.getCreneau_horaire().at(j)->batiment.size(); ++k)
			if(!maSimulation.contenir(maSimulation.getCreneau_horaire().at(j)->batiment.at(k)->numero_batiment))
			{
				maSimulation.setTableau_batiment(maSimulation.getCreneau_horaire().at(j)->batiment.at(k)->numero_batiment);
				maSimulation.incrementer_compteur_batiment();
			}

	/*
	for(int i = 0; i < (signed)maSimulation.getMax_batiment(); ++i)
		cerr << "Batiment n " << i << " : " << maSimulation.getTableau_batiment().at(i) << endl;
	*/

	return maSimulation;
}


Creneau_horaire * parserFichier(string fichier)
{
	Creneau_horaire * monCreneauHoraire = new Creneau_horaire();

	char * pch;

	int value;

	string debut;
	string fin;

	long nb_pers_total = 0;
	
    std::ifstream fic(fichier);													// le constructeur de ifstream permet d'ouvrir un fichier en lecture

    if (fic)																	// ce test échoue si le fichier n'est pas ouvert
    {
        std::string ligne;														// variable contenant chaque ligne lue

        while (std::getline(fic, ligne))										// cette boucle s'arrête dès qu'une erreur de lecture survient
        {
            //std::cerr << ligne << std::endl;									// afficher la ligne à l'écran

			char * tmp = new char[ligne.size() + 1];
			strcpy(tmp, ligne.c_str());

			pch = strtok(tmp, " \t\n");

			if(pch != NULL)
			{
				//cerr << pch << endl;

				switch(*pch)
				{
					case 'c': debut += ligne; debut += '\n'; break;

					case 'p': debut += ligne; debut += '\n'; break;

					case 'n':
						debut += ligne;
						debut += '\n';

						pch = strtok(NULL, " \t\n");
						value = atoi(pch);

						pch = strtok(NULL, " \t\n");

						if (*pch == 's')
						{
							monCreneauHoraire->sommet_initial = value;
							//cerr << "Sommet initial du graphe : " << monCreneauHoraire->sommet_initial << endl;
						}
						else if (*pch == 't')
						{
							monCreneauHoraire->sommet_terminal = value;
							//cerr << "Sommet terminal du graphe : " << monCreneauHoraire->sommet_terminal << endl;
						}
						break;

					case 'a':
						pch = strtok(NULL, " \t\n");
						value = atoi(pch);

						if(value == monCreneauHoraire->sommet_initial)
						{
							Batiment * monBatiment = new Batiment();

							pch = strtok(NULL, " \t\n");
							monBatiment->numero_batiment = atoi(pch);
							//cerr << "Nouveau batiment qui porte le numero " << atoi(pch);

							pch = strtok(NULL, " \t\n");
							monBatiment->population = atoi(pch);
							//cerr << " qui contient " << atoi(pch) << " personnes." << endl;

							monCreneauHoraire->batiment.push_back(monBatiment);
						}
						else
						{
							fin += ligne;
							fin += '\n';
						}

						break;

					default: cerr << "---DEFAULT --- " << endl; break;
				}
				pch = strtok(NULL, " \t\n");
			}
			else
				cerr << " **** PCH NULL *** " << endl;
        }
		
		//fic.close();
		monCreneauHoraire->debut = debut;
		monCreneauHoraire->fin = fin;

		/*
		cerr << endl << endl << endl;

		cerr << "Debut du fichier :" << endl <<  endl;
		cerr << debut;
		cerr << endl << endl;

		cerr << "Fin du fichier :" << endl << endl;
		cerr << fin;
		cerr << endl << endl;
		*/
		
		for (int i = 0; i < (signed)monCreneauHoraire->batiment.size(); i++)
		{
			nb_pers_total += monCreneauHoraire->batiment.at(i)->population;
		}

		monCreneauHoraire->flow_max = lancer_flot_max(fichier);

		if(nb_pers_total <= monCreneauHoraire->flow_max)
		{
			monCreneauHoraire->valide = true;
		}
		else
		{
			monCreneauHoraire->valide = false;
		}
    }

	return monCreneauHoraire;
}



void afficher_simulation(Simulation simulation)
{
	cerr << endl << "----------------------------------------------" << endl;
	cerr << "AFFICHAGE DE LA SIMULATION" << endl << endl;

	if (simulation.getSimulationValide())
	{
		cerr << "\tLa simulation est VALIDE" << endl << endl;
	}
	else
	{
		cerr << "\tLa simulation est INVALIDE" << endl << endl;
	}

	cerr << "Cette simulation contient " << simulation.getCreneau_horaire().size() << " creneaux horaires." << endl;

	for (int i = 0; i < (signed)simulation.getCreneau_horaire().size(); i++)
	{
		cerr << endl << endl << "\tCreneau n " << i + 1 << endl;
		if(simulation.getCreneau_horaire().at(i)->valide == true)
		{
			cerr << "\t\tCreneau : VALIDE" << endl << endl;
		}
		else
		{
			cerr << "\t\tCreneau : INVALIDE" << endl << endl;
		}

		cerr << "\t\tSommet initial : " << simulation.getCreneau_horaire().at(i)->sommet_initial << endl;
		cerr << "\t\tSommet final : " << simulation.getCreneau_horaire().at(i)->sommet_terminal << endl << endl;

		cerr << "\t\tValeur de Flot Max : " << simulation.getCreneau_horaire().at(i)->flow_max << endl << endl;

		cerr << "\t\tListe des batiments : " << endl;
		for (int j = 0; j < (signed)simulation.getCreneau_horaire().at(i)->batiment.size(); j++)
		{
			cerr << "\t\t\tBatiment n " << simulation.getCreneau_horaire().at(i)->batiment.at(j)->numero_batiment << " : " << simulation.getCreneau_horaire().at(i)->batiment.at(j)->population << " personnes" << endl;
		}
	}

	cerr << endl << "----------------------------------------------" << endl;
}


long lancer_flot_max(string fichier)
{
	using namespace boost;

	string temp_s;

	typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
  
	typedef adjacency_list	<	listS,
								vecS,
								directedS, 
								property<vertex_name_t, string>,
								property<edge_capacity_t, long, property<edge_residual_capacity_t, long, property<edge_reverse_t, Traits::edge_descriptor> > >
							> Graph;

	Graph g;

	property_map<Graph, edge_capacity_t>::type capacity;
	capacity= get(edge_capacity, g);
  
	property_map<Graph, edge_reverse_t>::type rev;
	rev = get(edge_reverse, g);
  
	property_map<Graph, edge_residual_capacity_t>::type residual_capacity;
	residual_capacity = get(edge_residual_capacity, g);
	
	ofstream result("./DATA_RESULT/Result.txt", ios::out | ios::trunc);

	Traits::vertex_descriptor s, t;

	temp_s = fichier;

	std::ifstream temp_f(temp_s.c_str());

	while(!temp_f.eof())
	{
		getline(temp_f,temp_s);
		read_dimacs_max_flow(g, capacity, rev, s, t, temp_f);
	}


	//read_dimacs_max_flow(g, capacity, rev, s, t, cin);
  
	long flow;

 
/*#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  // Use non-named parameter version
  property_map<Graph, vertex_index_t>::type 
    indexmap = get(vertex_index, g);
  flow = push_relabel_max_flow(g, s, t, capacity, residual_capacity, rev, indexmap);
#else
  */
	flow = push_relabel_max_flow(g, s, t);
//#endif

	result << "c  The total flow:" << endl;
	result << "s " << flow << endl << endl;
	result << "c flow values:" << endl;

	graph_traits<Graph>::vertex_iterator u_iter, u_end;
	graph_traits<Graph>::out_edge_iterator ei, e_end;

	for (std::tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
		for (std::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end; ++ei)
			if (capacity[*ei] > 0)
			{
				result << "f " << *u_iter << " " << target(*ei, g) << " " << (capacity[*ei] - residual_capacity[*ei]) << endl;
			}

	temp_f.close();
	result.close();

	return flow;
}



LPCWSTR MultiCharToUniChar(char* mbString)
{
	int len = strlen(mbString) + 1;
	wchar_t *ucString = new wchar_t[len];
	mbstowcs(ucString, mbString, len);

	return (LPCWSTR)ucString;
}


string UniCharToMultiChar(wchar_t* mbString)
{
	int i, len = 0;

	for (i=0; i<261; i++)
		if(mbString[i] != NULL)
			len += 1;

	char *ucString = new char[len];
	wcstombs(ucString, mbString, len);

	return (string)ucString;
}