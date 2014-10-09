#include <iostream>
#include <map>

struct Node
{
    std::string name;
    int id;
    
    Node (int id) : id(id) {}
};
    
bool operator<(const Node& lhs, const Node& rhs) 
{
    return lhs.id < rhs.id;
}

std::ostream& operator<<(std::ostream& os, const Node& n)
{
    return os << n.id;
}

typedef std::multimap<Node,Node> Graph;

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
    auto prev = g.begin()->first;
    os << prev << ": ";
    for (auto e : g) {
        if (e.first < prev || prev < e.first) // please implement operator!= to simplify this
            os << std::endl << (prev = e.first) << ": ";
        os << e.second << ", ";
    }
    return os << std::endl;
}

int main()
{
    Graph g;
    Node node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);
    
    g.insert (Graph::value_type(node1, node3));
    g.insert (Graph::value_type(node1, node4));
    g.insert (Graph::value_type(node1, node5));
    g.insert (Graph::value_type(node2, node6));
    g.insert (Graph::value_type(node3, node6));
    
    std::cout << g;
}
