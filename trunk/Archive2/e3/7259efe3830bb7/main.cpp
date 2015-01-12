#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dag_shortest_paths.hpp>
#include <iostream>

struct Node {};
struct Edge {};

using namespace std;

void blossom2(vector<Node*>&vertices, vector<Node*> &clients, vector<Edge*> &edges){
    typedef boost::property<boost::edge_weight_t, float> EdgeWeightProperty;

    typedef boost::adjacency_list < boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty > Graph;

    typedef boost::graph_traits < Graph >::vertex_descriptor vertex_descriptor;
    typedef boost::graph_traits < Graph >::edge_descriptor edge_descriptor;
    typedef std::pair<int, int> Edge;

    // Create a graph
    Graph g;

    Graph::vertex_descriptor v0 = boost::add_vertex(g);
    Graph::vertex_descriptor v1 = boost::add_vertex(g);
    Graph::vertex_descriptor v2 = boost::add_vertex(g);

    // Add weighted edges
    EdgeWeightProperty weight0(5);
    boost::add_edge(v0, v1, weight0, g);

    EdgeWeightProperty weight1 = 3;
    boost::add_edge(v1, v2, weight1, g);

    EdgeWeightProperty weight2 = 2;
    boost::add_edge(v2, v0, weight2, g);

    // Create things for Dijkstra
    std::vector<vertex_descriptor> parents(boost::num_vertices(g)); // To store parents
    std::vector<int> distances(boost::num_vertices(g)); // To store distances

    // Compute shortest paths from v0 to all vertices, and store the output in parents and distances
    boost::dijkstra_shortest_paths(g, v0, boost::predecessor_map(&parents[0]).distance_map(&distances[0]));

    // Output results
    std::cout << "distances and parents:" << std::endl;
    boost::graph_traits < Graph >::vertex_iterator vertexIterator, vend;
    for (boost::tie(vertexIterator, vend) = boost::vertices(g); vertexIterator != vend; ++vertexIterator)
    {
        std::cout << "distance(" << *vertexIterator << ") = " << distances[*vertexIterator] << ", ";
        std::cout << "parent(" << *vertexIterator << ") = " << parents[*vertexIterator] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    vector<Node*> vertices, clients;
    vector<Edge*> edges;

    blossom2(vertices, clients, edges);
}
