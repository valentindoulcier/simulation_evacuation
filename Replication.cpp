#include "Replication.h"


Replication::Replication(void)
{
	valide = true;
	max_batiment = 0;
}


Replication::~Replication(void)
{
}

void Replication::setValide(bool validite)
{
	valide = validite;
}

bool Replication::getSimulationValide()
{
	return valide;
}


void Replication::setMax_batiment(int nb_bat)
{
	max_batiment = nb_bat;
}

int Replication::getMax_batiment()
{
	return max_batiment;
}

void Replication::incrementer_compteur_batiment()
{
	max_batiment++;
}


void Replication::setTableau_batiment(int value)
{
	tableau_batiment.push_back(value);
}

vector< int > Replication::getTableau_batiment()
{
	return tableau_batiment;
}

bool Replication::contenir(int batiment)
{
	vector< int >::iterator it;
	for(it = tableau_batiment.begin(); it != tableau_batiment.end(); ++it)
		if( (*it) == batiment )
			return true;

	return false;
}


int Replication::indice(int batiment)
{
	vector< int >::iterator it;
	int compteur = 0;
	for(it = tableau_batiment.begin(); it != tableau_batiment.end(); ++it)
	{
		if( (*it) == batiment )
			return compteur;
		compteur++;
	}
	return -1; /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void Replication::setCreneauHoraire(Creneau_horaire * monCreneauHoraire)
{
	creneau_horaire.push_back(monCreneauHoraire);
}

vector< Creneau_horaire * > Replication::getCreneau_horaire()
{
	return creneau_horaire;
}