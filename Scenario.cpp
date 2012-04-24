#include "Scenario.h"


Scenario::Scenario(void)
{
}


Scenario::~Scenario(void)
{
}


void Scenario::setReplications(Replication replic)
{
	replications.push_back(replic);
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