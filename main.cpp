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
  using namespace boost;

  string temp_s;


  typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
  typedef adjacency_list<listS, vecS, directedS, 
    property<vertex_name_t, string>,
    property<edge_capacity_t, long,
      property<edge_residual_capacity_t, long,
        property<edge_reverse_t, Traits::edge_descriptor> > >
  > Graph;

 
  Graph g;

  property_map<Graph, edge_capacity_t>::type 
    capacity;
  capacity= get(edge_capacity, g);
  property_map<Graph, edge_reverse_t>::type 
    rev = get(edge_reverse, g);
  property_map<Graph, edge_residual_capacity_t>::type 
    residual_capacity = get(edge_residual_capacity, g);

   freopen("./DATA_RESULT/Result.txt", "w", stdout); 

  Traits::vertex_descriptor s, t;

  temp_s="./DATA_SOURCE/sample.max";
  ifstream temp_f(temp_s.c_str(), ios::in);

  
  while(!temp_f.eof()){
		getline(temp_f,temp_s);
		read_dimacs_max_flow(g, capacity, rev, s, t, temp_f);
  }



  //read_dimacs_max_flow(g, capacity, rev, s, t, cin);
  
  

  long flow;

 
/*#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  // Use non-named parameter version
  property_map<Graph, vertex_index_t>::type 
    indexmap = get(vertex_index, g);
  flow = push_relabel_max_flow(g, s, t, capacity, residual_capacity, rev, indexmap);
#else
  */
  flow = push_relabel_max_flow(g, s, t);
//#endif

  cout << "c  The total flow:" << endl;
  cout << "s " << flow << endl << endl;

  cout << "c flow values:" << endl;
  graph_traits<Graph>::vertex_iterator u_iter, u_end;
  graph_traits<Graph>::out_edge_iterator ei, e_end;
  for (std::tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
    for (std::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end; ++ei)
      if (capacity[*ei] > 0)
        cout << "f " << *u_iter << " " << target(*ei, g) << " " 
                  << (capacity[*ei] - residual_capacity[*ei]) << endl;

  cerr<<"how are you?"<<endl;
  fclose (stdout);
  system("pause");
  
  
  return 0;
  


 // 


}