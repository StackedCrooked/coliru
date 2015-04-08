#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include "/Archive2/45/a4410ef1bd3024/main.cpp" // alias <libs/graph/src/read_graphviz_new.cpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;

struct Vertex {
    std::string name, label, shape;
};

struct Edge {
    std::string label;
    double weight; // perhaps you need this later as well, just an example
};

typedef property<graph_name_t, std::string> graph_p;
typedef adjacency_list<vecS, vecS, directedS, Vertex, Edge, graph_p> graph_t;

int main() {
    // Construct an empty graph and prepare the dynamic_property_maps.
    graph_t graph(0);

    dynamic_properties dp/*(ignore_other_properties)*/;
    dp.property("node_id", get(&Vertex::name,  graph));
    dp.property("label",   get(&Vertex::label, graph));
    dp.property("shape",   get(&Vertex::shape, graph));
    dp.property("label",   get(&Edge::label,   graph));

    // Use ref_property_map to turn a graph property into a property map
    boost::ref_property_map<graph_t *, std::string> gname(get_property(graph, graph_name));
    dp.property("name",    gname);

    std::ifstream dot("input.dot");

    if (read_graphviz(dot, graph, dp/*, "node_id"*/)) {
        std::cout << "Graph name: '" << get_property(graph, graph_name) << "'\n";
        get_property(graph, graph_name) = "Let's give it a name";
        write_graphviz_dp(std::cout, graph, dp/*, "node_id"*/);
    }
}
