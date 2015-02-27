#include <boost/graph/adjacency_list.hpp>

namespace khut { struct diagonal {}; }

namespace boost { 
    enum vertex_diagonal_t{vertex_diagonal = 999};
    BOOST_INSTALL_PROPERTY(vertex, diagonal);
}
namespace boost { 
    enum edge_dominance_t{edge_dominance = 998};
    BOOST_INSTALL_PROPERTY(edge, dominance);
}

typedef boost::adjacency_list<
      boost::listS, 
      boost::vecS,
      boost::bidirectionalS,
      boost::property<boost::vertex_diagonal_t, const khut::diagonal*>,
      boost::property<boost::edge_dominance_t,  float>
    > diagonal_dominance_graph;
typedef boost::property_map<diagonal_dominance_graph, boost::vertex_diagonal_t>::type diagonal_map_type;
typedef boost::property_map<diagonal_dominance_graph, boost::edge_dominance_t>::type  dominance_map_type;

int main() {
    diagonal_dominance_graph graph;
    
    using storage_type = std::vector<int>;
    storage_type repo_begining(10);

    for(storage_type::const_iterator i = repo_begining.begin(); i != repo_begining.end(); ++i) {
        diagonal_dominance_graph::vertex_descriptor dia_vertex = boost::add_vertex(graph);

        diagonal_map_type p = get(boost::vertex_diagonal, graph);

        khut::diagonal* v = nullptr;
        boost::put(p, dia_vertex, v);
    }
}
