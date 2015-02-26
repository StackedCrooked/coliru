#include <boost/graph/adjacency_list.hpp>

namespace khut {
    struct diagonal { };

    struct MyVertexProperties {
        diagonal const* diag_ptr;
    };

    struct MyEdgeProperties {
        float dominance;
    };
}

typedef boost::adjacency_list<
      boost::listS, 
      boost::vecS,
      boost::bidirectionalS,
      khut::MyVertexProperties,
      khut::MyEdgeProperties
    > diagonal_dominance_graph;

#include <iostream>


int main() {
    using namespace boost;

    diagonal_dominance_graph g;

    khut::diagonal d1, d2;
    {
        auto v1 = add_vertex(khut::MyVertexProperties { &d1 }, g);
        auto v2 = add_vertex(khut::MyVertexProperties { &d2 }, g);

        /*auto e1 = */add_edge(v1, v2, khut::MyEdgeProperties { 42.31415926 }, g);
    }

    for(diagonal_dominance_graph::vertex_descriptor vd : make_iterator_range(vertices(g)))
        std::cout << "Is diagonal d1? " << std::boolalpha << (&d1 == g[vd].diag_ptr) << "\n";
    for(diagonal_dominance_graph::edge_descriptor ed : make_iterator_range(edges(g)))
        std::cout << "Edge dominance: " << g[ed].dominance << "\n";
}

