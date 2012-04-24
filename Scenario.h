#ifndef SCENARIO
#define SCENARIO

#include "Replication.h"

#include <iostream>
#include <vector>

using namespace std;

class Scenario
{

private:
	vector<Replication> replications;
	float moyenne;

public:
	Scenario(void);
	~Scenario(void);

	void setReplications(Replication);
	vector<Replication> getReplications();

	void setMoyenne(float);
	float getMoyenne();

};

#endif
