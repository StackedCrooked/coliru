#include <iostream>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <vector>

using namespace std;
using namespace boost;

int main() {
    typedef adjacency_list<vecS, vecS, undirectedS, no_property,
            property<edge_weight_t, int> > Graph;

    typedef graph_traits<Graph>::edge_descriptor Edge;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    int num_vertices, num_edges;
    cin >> num_vertices >> num_edges;

    Graph g(num_vertices);

    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
    vector<Edge> spanning_tree;

    for (int i = 0; i < num_edges; i++) {
        bool success;
        Edge e;
        int a, b, c;
        cin >> a >> b >> c;
        tie(e, success) = add_edge(a, b, g);
        weightmap[e] = c;
    }

    kruskal_minimum_spanning_tree(g, back_inserter(spanning_tree));

    // weight of spanning tree
    int ww = 0;
    for (auto const& e : spanning_tree) {
        std::cout << "Traversing: " << source(e,g) << " -> " << target(e,g) << ", cost " << weightmap[e] << "\n";
        ww += weightmap[e];
    }

    cout << "\n" << ww;
}
