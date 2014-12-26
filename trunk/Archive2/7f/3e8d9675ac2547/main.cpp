#include <boost/graph/adjacency_list.hpp>
#include <sstream>
#include <iostream>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef typename boost::graph_traits<Graph>::vertex_iterator vertex_iterator;
typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

int main() {
    Graph g;

    int linenum = 0;
    std::string line;
    while (getline(std::cin, line)) {
        std::istringstream iss(line);
        for (std::istream_iterator<int> f(iss), l; f != l; ++f) {
            int v = *f;
            if (linenum < v) {
                Graph::edge_descriptor e;
                bool inserted;
                boost::tie(e, inserted) = add_edge(linenum, v, g);

                if (!inserted) {
                    std::cout << "Unable to insert edge\n";
                }
            }
        }

        linenum++;
    }

    for(auto vd : g.vertex_set())
        if (!g.out_edge_list(vd).empty())
            std::cout << "vertex " << vd << " has outgoing edges\n";
}
