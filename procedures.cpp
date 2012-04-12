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
			{
				liste_fichiers.push_back(chemin + UniCharToMultiChar(File.cFileName));
			}
        } while (FindNextFile(hSearch, &File));
        
        FindClose(hSearch);
    }

	return liste_fichiers;
}


Simulation construction_simulation(vector<string> listeFichiers)
{
	Simulation maSimulation;

	for (int i = 0; i < (signed)listeFichiers.size(); i++)
	{
		maSimulation.setCreneauHoraire(parserFichier(listeFichiers.at(i)));
	}

	//maSimulation.getCreneau_horaire().at(maSimulation.getCreneau_horaire().size() - 1)->batiment.size()
	for (int i = 0; i < (signed)maSimulation.getCreneau_horaire().size(); i++)
	{
		if(maSimulation.getSimulationValide() == true)
		{
			if(maSimulation.getCreneau_horaire().at(i)->valide == false)
			{
				maSimulation.setValide(false);
			}
		}
	}

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
	
	//FILE * stream = stdout; ////////////////////////////////////////////////////////////////////////////////////////////////

	//FILE * stream = freopen("./DATA_RESULT/Result.txt", "w", stdout);
	FILE * stream = fopen("./DATA_RESULT/Result.txt", "w");

	Traits::vertex_descriptor s, t;

	temp_s = fichier;

	std::ifstream temp_f(temp_s.c_str());//*****

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

	//cout << "c  The total flow:" << endl;
	//cout << "s " << flow << endl << endl;
	//cout << "c flow values:" << endl;
	fputs ("c  The total flow:\n", stream);
	fputs ("s \n" + flow, stream);
	fputs ("c flow values:\n", stream);

	graph_traits<Graph>::vertex_iterator u_iter, u_end;
	graph_traits<Graph>::out_edge_iterator ei, e_end;

	for (std::tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
		for (std::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end; ++ei)
			if (capacity[*ei] > 0)
			{
				fputs ("f " + *u_iter, stream);
				fputs (" " + target(*ei, g), stream);
				fputs (" " + (capacity[*ei] - residual_capacity[*ei]), stream);
				fputc ('\n', stream);
			}

	//fclose (stream);
	//fclose (stdout);
	temp_f.close();
	fclose(stream);

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