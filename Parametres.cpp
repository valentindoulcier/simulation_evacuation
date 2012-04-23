#include "Parametres.h"

Parametres * Parametres::instance = NULL;

Parametres::Parametres(void)
{
}


Parametres::~Parametres(void)
{
}


Parametres * Parametres::getInstance ()
{
	if (instance == NULL)
		instance =  new Parametres();

	return instance;
}


void Parametres::setNbSousReplication(int nb)
{
	nb_sous_replication = nb;
}

int Parametres::getNbSousReplication()
{
	return nb_sous_replication;
}

void Parametres::setIntervalleConfiance(int intervalle)
{
	intervalle_de_confiance = intervalle;
}

int Parametres::getIntervalleConfiance()
{
	return intervalle_de_confiance;
}


void Parametres::setAmplitudeAvant(int amplitude)
{
	amplitude_avant = amplitude;
}

int Parametres::getAmplitudeAvant()
{
	return amplitude_avant;
}

void Parametres::setAmplitudeArriere(int amplitude)
{
	amplitude_arriere = amplitude;
}

int Parametres::getAmplitudeArriere()
{
	return amplitude_arriere;
}

void Parametres::setStrategie(int strat)
{
	strategie = strat;
}

int Parametres::getStrategie()
{
	return strategie;
}

void Parametres::setModeDebug(bool mode)
{
	mode_debug = mode;
}

bool Parametres::getModeDebug()
{
	return mode_debug;
}


void Parametres::parserFichierConfiguration()
{
	char * pch;
	
    std::ifstream fic("./DATA_PARAMETRES/configuration.txt");					// le constructeur de ifstream permet d'ouvrir un fichier en lecture

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
					case 'a':
						pch = strtok(NULL, " \t\n");

						amplitude_avant = atoi(pch);
						
						break;

					case 'b':
						pch = strtok(NULL, " \t\n");

						amplitude_arriere = atoi(pch);
						
						break;

					case 'c': break;

					case 'd':
						pch = strtok(NULL, " \t\n");

						if(atoi(pch) == 0)
							mode_debug = false;
						else
							mode_debug = true;
						
						break;

					case 'e':
						pch = strtok(NULL, " \t\n");

						strategie = atoi(pch);
						
						break;

					case 'f':
						pch = strtok(NULL, " \t\n");

						nb_sous_replication = atoi(pch);
						
						break;

					case 'g':
						pch = strtok(NULL, " \t\n");

						intervalle_de_confiance = atoi(pch);
						
						break;

					default: break;
				}
				pch = strtok(NULL, " \t\n");
			}
			else
				cerr << " **** PCH NULL *** " << endl;
        }
    }
}


void Parametres::validationDataEntrees()
{
	if(strategie != 0 && strategie != 1 && strategie != 2)
	{
		strategie = 2;
	}

	if(strategie == 0)
	{
		amplitude_arriere = 0;
	}
	else if(strategie == 1)
	{
		amplitude_avant = 0;
	}
}


void Parametres::afficherParametres()
{
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	cout << "AFFICHAGE DES PARAMETRES" << endl << endl;

	cout << "\tNombre de sous-replication.............." << nb_sous_replication << endl;

	cout << "\tIntervalle de confiance souhaite........" << intervalle_de_confiance << endl;

	cout << "\tChoix de strategie......................" << strategie << endl;

	cout << "\tAmplitude avant........................." << amplitude_avant << endl;

	cout << "\tAmplitude arriere......................." << amplitude_arriere << endl;

	if(mode_debug)
		cout << "\tMode Debug..............................ACTIVE" << endl << endl;
	else
		cout << "\tMode Debug..............................DESACTIVE" << endl << endl;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;
}