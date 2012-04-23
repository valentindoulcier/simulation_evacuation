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
	int nb_sous_replication;
	int intervalle_de_confiance;
	int strategie;
	int amplitude_avant;
	int amplitude_arriere;
	bool mode_debug;
	Parametres(void);
	~Parametres(void);
	static Parametres * instance;

public:
	void parserFichierConfiguration();
	void validationDataEntrees();
	void afficherParametres();

	void setNbReplication(int);
	int getNbReplication();

	void setIntervalleConfiance(int);
	int getIntervalleConfiance();
	
	void setStrategie(int);
	int getStrategie();

	void setAmplitudeAvant(int);
	int getAmplitudeAvant();

	void setAmplitudeArriere(int);
	int getAmplitudeArriere();

	void setModeDebug(bool);
	bool getModeDebug();

	static Parametres * getInstance ();


};

#endif