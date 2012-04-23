#include "procedures.h"
#include "Replication.h"
#include "Parametres.h"
#include "Scenario.h"

#include "time.h"

using namespace std;


typedef struct _Analyse
{
	int nb_scenario;
	int intervalle_de_confiance;
	vector<float> moyenne;

} Analyse;


int main()
{
	SetConsoleTitle(MultiCharToUniChar("DOULCIER_MARCINKOWSKI  -  Projet ACCELL"));

	clock_t start;
	clock_t end;
    double elapsed;

	// Lancement de la mesure
	start = clock();

	Parametres * parametres;
	parametres = Parametres::getInstance();
	parametres->parserFichierConfiguration();
	parametres->validationDataEntrees();
	parametres->afficherParametres();

	//system("COLOR F0");
	//Color(15,12);
	Color(0,12);
    printf("Test Before\n");
	//Color(15,0);
	Color(0,7);
    printf("Test After\n");

	Analyse * analyse = new Analyse();
	analyse->nb_scenario = 0;
	analyse->intervalle_de_confiance = 0;

	vector<string> listeFichiers;

	Replication maReplicationMere;

	vector<Scenario> mesScenarios;

	cerr << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << "\t///////////////////////// SOURCE ///////////////////////////////" << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << endl << endl;

	// Récupération des data d'entrées et construction de la simulation
	listeFichiers = liste_fichiers_du_dossier("./DATA_SOURCE/*");
	maReplicationMere = construction_replication(listeFichiers);

	// Affichage de la liste des fichiers d'entrée
	cerr << "Fichiers d'entree de la simulation mere :" << endl;
	for (int i = 0; i < (signed)listeFichiers.size(); i++)
		cerr << "\t" << listeFichiers.at(i) << endl;
	cerr << endl;

	// Affichage du résultat de la simulation initiale
	afficher_replication(maReplicationMere);

	listeFichiers.clear();




	cerr << endl << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << "\t///////////////////////// GENERATED ////////////////////////////" << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << endl << endl;

	char nom_dossier[50];


	while(parametres->getIntervalleConfiance() > analyse->intervalle_de_confiance)
	{
		for(int i = 0; i < 5; ++i)
		{
			Scenario tempo;
			float somme = 0;
			//tempo.getReplications().clear();

			analyse->nb_scenario++;

			sprintf(nom_dossier,"./DATA_GENERATED/Scenario_%i", analyse->nb_scenario);
			CreateDirectory(MultiCharToUniChar(nom_dossier), NULL);


			// On créé les réplications
			repliquer(analyse->nb_scenario, parametres->getNbReplication(), maReplicationMere);

			
			// Récupération des data d'entrées et construction de la simulation
			for(int j = 0; j < parametres->getNbReplication(); ++j)
			{
				sprintf(nom_dossier,"./DATA_GENERATED/Scenario_%i/Replication_%i/*", analyse->nb_scenario, j + 1);
				listeFichiers = liste_fichiers_du_dossier(nom_dossier);
		
				// Affichage de la liste des fichiers d'entrée
				if(listeFichiers.empty())
				{
					cerr << endl << "Fichiers d'entree de la simulation " << j + 1 << " :" << endl;
					cerr << "\t" << "Dossier EMPTY" << endl;
				}
				else
				{
					cerr << endl << "Fichiers d'entree de la replication " << j + 1 << " :" << endl;
					for(int k = 0; k < (signed)listeFichiers.size(); ++k)
					{
						cerr << "\t" << listeFichiers.at(k) << endl;
					}
				}
				tempo.getReplications().push_back(construction_replication(listeFichiers));
			}
			/*for(int  cpt =0; cpt < parametres->getNbReplication() ; ++cpt)
			{
				if(tempo.getReplications().at(cpt).getSimulationValide())
					somme++;
			}*/
			//push back du scenario tempo
			//tempo.setMoyenne(somme/= parametres->getNbReplication());
			mesScenarios.push_back(tempo);
			
		}
		/*
		float moyenne=0;
		for(int cpt = analyse->nb_scenario; cpt > analyse->nb_scenario-5; --cpt)
		{
			moyenne+= mesScenarios.at(cpt).getMoyenne();
		}
		moyenne /=5;

		analyse->moyenne.push_back(moyenne);
		*/
		analyse->intervalle_de_confiance++;
		//Calcul des nouveaux résultats

	}
	

	// Affichage du résultat de la simulation
	//for (int i = 1; i < (signed)mesSimulations.size(); i++)
	//	afficher_replication(mesSimulations.at(i));



	cerr << endl << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << "\t///////////////////////// FIN //////////////////////////////////" << endl;
	cerr << "\t////////////////////////////////////////////////////////////////" << endl;
	cerr << endl << endl;

	cerr << endl << "how are you?" << endl;

	// Arret de la mesure
	end = clock();
	elapsed = ((double)end - start) / CLOCKS_PER_SEC; // Conversion en seconde 
    
    cout << endl << "Ce programme s'est execute en " << elapsed << " secondes." << endl;

	system("pause");
	
	return 0;
}

/*
x correspond à la couleur du texte
y correspond à la couleur de fond

les valeurs:
0: noir
1: bleu foncé
2: vert
3: bleu-gris
4: marron
5: pourpre
6: kaki
7: gris clair
8: gris
9: bleu
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc 
*/

















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