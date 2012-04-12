#ifndef SIMULATION
#define SIMULATION

#include <vector>

using namespace std;

typedef struct _Batiment
{
	int numero_batiment;
	int population;
} Batiment;


typedef struct _Creneau_horaire
{
	bool valide;
	long flow_max;
	int sommet_initial;
	int sommet_terminal;
	string debut;
	string fin;
	vector< Batiment * > batiment;
} Creneau_horaire;


class Simulation
{

private:
	bool valide;
	vector< Creneau_horaire * > creneau_horaire;


public:
	Simulation(void);
	~Simulation(void);

	void setValide(bool);
	bool getSimulationValide();

	void setCreneauHoraire(Creneau_horaire * monCreneauHoraire);
	vector< Creneau_horaire * > getCreneau_horaire();
};

#endif