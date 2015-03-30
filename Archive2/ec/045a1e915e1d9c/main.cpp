#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/subgraph.hpp>
#include <iostream>

#include <boost/graph/random.hpp> // in case you comment out the random graph creation code
#include <random>

using namespace boost;

template <typename SubGraph> SubGraph generate_random()
{
    std::mt19937 prng(std::random_device{}());
    SubGraph randomized(uniform_int<int>(10,20)(prng));

    auto subs = uniform_int<int>(1,5)(prng);
    while (subs--) randomized.create_subgraph();
    subs = boost::size(randomized.children());

    int offset = 0;
    for (auto& sub : make_iterator_range(randomized.children()))
    {
        for (size_t i = offset; i < num_vertices(randomized); i += subs) 
            add_vertex(i, sub);
        ++offset;
    }

    auto random_edges = [&](SubGraph& g) {
        uniform_int<typename SubGraph::vertex_descriptor> v(0, num_vertices(g) -1);
        for (size_t i = 1; i < 4; ++i)
            add_edge(v(prng), v(prng), g);
    };

    for (auto& sub : make_iterator_range(randomized.children()))
        random_edges(sub);
    random_edges(randomized);

    // setting some graph viz attributes
    get_property(randomized, graph_name) = "G0";

    offset = 0;
    for (auto& sub : make_iterator_range(randomized.children())) {
        ++offset;
        get_property(sub, graph_name) = "cluster" + std::to_string(offset);
        get_property(sub, graph_graph_attribute)["label"]    = "G" + std::to_string(offset);
    }

    return randomized;
}

template <typename SubGraph> SubGraph create_data()
{
    enum { A,B,C,D,E,F,N }; // main edges
    SubGraph main(N);

    SubGraph& sub1 = main.create_subgraph();
    SubGraph& sub2 = main.create_subgraph();

    auto A1 = add_vertex(A, sub1);
    auto B1 = add_vertex(B, sub1);
    
    auto E2 = add_vertex(E, sub2);
    auto C2 = add_vertex(C, sub2);
    auto F2 = add_vertex(F, sub2);

    add_edge(A1, B1, sub1);
    add_edge(E2, F2, sub2);
    add_edge(C2, F2, sub2);

    add_edge(E, B, main);
    add_edge(B, C, main);
    add_edge(B, D, main);
    add_edge(F, D, main);

    // setting some graph viz attributes
    get_property(main, graph_name) = "G0";
    get_property(sub1, graph_name) = "clusterG1";
    get_property(sub2, graph_name) = "clusterG2";

    get_property(sub1, graph_graph_attribute)["label"]              = "G1";
    /*extra*/get_property(sub1, graph_vertex_attribute)["shape"]    = "Mrecord";

    get_property(sub2, graph_graph_attribute)["label"]              = "G2";
    /*extra*/get_property(sub1, graph_vertex_attribute)["color"]    = "red";
    /*extra*/get_property(sub2, graph_graph_attribute)["fillcolor"] = "lightgray";
    /*extra*/get_property(sub2, graph_graph_attribute)["style"]     = "filled";
    /*extra*/get_property(sub2, graph_vertex_attribute)["shape"]    = "circle";

    return main;
}

int main() {
    using GraphvizAttributes = 
        std::map<std::string, std::string>;

    using Graph =
        adjacency_list<vecS, vecS, directedS, 
          property<vertex_attribute_t, GraphvizAttributes>,
          property<edge_index_t, int, property<edge_attribute_t, GraphvizAttributes> >,
          property<graph_name_t, std::string,
            property<graph_graph_attribute_t,  GraphvizAttributes,
            property<graph_vertex_attribute_t, GraphvizAttributes,
            property<graph_edge_attribute_t,   GraphvizAttributes>
          > > >
        >;

#ifdef GENERATE_RANDOM_GRAPHS
    write_graphviz(std::cout, generate_random<subgraph<Graph> >());
#else
    char names[] = {"ABCDEFGH"};
    write_graphviz(std::cout, create_data<subgraph<Graph> >(), make_iterator_vertex_map(names));
#endif
}
