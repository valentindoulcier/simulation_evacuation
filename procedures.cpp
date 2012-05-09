#include "procedures.h"



void repliquer(int num_scenario, int nb_replication, Replication maReplicationMere)
{
	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	for(int i = 0; i < nb_replication; ++i)
	{
		creer_replication(num_scenario, i, maReplicationMere);
	}
}


void creer_replication(int num_scenario, int iPos, Replication maReplicationMere)
{
	creer_dossier_replication(num_scenario, iPos);
	creer_fichiers(num_scenario, iPos, maReplicationMere, calculer_strategie(num_scenario, iPos, maReplicationMere));
}


void creer_dossier_replication(int num_scenario, int iPos)
{
	char nom_dossier[46];

	sprintf(nom_dossier,"./DATA_GENERATED/Scenario_%i/Replication_%i", num_scenario, iPos + 1);
	
	//RemoveDirectory(MultiCharToUniChar(nom_dossier));

	CreateDirectory(MultiCharToUniChar(nom_dossier), NULL);
}



// Fonction qui construit une matrice de la population de la simulation initiale et qui retourne une nouvelle matrice.
vector < list<int> > calculer_strategie(int num_scenario, int iPos, Replication maReplicationMere)
{
	static int compteur = 0;
	compteur++;

	Parametres * parametres;
	parametres = Parametres::getInstance();

	// x% des gens ont une chance de RESTER sur place.
	float ratio;

	// Nombre de créneau AJOUTES => n + 1 possibilités (avec n = nb_amplitude)
	int amplitude_avant = parametres->getAmplitudeAvant();
	int amplitude_arriere = parametres->getAmplitudeArriere();

	// Stratégie : [ 0 Anticipe ] [ 1 Retarde ] [ 2 Aléatoire ]
	int strategie = parametres->getStrategie();

	/* generate secret number: */
	float chance;

	int ** monTab;
	vector<int> nb_personne_par_bat;

	//Déclaration de mon tableau
	monTab = new int* [maReplicationMere.getMax_batiment()];
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		monTab[i] = new int [maReplicationMere.getCreneau_horaire().size()];
	
	//Remplissage de mon tableau
		//Initialisation à 0
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size(); ++j)
			monTab[i][j] = 0;

		//Remplissage réel
	int indice = -1;
	for (int i = 0; i < (signed)maReplicationMere.getCreneau_horaire().size(); ++i)
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().at(i)->batiment.size(); ++j)
		{
			indice = maReplicationMere.indice(maReplicationMere.getCreneau_horaire().at(i)->batiment.at(j)->numero_batiment);
			monTab[indice][i] = maReplicationMere.getCreneau_horaire().at(i)->batiment.at(j)->population;
		}

	int somme;
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
	{
		somme = 0;
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size(); ++j)
			somme += monTab[i][j];
		nb_personne_par_bat.push_back(somme);
	}

	//for(int i = 0; i < (signed)nb_personne_par_bat.size(); ++i)
	//	cerr << "\n" << nb_personne_par_bat.at(i);

	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::trunc);			// ouverture en écriture avec effacement du fichier ouvert
 
		if(fichier)
		{
			fichier << "\n\n";
			fichier << "\t//////////////////////////////////\n";
			fichier << "\t/////////// Scénario_" << num_scenario << " ///////////\n";
			fichier << "\t//////////////////////////////////\n";

			fichier << "\n\n";
			fichier << "//////////////////////////////////\n";
			fichier << "///////// Replication_" << iPos + 1 << " //////////\n";
			fichier << "//////////////////////////////////\n";
			fichier << "\n\n";


			fichier << "\tSOLUTION MERE\n\n";

			//Affichage de mon tableau
			for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
			{
				fichier << "\n\t";
				for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size(); ++j)
					fichier << "\t" << monTab[i][j];
			}
			fichier << "\n\n\n\n";

			fichier << "\tAMPLITUDE AVANT\n\n";

			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}




	float ** anticipation;

	//Déclaration de mon tableau
	anticipation = new float* [maReplicationMere.getMax_batiment()];
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		anticipation[i] = new float [amplitude_avant + 1];
	
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
	{
		ratio = (float)(rand() % 100);

		if(parametres->getModeDebug())
		{
			char nom_fichier[50];

			sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
			ofstream fichier(nom_fichier, ios::out | ios::app);
 
			if(fichier)
			{
				fichier << "\t\tRatio d'anticipation du batiment " << i + 1 << " : " << ratio << "%\n";
				fichier << "\n";

				fichier.close();
			}
			else
				cerr << "Impossible d'ouvrir le fichier !" << endl;
		}

		for (int j = amplitude_avant; j >= 0; j--)
		{
			if( j == amplitude_avant )
			{
				anticipation[i][j] = ratio / 100;
			}
			else
			{
				anticipation[i][j] = (j + 1) * ( ( 1 - ( ratio / 100 ) ) / ( (amplitude_avant * ( amplitude_avant + 1 ) ) / 2 ) );
			}
		}
	}

	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < amplitude_avant + 1; ++j)
			anticipation[i][j + 1] = anticipation[i][j] + anticipation[i][j + 1];


	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::app);
 
		if(fichier)
		{
			for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
			{
				fichier << "\n\t";
				for (int j = 0; j < amplitude_avant + 1; ++j)
					fichier << "\t" << anticipation[i][j];
			}
			fichier << "\n\n\n";

			fichier << "\tAMPLITUDE ARRIERE\n\n";

			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}


	float ** retardement;

	//Déclaration de mon tableau
	retardement = new float* [maReplicationMere.getMax_batiment()];
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		retardement[i] = new float [amplitude_arriere + 1];
	

	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
	{
		ratio = (float)(rand() % 100);

		if(parametres->getModeDebug())
		{
			char nom_fichier[50];

			sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
			ofstream fichier(nom_fichier, ios::out | ios::app);
 
			if(fichier)
			{
				fichier << "\t\tRatio de retardement du batiment " << i << " : " << ratio << "%\n";
				fichier << "\n";

				fichier.close();
			}
			else
				cerr << "Impossible d'ouvrir le fichier !" << endl;
		}

		for (int j = 0; j <= amplitude_arriere; j++)
		{
			if( j == 0 )
			{
				retardement[i][j] = ratio / 100;
			}
			else
			{
				retardement[i][j] = (amplitude_arriere + 1 - j) * ( ( 1 - ( ratio / 100 ) ) / ( (amplitude_arriere * ( amplitude_arriere + 1 ) ) / 2 ) );
			}
		}
	}

	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < amplitude_arriere + 1; ++j)
			retardement[i][j + 1] = retardement[i][j] + retardement[i][j + 1];


	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::app);
 
		if(fichier)
		{
			for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
			{
				fichier << "\n\t";
				for (int j = 0; j < amplitude_arriere + 1; ++j)
					fichier << "\t" << retardement[i][j];
			}
			fichier << "\n\n\n\n";

			fichier << "\tPROBABILITES CUMULEES FINALES PAR CRENEAU\n\n";

			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}


	float ** monTabSolution;

	//Déclaration de mon tableau
	monTabSolution = new float* [maReplicationMere.getMax_batiment()];
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		monTabSolution[i] = new float [maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere]; //TAILLE DU TABLEAU ADAPTEE


	//Initialisation à 0
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
			monTabSolution[i][j] = 0;
	
	//Remplissage de mon tableau
	int tempo = 0;
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
	{
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size(); ++j)
		{
			for(int k = 0; k < (signed)maReplicationMere.getCreneau_horaire().at(j)->batiment.at(i)->population; ++k)
			{
				//GERER CAS ALEATOIRE
				tempo = strategie;

				if(tempo == 2)
					tempo = rand() % 2;

				chance = (float)(rand() % 1000);
				chance /= 1000;
				indice = -1;
				
				switch(tempo)
				{
					case 0 :

						do{
							indice++;
						} while(chance > anticipation[i][indice]);

						monTabSolution[i][indice + j] += 1;
						
						
						break;

					case 1 :
						
						do{
							indice++;
						} while(chance > retardement[i][indice]);

						monTabSolution[i][indice + j + amplitude_avant] += 1;
						
						break;

					default: break;
				}
			}
		}
	}

	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
			monTabSolution[i][j] = monTabSolution[i][j] / nb_personne_par_bat.at(i);

	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
			monTabSolution[i][j + 1] = monTabSolution[i][j] + monTabSolution[i][j + 1];

	

	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::app);
 
		if(fichier)
		{
			for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
			{
				fichier << "\n\t";
				for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
					fichier << "\t" << monTabSolution[i][j];
			}
			fichier << "\n\n\n\n";

			fichier << "\tNOUVEAUX EFFECTIFS CUMULES PAR CRENEAU\n\n";

			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}


	int ** maPopulation;

	//Déclaration de mon tableau
	maPopulation = new int* [maReplicationMere.getMax_batiment()];
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		maPopulation[i] = new int [maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere];

	//Initialisation à 0
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
			maPopulation[i][j] = 0;

	
	vector < list<int> > monVector;
	list<int>::iterator it;
	//monVector.at(0).push_front(5);
	//monVector.at(0).front();


	//Calcul de ma nouvelle stratégie
	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
	{
		for(int j = 0; j < nb_personne_par_bat.at(i); ++j)
		{
			chance = (float)(rand() % 1000);
			chance /= 1000;
			indice = -1;

			do{
				indice++;
			} while(chance > monTabSolution[i][indice]);

			maPopulation[i][indice] += 1;
		}
	}


	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::app);
 
		if(fichier)
		{
			for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
			{
				fichier << "\n\t";
				for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
					fichier << "\t" << maPopulation[i][j];
			}
			fichier << "\n\n";
			
			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
	

	for(int i = 0; i < (signed)maReplicationMere.getMax_batiment(); ++i)
	{
		list<int> maListe;
		monVector.push_back(maListe);

		for (int j = 0; j < (signed)maReplicationMere.getCreneau_horaire().size() + amplitude_avant + amplitude_arriere; ++j)
		{
			monVector.at(i).push_back(maPopulation[i][j]);
		}
	}

	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::app);
 
		if(fichier)
		{
			for(int i = 0; i < (signed)monVector.size(); ++i)
			{
				fichier << "\n\t";
				for(it = monVector.at(i).begin(); it != monVector.at(i).end(); ++it)
					fichier << "\t" << (*it);
			}
			fichier << "\n\n";
			
			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}

	

	return monVector;
}

