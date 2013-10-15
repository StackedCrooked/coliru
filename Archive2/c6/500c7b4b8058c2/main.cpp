#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

namespace {
    using namespace boost;

    typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
    typedef graph_traits<Graph>::edge_descriptor Edge;
    typedef std::set<Edge> EdgeSet;
}

struct MyVisitor : default_dfs_visitor {
    MyVisitor(EdgeSet& tree_edges) : tree_edges(tree_edges) {}

    void tree_edge(Edge e, const Graph& g) const {
        std::cerr << "tree_edge " << e << std::endl;
        tree_edges.insert(e);
    }
    void back_edge(Edge e, const Graph& g) const {
        if (tree_edges.find(e) == tree_edges.end())
            std::cerr << "back_edge " << e << std::endl;
    }

  private: 
    EdgeSet& tree_edges;
};

int main() {
    Graph g;
    add_edge(0, 1, g);
    add_edge(0, 2, g);

    std::set<Edge> tree_edges;
    MyVisitor vis(tree_edges);

    depth_first_search(g, visitor(vis));
}
