#include <iostream>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/property_map/property_map.hpp>

using namespace std;
using namespace boost;

//vertex and node properties
struct VertexProperties {  int state; };
struct EdgeProperties   {  int timestamp; };

//define local vertex property : tag = vertex_index, value = struct VertexProperties
typedef boost::property<boost::vertex_index_t, VertexProperties>  vproperty;

typedef boost::adjacency_list <vecS, vecS, undirectedS, vproperty, boost::no_property> Graph_t;
typedef boost::graph_traits<Graph_t>::vertex_descriptor  vd_t;
typedef boost::graph_traits<Graph_t>::edge_descriptor    ed_t;


//vertex property map internal
typedef typename boost::property_map<Graph_t, boost::vertex_index_t>::type IndexMap;


//define a external vector to store properties of vertices
typedef std::vector <VertexProperties>   PropVector;

//iterator prop map
typedef iterator_property_map <typename PropVector::iterator, IndexMap>  IterMap;


int main() {

Graph_t  G;
vd_t  v = add_vertex(G);
vd_t  u = add_vertex(G);

//create a property vector
PropVector  vd_storage(boost::num_vertices(G));

//get the internal graph index map
IndexMap idxmap = boost::get(vertex_index, G);

//fill the vector property map
IterMap itermap = make_iterator_property_map (vd_storage.begin(), idxmap);

//define a random vertex property
VertexProperties  vp;
vp.state = 100;

// put in itermap
put(itermap, u, vp);


// get from itermap
VertexProperties vpget = get(itermap, u);
cout << " u = " << u << "  get = " << vpget.state << endl;





return 0;
}