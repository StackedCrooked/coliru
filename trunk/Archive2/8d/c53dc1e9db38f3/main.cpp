#include <boost/graph/adjacency_list.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <iostream>

using namespace boost::adaptors;

using namespace boost;
typedef boost::adjacency_list<setS, vecS, directedS, std::string, char> MyGraph;
typedef boost::graph_traits<MyGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<MyGraph>::edge_descriptor Edge;

int main() {
    MyGraph g;

    // setup
    add_vertex(std::string("xxx"), g);
    Vertex currentVertex = g.vertex_set()[0];
    Vertex endVertex = add_vertex(std::string("yyy"), g);
    add_edge(currentVertex, endVertex, 'i', g);

    for (auto matching : boost::edges(g) | filtered([&g](auto const& e) { return g[e] == 'i'; }))
        std::cout << matching << " --> " << g[matching] << "\n";
}
