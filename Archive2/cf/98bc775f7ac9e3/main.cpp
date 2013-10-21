#include <vector>
#include <iterator>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

int main()
{
    using namespace boost;
    typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                           property<edge_weight_t, int> > graph_t;

    int v, e;
    std::cin >> v >> e;

    graph_t g(e);

    // load the data into the graph
    while(e-->0) {
        int from, to;
        std::cin >> from >> to;
        add_edge(from, to, g);
    }

    typedef graph_traits<graph_t>::edge_descriptor edge_t;
    std::vector<edge_t> mst;
    kruskal_minimum_spanning_tree(g, std::back_inserter(mst));

    for(const auto& edge : mst)
        std::cout << source(edge, g) << ' ' << target(edge,g) << '\n';
}
