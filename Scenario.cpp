#include "Scenario.h"


Scenario::Scenario(void)
{
}


Scenario::~Scenario(void)
{
}


vector<Replication> Scenario::getReplications()
{
	return replications;
}


void Scenario::setMoyenne(float moy)
{
	moyenne = moy;
}


float Scenario::getMoyenne()
{
	return moyenne;
}