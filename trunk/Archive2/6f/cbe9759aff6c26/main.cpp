#include <boost/property_map/property_map.hpp>
#include <boost/property_map/function_property_map.hpp>
#include <boost/property_map/property_map_iterator.hpp>

#include <random>
#include <boost/graph/random.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <fstream>

using namespace boost;

struct propretyEdge {
    std::map<std::string, double> weights; // Date indexed 
};

using Graph = adjacency_list<vecS, vecS, directedS, no_property, propretyEdge>;

void Dijkstra(std::string const& date, Graph const& g, int vertex_origin_num_l = 0) {

    auto dated_weight_f = [&](Graph::edge_descriptor ed) {
        return g[ed].weights.at(date);
    };

    auto dated_weight_map = make_function_property_map<Graph::edge_descriptor, double>(dated_weight_f);

    std::vector<Graph::vertex_descriptor> p(num_vertices(g));
    std::vector<double>                   d(num_vertices(g));
    std::vector<default_color_type>       color_map(num_vertices(g));

    boost::typed_identity_property_map<Graph::vertex_descriptor> vid; // T* property maps were deprecated

    dijkstra_shortest_paths(g, vertex_origin_num_l,
            weight_map(dated_weight_map).
            predecessor_map(make_iterator_property_map(p.data(),   vid)).
            distance_map(make_iterator_property_map(d.data(),      vid)).
            color_map(make_iterator_property_map(color_map.data(), vid))
        );

    std::cout << "distances and parents for '" + date + "':" << std::endl;
    for (auto vd : make_iterator_range(vertices(g)))
    {
        std::cout << "distance(" << vd << ") = " << d[vd] << ", ";
        std::cout << "parent(" << vd << ") = " << p[vd] << std::endl;
    }
    std::cout << std::endl;

    std::ofstream dot_file("dijkstra-eg-" + date + ".dot");

    dot_file << "digraph D {\n"
        "  rankdir=LR\n"
        "  size=\"6,4\"\n"
        "  ratio=\"fill\"\n"
        "  graph[label=\"shortest path on " + date + "\"];\n"
        "  edge[style=\"bold\"]\n" 
        "  node[shape=\"circle\"]\n";

    for (auto ed : make_iterator_range(edges(g))) {
        auto u = source(ed, g),
            v = target(ed, g);

        dot_file 
            << u << " -> " << v << "[label=\"" << get(dated_weight_map, ed) << "\""
            << (p[v] == u?", color=\"black\"" : ", color=\"grey\"")
            << "]";
    }
    dot_file << "}";
}

int main() {
    Graph g;
    std::mt19937 prng { std::random_device{}() };
    generate_random_graph(g, 8, 12, prng);

    uniform_real<double> weight_dist(10,42);
    for (auto e : make_iterator_range(edges(g)))
        for (auto&& date : { "2014-01-01", "2014-02-01", "2014-03-01" })
            g[e].weights[date] = weight_dist(prng);

    for (std::string const& date : { "2014-01-01", "2014-02-01", "2014-03-01" }) {
        Dijkstra(date, g, 0);
    }

}
