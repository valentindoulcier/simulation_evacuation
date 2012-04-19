#include "procedures.h"
#include "Simulation.h"

using namespace std;

#define nb_simul 1

int main()
{
	vector<string> listeFichiers;

	vector<Simulation> mesSimulations;

	//lancer_menu();


	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << "\t///////////////////////// SOURCE ///////////////////////////////" << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << endl << endl;

	// Récupération des data d'entrées et construction de la simulation
	listeFichiers = liste_fichiers_du_dossier("./DATA_SOURCE/*");
	mesSimulations.push_back(construction_simulation(listeFichiers));

	// Affichage de la liste des fichiers d'entrée
	cerr << "Fichiers d'entree de la simulation mere :" << endl;
	for (int i = 0; i < (signed)listeFichiers.size(); i++)
		cerr << "\t" << listeFichiers.at(i) << endl;

	// Affichage du résultat de la simulation initiale
	for (int i = 0; i < (signed)mesSimulations.size(); i++)
		afficher_simulation(mesSimulations.at(i));

	listeFichiers.clear();





	cerr << endl << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << "\t///////////////////////// GENERATED ////////////////////////////" << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << endl << endl;

	char nom_dossier[29];

	// On créé les simulations
	simuler(nb_simul, mesSimulations);
	
	// Récupération des data d'entrées et construction de la simulation
	for(int i = 0; i < nb_simul; ++i)
	{
		sprintf(nom_dossier,"./DATA_GENERATED/Simul_%i/*", i + 1);
		listeFichiers = liste_fichiers_du_dossier(nom_dossier);
		
		// Affichage de la liste des fichiers d'entrée
		if(listeFichiers.empty())
		{
			cerr << endl << "Fichiers d'entree de la simulation " << i + 1 << " :" << endl;
			cerr << "\t" << "Dossier EMPTY" << endl;
		}
		else
		{
			cerr << endl << "Fichiers d'entree de la simulation " << i + 1 << " :" << endl;
			for(int j = 0; j < (signed)listeFichiers.size(); ++j)
				cerr << "\t" << listeFichiers.at(j) << endl;
		}

		mesSimulations.push_back(construction_simulation(listeFichiers));
	}
	
	// Affichage du résultat de la simulation
	for (int i = 1; i < (signed)mesSimulations.size(); i++)
		afficher_simulation(mesSimulations.at(i));
		




	cerr << endl << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << "\t///////////////////////// FIN //////////////////////////////////" << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << endl << endl;

	cerr << endl << "how are you?" << endl;
	
	system("pause");
	
	return 0;
}




















/*
	WIN32_FIND_DATA File;
    HANDLE hSearch;
    
    hSearch = FindFirstFile((LPCTSTR)"*.*", &File);
    if (hSearch != INVALID_HANDLE_VALUE)
    {
        do {
            printf("%s\n", File.cFileName);
        } while (FindNextFile(hSearch, &File));
        
        FindClose(hSearch);
    }
	system("pause");
    
    return 0;
*/





// Use a DIMACS network flow file as stdin.
// max_flow < max_flow.dat
//
// Sample output:
//  c  The total flow:
//  s 13
//
//  c flow values:
//  f 0 6 3
//  f 0 1 6
//  f 0 2 4
//  f 1 5 1
//  f 1 0 0
//  f 1 3 5
//  f 2 4 4
//  f 2 3 0
//  f 2 0 0
//  f 3 7 5
//  f 3 2 0
//  f 3 1 0
//  f 4 5 4
//  f 4 6 0
//  f 5 4 0
//  f 5 7 5
//  f 6 7 3
//  f 6 4 0
//  f 7 6 0
//  f 7 5 0