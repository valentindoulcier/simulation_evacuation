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

void Parametres::setNbSimulation(int nb_simul)
{
	nb_simulation = nb_simul;
}

int Parametres::getNbSimulation()
{
	return nb_simulation;
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

						nb_simulation = atoi(pch);
						
						break;

					case 'b':
						pch = strtok(NULL, " \t\n");

						strategie = atoi(pch);
						
						break;

					case 'c': break;

					case 'd':
						pch = strtok(NULL, " \t\n");

						amplitude_avant = atoi(pch);
						
						break;

					case 'e':
						pch = strtok(NULL, " \t\n");

						amplitude_arriere = atoi(pch);
						
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


void Parametres::afficherParametres()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	cout << "\tNombre de simulation : " << nb_simulation << endl;

	cout << "\tChoix de strategie : " << strategie << endl;

	cout << "\tAmplitude avant : " << amplitude_avant << endl;

	cout << "\tAmplitude arriere : " << amplitude_arriere << endl << endl;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
}