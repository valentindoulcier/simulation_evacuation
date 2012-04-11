#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/graph_utility.hpp>

#include <fstream>

#include "procedures.h"

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
using namespace std;

int main()
{
	long result = 0;

	result = lancer_flot_max();

	cerr << "how are you?" << endl << endl;
	cerr << "\tLe resultat est de : " << result << endl;
	
	system("pause");
  
	return 0;
}