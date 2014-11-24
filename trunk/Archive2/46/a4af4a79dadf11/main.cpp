#include <iostream>
#include<boost/config.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/prim_minimum_spanning_tree.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/config.hpp>
#include <vector>
#include <list>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>

namespace boost
{
  struct edge_component_t  //custom edge property
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}

using namespace std;
using namespace boost;

void testcase();

int main() {

    int n;
    cin >> n;

    while(n--)
    {
        testcase();
    }


    return 0;
}

void testcase()
{
    typedef adjacency_list < vecS, vecS, undirectedS,
        no_property, property < edge_component_t, std::size_t > >graph_t;
      typedef graph_traits < graph_t >::vertex_descriptor vertex_t;
      typedef graph_traits < graph_t >::edge_iterator edge_it;
      typedef graph_traits < graph_t >::vertex_iterator vertex_it;


      int num_nodes,num_edges;

      cin >> num_nodes >> num_edges;

      graph_t g(num_nodes);

      for(int i=0;i<num_edges;i++)
      {
          int a,b;

          cin >> a >> b;
          add_edge(a-1,b-1,g);
      }

      property_map < graph_t, edge_component_t >::type
        component = get(edge_component, g);

      std::size_t num_comps = biconnected_components(g, component);
      std::cerr << "Found " << num_comps << " biconnected components.\n";

      std::vector <vertex_t> art_points;
      articulation_points(g, std::back_inserter(art_points));
      for (vector<vertex_t>::iterator vi = art_points.begin(); vi != art_points.end() ; vi++)
          {
              std::cerr << *vi << endl; //This is missing,why? (even if I use cout <<)

          }
      std::cerr << "Found " << art_points.size() << " articulation points.\n";

}
