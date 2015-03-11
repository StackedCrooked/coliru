#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <fstream>
#include <iostream>

using namespace boost;

typedef adjacency_list < listS, vecS, directedS,
        no_property, property < edge_weight_t, int > > graph_t;
typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
typedef std::pair<int, int> Edge;

struct VEdge{
    // custom variables here
    // includes VNodes (custom class) // nodes include coordinates, id, etc
    // weight
    // id
    // etc
};

enum nodes { A, B, C, D, E };

class td {
public:
    td();
    td(std::vector<VEdge*>);
    ~td() {}

    void run_d();

    void print_path();
    void generate_dot_file();
private:
    Edge kEdgeArray[9] = { Edge(A, C), Edge(B, B), Edge(B, D), Edge(B, E),
            Edge(C, B), Edge(C, D), Edge(D, E), Edge(E, A), Edge(E, B)
    };
    char kName[5] = {'A','B','C','D','E'};
    int kWeights[9] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };
    int kNumArcs;
    int kNumNodes;
    vertex_descriptor kS;
    graph_t kGraph;
    std::vector<int> kD;
    std::vector<vertex_descriptor> kP;
    property_map<graph_t, edge_weight_t>::type kWeightMap;
};

td::td() {
    kNumArcs = sizeof(kEdgeArray) / sizeof(Edge);
    kNumNodes = 5;
}

td::td(std::vector<VEdge*> edges) {
    // add edges to the edge property here
    for(VEdge* e : edges) {
        // for each edge, add to the kEdgeArray variable in some way
    }
    kNumArcs = sizeof(kEdgeArray) / sizeof(Edge);
    kNumNodes = 5;
}

void td::run_d() {
    kGraph = graph_t(kEdgeArray, kEdgeArray + kNumArcs, kWeights, kNumNodes);

    kWeightMap = get(edge_weight, kGraph);
    kP = std::vector<vertex_descriptor >(num_vertices(kGraph));
    kD = std::vector<int>(num_vertices(kGraph));
    kS = vertex(A, kGraph);

    dijkstra_shortest_paths(kGraph, kS,
            predecessor_map(boost::make_iterator_property_map(kP.begin(), get(boost::vertex_index, kGraph))).
                    distance_map(boost::make_iterator_property_map(kD.begin(), get(boost::vertex_index, kGraph))));
}

void td::print_path() {
    std::cout << "distances and parents:" << std::endl;
    graph_traits < graph_t >::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(kGraph); vi != vend; ++vi) {
        std::cout << "distance(" << kName[*vi] << ") = " << kD[*vi] << ", ";
        std::cout << "parent(" << kName[*vi] << ") = " << kName[kP[*vi]] << std::
        endl;
    }
}

void td::generate_dot_file() {
    std::cout << std::endl;

    std::ofstream dot_file("figs/dijkstra-eg.dot");

    dot_file << "digraph D {\n"
            << "  rankdir=LR\n"
            << "  size=\"4,3\"\n"
            << "  ratio=\"fill\"\n"
            << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

    graph_traits < graph_t >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(kGraph); ei != ei_end; ++ei) {
        graph_traits < graph_t >::edge_descriptor e = *ei;
        graph_traits < graph_t >::vertex_descriptor
                u = source(e, kGraph), v = target(e, kGraph);
        dot_file << kName[u] << " -> " << kName[v]
                << "[label=\"" << get(kWeightMap, e) << "\"";
        if (kP[v] == u)
            dot_file << ", color=\"black\"";
        else
            dot_file << ", color=\"grey\"";
        dot_file << "]";
    }
    dot_file << "}";
}

int main() {
    td test(std::vector<VEdge*>{});
    test.run_d();

    test.print_path();
}
