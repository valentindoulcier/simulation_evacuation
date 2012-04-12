#include "procedures.h"
#include "Simulation.h"

using namespace std;

int main()
{
	vector<string> listeFichiers;

	vector<Simulation> mesSimulations;

	listeFichiers = liste_fichiers_du_dossier("./DATA_SOURCE/*");

	for (int i = 0; i < (signed)listeFichiers.size(); i++)
		cout << listeFichiers.at(i) << endl;

	mesSimulations.push_back(construction_simulation(listeFichiers));
	

	for (int i = 0; i < (signed)mesSimulations.size(); i++)
	{
		afficher_simulation(mesSimulations.at(i));
	}

	cerr << "how are you?" << endl;
	
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