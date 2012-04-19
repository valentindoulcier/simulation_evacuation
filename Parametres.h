#ifndef PARAMETRES
#define PARAMETRES


#include <iostream>
#include <string>
#include <istream>
#include <fstream>

using namespace std;

class Parametres
{
private:
	int amplitude_avant;
	int amplitude_arriere;
	int strategie;
	int nb_simulation;
	Parametres(void);
	~Parametres(void);
	static Parametres * instance;

public:
	void parserFichierConfiguration();
	void afficherParametres();

	void setAmplitudeAvant(int);
	int getAmplitudeAvant();

	void setAmplitudeArriere(int);
	int getAmplitudeArriere();

	void setStrategie(int);
	int getStrategie();

	void setNbSimulation(int);
	int getNbSimulation();

	static Parametres * getInstance ();


};

#endif