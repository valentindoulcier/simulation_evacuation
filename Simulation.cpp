#include "Simulation.h"


Simulation::Simulation(void)
{
	valide = true;
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

void Simulation::setCreneauHoraire(Creneau_horaire * monCreneauHoraire)
{
	creneau_horaire.push_back(monCreneauHoraire);
}

vector< Creneau_horaire * > Simulation::getCreneau_horaire()
{
	return creneau_horaire;
}