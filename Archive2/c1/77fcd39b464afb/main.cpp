#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/transitive_reduction.hpp>
#include <iostream>

#include <boost/graph/graph_utility.hpp> // dumping graphs
#include <boost/graph/graphviz.hpp>      // generating pictures

using namespace boost;

struct IQsNode { 
    size_t i;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, IQsNode*> Graph;

Graph make_random();

int main() {
    Graph const g = make_random();

    Graph tr;
    std::map<Graph::vertex_descriptor, Graph::vertex_descriptor> g_to_tr;
    std::vector<size_t> id_map(num_vertices(g));
    std::iota(id_map.begin(), id_map.end(), 0u);

    transitive_reduction(g, tr, make_assoc_property_map(g_to_tr), id_map.data());
    for (auto& e : g_to_tr)
        tr[e.second] = g[e.first];

    print_graph(g);
    std::cout << "----------------------------\n";
    for (auto& e : g_to_tr)
        std::cout << "Mapped " << e.first << " to " << e.second << "\n";
    std::cout << "----------------------------\n";
    print_graph(tr);

    // generating graphviz files
    { std::ofstream dot("g.dot");  write_graphviz(dot, g); }
    { std::ofstream dot("tr.dot"); write_graphviz(dot, tr); }
}

// generating test data
#include <boost/graph/random.hpp>
#include <random>
Graph make_random() {
    Graph g;
    std::mt19937 prng (std::random_device{}());
    generate_random_graph(g, 10, 5, prng);

    for (auto v : make_iterator_range(vertices(g)))
        g[v] = new IQsNode { prng() % 20 };

    return g;
}
