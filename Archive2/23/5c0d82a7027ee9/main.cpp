#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <fstream>
#include <iostream>

struct VEdge {
    int id;
    int source, target;
    double weight;
    // custom variables here
};

class test_dijkstra {
    using graph_t           = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, VEdge>;
    using vertex_descriptor = boost::graph_traits<graph_t>::vertex_descriptor;
    using edge_descriptor   = boost::graph_traits<graph_t>::edge_descriptor;
    using weight_map_t      = boost::property_map<graph_t, double VEdge::*>::type;

  public:
    test_dijkstra(std::vector<VEdge>);
    ~test_dijkstra() {}

    void run_dijkstra();

    void print_path();
    void generate_dot_file();

  private:
    graph_t kGraph;

    std::vector<int> kD;
    std::vector<vertex_descriptor> kP;
};

test_dijkstra::test_dijkstra(std::vector<VEdge> edges) {
    using namespace boost::adaptors;

    size_t max_node;

    boost::partial_sort_copy(
            edges | transformed([](VEdge const &e) -> size_t { return std::max(e.source, e.target); }),
            boost::make_iterator_range(&max_node, &max_node + 1),
            std::greater<size_t>());

    auto e = edges | transformed([](VEdge const &ve) { return std::make_pair(ve.source, ve.target); });
    kGraph = graph_t(e.begin(), e.end(), edges.begin(), max_node + 1);
}

void test_dijkstra::run_dijkstra() {

    weight_map_t kWeightMap = boost::get(&VEdge::weight, kGraph);

    vertex_descriptor kS    = vertex(0, kGraph);
    kP                      = std::vector<vertex_descriptor>(num_vertices(kGraph));
    kD                      = std::vector<int>(num_vertices(kGraph));

    dijkstra_shortest_paths(
        kGraph, kS,
            predecessor_map(boost::make_iterator_property_map(kP.begin(), get(boost::vertex_index, kGraph)))
           .distance_map(boost::make_iterator_property_map(kD.begin(), get(boost::vertex_index, kGraph)))
           .weight_map(kWeightMap));
}

void test_dijkstra::print_path() {
    std::cout << "distances and parents:" << std::endl;
    boost::graph_traits<graph_t>::vertex_iterator vi, vend;

    for (boost::tie(vi, vend) = vertices(kGraph); vi != vend; ++vi) {
        std::cout << "distance(" << *vi << ") = " << kD[*vi] << ", ";
        std::cout << "parent(" << *vi << ") = " << kP[*vi] << "\n";
    }
}

void test_dijkstra::generate_dot_file() {
    weight_map_t kWeightMap = boost::get(&VEdge::weight, kGraph);

    std::ofstream dot_file("figs/dijkstra-eg.dot");

    dot_file << "digraph D {\n"
             << "  rankdir=LR\n"
             << "  size=\"4,3\"\n"
             << "  ratio=\"fill\"\n"
             << "  edge[style=\"bold\"]\n"
             << "  node[shape=\"circle\"]\n";

    boost::graph_traits<graph_t>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(kGraph); ei != ei_end; ++ei) {
        boost::graph_traits<graph_t>::edge_descriptor e = *ei;
        boost::graph_traits<graph_t>::vertex_descriptor u = source(e, kGraph), v = target(e, kGraph);
        dot_file << u << " -> " << v << "[label=\"" << get(kWeightMap, e) << "\"";

        if (kP[v] == u)
            dot_file << ", color=\"black\"";
        else
            dot_file << ", color=\"grey\"";
        dot_file << "]";
    }
    dot_file << "}";
}

int main() {
    std::vector<VEdge> edges {
        { 2100, 0, 2, 1 },
        { 2101, 1, 1, 2 },
        { 2102, 1, 3, 1 },
        { 2103, 1, 4, 2 },
        { 2104, 2, 1, 7 },
        { 2105, 2, 3, 3 },
        { 2106, 3, 4, 1 },
        { 2107, 4, 0, 1 },
        { 2108, 4, 1, 1 },
    };

    test_dijkstra test(edges);
    test.run_dijkstra();

    test.print_path();
    test.generate_dot_file();
}
