#include <boost/graph/adjacency_list.hpp>
#include <boost/range.hpp> // make_iterator_range
#include <iomanip> // for std::setw

using namespace boost;

struct MyObj{
    int idNumber;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, MyObj> Graph;

int main() {
    Graph g;

    Graph::vertex_descriptor // essentially, index into the vector or MyObj
        node1 = add_vertex(MyObj {42}, g),
        node2 = add_vertex(MyObj { 7},  g),
        node3 = add_vertex(MyObj {99}, g),
        node4 = add_vertex(MyObj {-1}, g);

    std::cout << "node1: " << node1 << "\n"; // 0
    std::cout << "node2: " << node2 << "\n"; // 1
    std::cout << "node3: " << node3 << "\n"; // 2
    std::cout << "node4: " << node4 << "\n"; // 3

    add_edge(node1, node3, g);
    add_edge(node2, node3, g);
    add_edge(node4, node1, g);

    // now we have a graph with these connections:
    for(auto const& connection: make_iterator_range(edges(g)))
    {
        Graph::vertex_descriptor sd = source(connection, g);
        Graph::vertex_descriptor td = target(connection, g);
        MyObj const& s = g[sd];
        MyObj const& t = g[td];

        std::cout << "Connection of " << sd << " (idNumber=" << std::setw(2) << s.idNumber << ") <-> "
                                      << td << " (idNumber=" << std::setw(2) << t.idNumber << ")\n";
    }

}
