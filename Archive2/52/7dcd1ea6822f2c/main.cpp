#include <boost/graph/adjacency_list.hpp>
#include <sstream>
#include <iostream>

typedef boost::adjacency_list<boost::setS, boost::listS, boost::undirectedS, boost::property<boost::vertex_index_t, int> > Graph;
typedef typename boost::graph_traits<Graph>::vertex_iterator vertex_iterator;
typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

int main() {
    Graph g;
    std::map<int, Graph::vertex_descriptor> vertex_map;

    int linenum = 0;
    std::string line;
    while (getline(std::cin, line)) {
        std::istringstream iss(line);
        for (std::istream_iterator<int> f(iss), l; f != l; ++f) {
            int v = *f;
            if (linenum < v) {
                auto lvd = vertex_map[linenum];
                if (lvd == g.null_vertex()) lvd = vertex_map[linenum] = boost::add_vertex(linenum, g);

                auto vvd = vertex_map[v];
                if (vvd == g.null_vertex()) vvd = vertex_map[v] = boost::add_vertex(v, g);

                Graph::edge_descriptor e;
                bool inserted;
                boost::tie(e, inserted) = add_edge(lvd, vvd, g);

                if (!inserted) {
                    std::cout << "Unable to insert edge\n";
                }
            }
        }

        linenum++;
    }

    boost::property_map<Graph, boost::vertex_index_t>::const_type index_map(&g, boost::vertex_index);
    for(auto vd : g.vertex_set())
    {
        std::cout << "vertex " << boost::get(index_map, vd) << ": ";
        for(auto& e: g.out_edge_list(vd))
            std::cout << boost::get(index_map, e.get_target()) << " ";
        std::cout << "\n";
    }
}
