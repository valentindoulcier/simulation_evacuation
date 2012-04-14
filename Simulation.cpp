#include "Simulation.h"


Simulation::Simulation(void)
{
	valide = true;
	max_batiment = 0;
}


Simulation::~Simulation(void)
{
}

void Simulation::setValide(bool validite)
{
	valide = validite;
}

bool Simulation::getSimulationValide()
{
	return valide;
}


void Simulation::setMax_batiment(int nb_bat)
{
	max_batiment = nb_bat;
}

int Simulation::getMax_batiment()
{
	return max_batiment;
}

void Simulation::incrementer_compteur_batiment()
{
	max_batiment++;
}


void Simulation::setTableau_batiment(int value)
{
	tableau_batiment.push_back(value);
}

vector< int > Simulation::getTableau_batiment()
{
	return tableau_batiment;
}

bool Simulation::contenir(int batiment)
{
	vector< int >::iterator it;
	for(it = tableau_batiment.begin(); it != tableau_batiment.end(); ++it)
		if( (*it) == batiment )
			return true;

	return false;
}


int Simulation::indice(int batiment)
{
	vector< int >::iterator it;
	int compteur = 0;
	for(it = tableau_batiment.begin(); it != tableau_batiment.end(); ++it)
	{
		if( (*it) == batiment )
			return compteur;
		compteur++;
	}
}


void Simulation::setCreneauHoraire(Creneau_horaire * monCreneauHoraire)
{
	creneau_horaire.push_back(monCreneauHoraire);
}

vector< Creneau_horaire * > Simulation::getCreneau_horaire()
{
	return creneau_horaire;
}