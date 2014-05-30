#include <boost/graph/adjacency_list.hpp>
#include <iostream>

using std::cout;
using std::endl;

int main() {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph;

    Graph g;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<Graph>::edge_descriptor Edge_Desc;
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iterator;

    Vertex u, v;
    u = boost::add_vertex(g);
    v = boost::add_vertex(g);

    Edge_Desc edge;
    bool inserted = false;
    boost::tie(edge,inserted) = boost::add_edge(u,v,g);

    boost::remove_edge(edge,g);
    cout<<"\nAfter removing edge"<<endl;

    cout<<"\nRemove u"<<endl;
    boost::remove_vertex(u,g);

    cout<<"\nRemove v"<<endl;
    boost::remove_vertex(v,g);
    cout<<"\n!Everything removed"<<endl;
}