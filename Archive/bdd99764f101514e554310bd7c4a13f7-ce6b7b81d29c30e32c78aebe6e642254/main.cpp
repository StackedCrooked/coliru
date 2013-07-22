#include <iostream>
#include <iterator>
#include <boost/graph/adjacency_list.hpp>

using V = unsigned;
using E = std::pair<V, V>;

// store neighbors in a std::list, vertices in a std::list
using G = boost::adjacency_list<boost::vecS, boost::vecS>;

void print_graph(G const& g)
{
    auto vs = boost::vertices(g);
    for (auto vit = vs.first; vit != vs.second; ++vit) {
        auto neighbors = boost::adjacent_vertices(*vit, g);
        for (auto nit = neighbors.first; nit != neighbors.second; ++nit)
            std::cout << "{" << *vit << "," << *nit << "}" << ", ";
    }
    std::cout << "\n";
}

void collapse_vertices(V b, V a, G& g)
{
    auto be = boost::adjacent_vertices(b, g);
    for (auto beit = be.first; beit != be.second; ++beit)
        add_edge(a, *beit, g);
    remove_vertex(b, g);
}

int main()
{
    // named vertices
    auto const A = V { 1 };
    auto const B = V { 2 };
   
    // construct the graph
    auto e = std::vector<E> { { A, 3 }, { B, 4 } };
    auto g = G { std::begin(e), std::end(e), 4 };

    print_graph(g);
    collapse_vertices(B, A, g);    
    print_graph(g);
}