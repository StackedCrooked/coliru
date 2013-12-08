#include <boost/graph/adjacency_list.hpp>
#include <memory>

struct Node
{
    int id;
    size_t Hash() const { return id; }
    bool operator<(const Node& other) const { return id < other.id; }
    bool operator==(const Node& other) const { return id==other.id; }
};

class SemanticGraph
{
public:
    typedef std::shared_ptr< Node > Node_ptr;
    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, Node_ptr > Graph;
    typedef boost::graph_traits< Graph >::vertex_descriptor Vertex;
    typedef boost::graph_traits< Graph >::edge_descriptor Edge;

    std::vector<Node_ptr> _nodes;
    Graph _graph;

    bool findNode(Node_ptr const& n) const { return std::find(begin(_nodes), end(_nodes), n) != end(_nodes); }

    void AddSubGraph(SemanticGraph subgraph)
    {
        typename boost::graph_traits<Graph>::vertex_iterator it, end;
        Vertex vertex;
        for(auto node : subgraph._nodes)
        {
            if(!findNode(node))
            {
                _nodes.push_back(node);
            }
            boost::tie(it, end) = boost::vertices(_graph);
            std::find_if(it, end, [&](const Vertex vertex) { return _graph[*it]->Hash() == node->Hash(); });
            if(it == end)
                vertex = boost::add_vertex(node, _graph);
            else
                vertex = boost::vertex(*it, _graph);

            boost::tie(it, end) = boost::vertices(subgraph._graph);

            std::find_if(it, end, [&](const Vertex vertex) { return subgraph._graph[*it]->Hash() == node->Hash(); });

            auto subgraph_vertex = boost::vertex(*it, subgraph._graph);
            typename boost::graph_traits<Graph>::out_edge_iterator a, z;

            // Iterate subgraph's vertex out edges
            for(boost::tie(a, z) = boost::out_edges(subgraph_vertex, subgraph._graph);
                    a != z;
                    ++a)
            {
                typename boost::graph_traits<Graph>::out_edge_iterator my_edge, edge_end;
                boost::tie(my_edge, edge_end) = boost::out_edges(vertex, _graph);
                // How can I see if the same edge as the one pointed by edge iterator a, exists in my vertex's edges?
                std::find_if(my_edge, edge_end, [&](const Edge edge) { return edge == *a; });
            }
        }
    }
};

int main()
{
    SemanticGraph g;
}