void creer_fichiers(int num_scenario, int iPos, Replication maReplicationMere, vector < list<int> > monVector)
{
	Parametres * parametres;
	parametres = Parametres::getInstance();

	char nom_fichier[60];

	int cas = parametres->getStrategie();

	int nb_creneau_simul_mere = maReplicationMere.getCreneau_horaire().size();
	int nb_creneau_simul_cree = monVector.at(0).size();
	int nb_creneau_simul_diff = abs(nb_creneau_simul_mere - nb_creneau_simul_cree);
	int tempo = nb_creneau_simul_mere;
	
	//cerr << "Nombre de creneau de la simul mere : " << nb_creneau_simul_mere << endl;
	//cerr << "Nombre de creneau de la simul cree : " << nb_creneau_simul_cree << endl;
	//cerr << "\t Rajout de " << abs(nb_creneau_simul_mere - nb_creneau_simul_cree) << " simulations" << endl;


	for(int i = 0; i < nb_creneau_simul_cree; ++i) // Je tape la liste
	{
		sprintf(nom_fichier,"./DATA_GENERATED/Scenario_%i/Replication_%i/sample_%i.max", num_scenario, iPos + 1, i);
	
		ofstream fichier(nom_fichier, ios::out | ios::trunc);						// ouverture en écriture avec effacement du fichier ouvert
 
		if(fichier)
		{
			if(cas == 0) // On ANTICIPE
			{
				if(nb_creneau_simul_diff > 0) // ON AVANCE ET Y'A DES CRENEAUX EN PLUS
				{
					//cerr << "ANTICIPE " << i << endl;
					fichier << maReplicationMere.getCreneau_horaire().at(0)->debut;
			
					for(int j = 0; j < (signed)maReplicationMere.getMax_batiment(); ++j)
					{
						fichier << "a " << maReplicationMere.getCreneau_horaire().at(0)->sommet_initial << " " << maReplicationMere.getTableau_batiment().at(j) << " " << monVector.at(j).front() << endl;
						monVector.at(j).pop_front();
					}

					fichier << maReplicationMere.getCreneau_horaire().at(0)->fin;

					nb_creneau_simul_diff--;
				}
				else
				{
					//cerr << "NORMAL " << i << endl;
					fichier << maReplicationMere.getCreneau_horaire().at(i - abs(nb_creneau_simul_mere - nb_creneau_simul_cree))->debut;
			
					for(int j = 0; j < (signed)maReplicationMere.getMax_batiment(); ++j)
					{
						fichier << "a " << maReplicationMere.getCreneau_horaire().at(i - abs(nb_creneau_simul_mere - nb_creneau_simul_cree))->sommet_initial << " " << maReplicationMere.getTableau_batiment().at(j) << " " << monVector.at(j).front() << endl;
						monVector.at(j).pop_front();
					}

					fichier << maReplicationMere.getCreneau_horaire().at(i - abs(nb_creneau_simul_mere - nb_creneau_simul_cree))->fin;
				}
			}
			else if(cas == 1) // ON RETARDE
			{
				if(tempo > 0)
				{
					cerr << "NORMAL " << i << endl;
					fichier << maReplicationMere.getCreneau_horaire().at(i - abs(nb_creneau_simul_mere - nb_creneau_simul_cree))->debut;
			
					for(int j = 0; j < (signed)maReplicationMere.getMax_batiment(); ++j)
					{
						fichier << "a " << maReplicationMere.getCreneau_horaire().at(i - abs(nb_creneau_simul_mere - nb_creneau_simul_cree))->sommet_initial << " " << maReplicationMere.getTableau_batiment().at(j) << " " << monVector.at(j).front() << endl;
						monVector.at(j).pop_front();
					}

					fichier << maReplicationMere.getCreneau_horaire().at(i - abs(nb_creneau_simul_mere - nb_creneau_simul_cree))->fin;

					tempo--;
				}
				else if(nb_creneau_simul_diff > 0) // ON RETARDE ET Y'A DES CRENEAUX EN PLUS
				{
					cerr << "RETARDE " << i << endl;
					fichier << maReplicationMere.getCreneau_horaire().at(maReplicationMere.getCreneau_horaire().size())->debut;
			
					for(int j = 0; j < (signed)maReplicationMere.getMax_batiment(); ++j)
					{
						fichier << "a " << maReplicationMere.getCreneau_horaire().at(maReplicationMere.getCreneau_horaire().size())->sommet_initial << " " << maReplicationMere.getTableau_batiment().at(j) << " " << monVector.at(j).front() << endl;
						monVector.at(j).pop_front();
					}

					fichier << maReplicationMere.getCreneau_horaire().at(maReplicationMere.getCreneau_horaire().size())->fin;

					nb_creneau_simul_diff--;
				}
			}
			else
				cerr << "PROBLEME : ANTICIPE OU RETARDE ?" << endl;
 
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


Replication construction_replication(vector<string> listeFichiers)
{
	Replication maReplication;

	for (int i = 0; i < (signed)listeFichiers.size(); i++)
		maReplication.setCreneauHoraire(parserFichier(listeFichiers.at(i)));
	
	//maSimulation.getCreneau_horaire().at(maSimulation.getCreneau_horaire().size() - 1)->batiment.size()
	for (int i = 0; i < (signed)maReplication.getCreneau_horaire().size(); i++)
		if(maReplication.getSimulationValide() == true)
			if(maReplication.getCreneau_horaire().at(i)->valide == false)
				maReplication.setValide(false);

	//Je mets à jour le nombre max de batiment
	for(int j = 0; j < (signed)maReplication.getCreneau_horaire().size(); ++j)
		for(int k = 0; k < (signed)maReplication.getCreneau_horaire().at(j)->batiment.size(); ++k)
			if(!maReplication.contenir(maReplication.getCreneau_horaire().at(j)->batiment.at(k)->numero_batiment))
			{
				maReplication.setTableau_batiment(maReplication.getCreneau_horaire().at(j)->batiment.at(k)->numero_batiment);
				maReplication.incrementer_compteur_batiment();
			}

	/*
	for(int i = 0; i < (signed)maSimulation.getMax_batiment(); ++i)
		cerr << "Batiment n " << i << " : " << maSimulation.getTableau_batiment().at(i) << endl;
	*/

	return maReplication;
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


void afficher_replication(Replication maReplication)
{
	cerr << endl << "----------------------------------------------" << endl;
	cerr << "AFFICHAGE DE LA SIMULATION" << endl << endl;

	if (maReplication.getSimulationValide())
	{
		cerr << "\tLa simulation est VALIDE" << endl << endl;
	}
	else
	{
		cerr << "\tLa simulation est INVALIDE" << endl << endl;
	}

	cerr << "Cette simulation contient " << maReplication.getCreneau_horaire().size() << " creneaux horaires." << endl;

	for (int i = 0; i < (signed)maReplication.getCreneau_horaire().size(); i++)
	{
		cerr << endl << endl << "\tCreneau n " << i + 1 << endl;
		if(maReplication.getCreneau_horaire().at(i)->valide == true)
		{
			cerr << "\t\tCreneau : VALIDE" << endl << endl;
		}
		else
		{
			cerr << "\t\tCreneau : INVALIDE" << endl << endl;
		}

		cerr << "\t\tSommet initial : " << maReplication.getCreneau_horaire().at(i)->sommet_initial << endl;
		cerr << "\t\tSommet final : " << maReplication.getCreneau_horaire().at(i)->sommet_terminal << endl << endl;

		cerr << "\t\tValeur de Flot Max : " << maReplication.getCreneau_horaire().at(i)->flow_max << endl << endl;

		cerr << "\t\tListe des batiments : " << endl;
		for (int j = 0; j < (signed)maReplication.getCreneau_horaire().at(i)->batiment.size(); j++)
		{
			cerr << "\t\t\tBatiment n " << maReplication.getCreneau_horaire().at(i)->batiment.at(j)->numero_batiment << " : " << maReplication.getCreneau_horaire().at(i)->batiment.at(j)->population << " personnes" << endl;
		}
	}

	cerr << endl << "----------------------------------------------" << endl;
}


void enregistrer_replication(int num_scenario, int iPos, Replication maReplication)
{
	Parametres * parametres;
	parametres = Parametres::getInstance();


	if(parametres->getModeDebug())
	{
		char nom_fichier[50];

		sprintf(nom_fichier,"./DATA_DEBUG/Scenario_%i/Réplication_%i.txt", num_scenario + 1, iPos + 1);
	
		ofstream fichier(nom_fichier, ios::out | ios::app);
 
		if(fichier)
		{
			fichier << "\n----------------------------------------------\n";
			fichier << "AFFICHAGE DE LA SIMULATION\n\n";

			if (maReplication.getSimulationValide())
			{
				fichier << "\tLa simulation est VALIDE\n\n";
			}
			else
			{
				fichier << "\tLa simulation est INVALIDE\n\n";
			}

			fichier << "Cette simulation contient " << maReplication.getCreneau_horaire().size() << " creneaux horaires.\n";

			for (int i = 0; i < (signed)maReplication.getCreneau_horaire().size(); i++)
			{
				fichier << "\n\n\tCreneau n " << i + 1 << "\n";
				if(maReplication.getCreneau_horaire().at(i)->valide == true)
				{
					fichier << "\t\tCreneau : VALIDE\n\n";
				}
				else
				{
					fichier << "\t\tCreneau : INVALIDE\n\n";
				}

				fichier << "\t\tSommet initial : " << maReplication.getCreneau_horaire().at(i)->sommet_initial << "\n";
				fichier << "\t\tSommet final : " << maReplication.getCreneau_horaire().at(i)->sommet_terminal << "\n\n";

				fichier << "\t\tValeur de Flot Max : " << maReplication.getCreneau_horaire().at(i)->flow_max << "\n\n";

				fichier << "\t\tListe des batiments : \n";
				for (int j = 0; j < (signed)maReplication.getCreneau_horaire().at(i)->batiment.size(); j++)
				{
					fichier << "\t\t\tBatiment n " << maReplication.getCreneau_horaire().at(i)->batiment.at(j)->numero_batiment << " : " << maReplication.getCreneau_horaire().at(i)->batiment.at(j)->population << " personnes\n";
				}
			}

			fichier << "\n----------------------------------------------\n";

			fichier.close();
		}
		else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}


bool Statistiques(vector<Scenario> mesScenarios, Analyse * analyse)
{
		//////////////////////////////
		////Moyennes//////////////////
		//////////////////////////////

		Parametres * parametres;
		parametres = Parametres::getInstance();

		bool stop = false;

		
		float moyenne=0;				//Moyenne pour 5 scénarios
		float X = 0;					//Moyenne de tous les blocs de 5 scnénarios		
		float ecartType = 0;
		float tmp = 0;
		
		//
		float intervalleConf = parametres->getIntervalleConfiance();
		float A = (1 - (intervalleConf/2));
		float t = 0;
		float r;


		for(int cpt = analyse->nb_scenario - 1 ; cpt >= analyse->nb_scenario - 5; --cpt)
		{
			moyenne += mesScenarios.at(cpt).getMoyenne();
			//cerr << " Moyenne  ... " << " Compteur  " << cpt << "     Get Moyenne : " << mesScenarios.at(cpt).getMoyenne() << endl;
		}
		moyenne /= 5;

		analyse->moyenne.push_back(moyenne);		//on insère les moyennes (des blocs de 5 scénarios)


		analyse->intervalle_de_confiance++;
		//Calcul des nouveaux résultats


		for(int cpt = 0; cpt < analyse->nb_scenario / 5; ++ cpt)
		{
			X += analyse->moyenne.at(cpt);
			//cerr << " Moyenne   " << moyenne << endl;
		}
		X /= analyse->moyenne.size();			//moyenne de tous les  blocs de 5 scnénarios	


		//calcul de l'écart type
		for(int cpt = 0; cpt < analyse->nb_scenario / 5; ++ cpt)
		{			
			//calcul de Somme (xi - Moyenne )
			tmp += pow((analyse->moyenne.at(cpt) - X),2);
		}
		ecartType = sqrt(tmp/(analyse->nb_scenario/5));
		

		//intervalle de confiance
		for(int i=1; i<11 ;++i)
		{
			for(int j=1; j< 41; ++j)
			{
				if(A > parametres->getValeurMatrice(i,j))
				{
					t = parametres->getValeurMatrice(0,j) + parametres->getValeurMatrice (i,0);
					break;
				}
			}
		}
		
		r = (t * ecartType )/sqrt((float)(analyse->nb_scenario/5));

		if( (X * r) > ( X * parametres->getIntervalleConfiance()) )	//Si notre +- X% est supérieur à l'intervalle de confiance que l'on souhaite, on continueras ...
			return false;
		else
			return true;

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


void Color(int f, int t)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}