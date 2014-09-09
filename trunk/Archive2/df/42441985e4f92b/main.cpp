#include <iostream> 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <algorithm>

using namespace boost;
typedef adjacency_list<boost::listS, boost::listS> Graph;
typedef graph_traits<Graph>::vertex_iterator v_iter;

int main()
{
    Graph g;

	auto
		v1 = add_vertex(g),
		v2 = add_vertex(g),
		v3 = add_vertex(g),
		v4 = add_vertex(g),
		v6 = add_vertex(g);

	add_edge(v1, v2, g);
	add_edge(v1, v4, g);
	add_edge(v2, v3, g);
	add_edge(v2, v6, g);

	std::cout << "num edges: " << num_edges(g) << "; num vertices: " << num_vertices(g) << std::endl;
	for (std::pair<v_iter, v_iter> vp = vertices(g); vp.first != vp.second; ++vp.first) {
		std::cout << std::distance(vertices(g).first, std::find(vertices(g).first, vertices(g).second, *vp.first)) << " ";
	}
}