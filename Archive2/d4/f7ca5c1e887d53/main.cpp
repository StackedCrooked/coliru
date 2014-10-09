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

int main()
{
    Graph g;
    Node node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);
    
    g.insert (Graph::value_type(node1, node3));
    g.insert (Graph::value_type(node1, node4));
    g.insert (Graph::value_type(node1, node5));
    g.insert (Graph::value_type(node2, node6));
    g.insert (Graph::value_type(node3, node6));
        
    auto prev = g.begin()->first;
    std::cout << prev << ": ";
    for (auto e : g) {
        if (e.first < prev || prev < e.first) // please implement operator!= to simplify this
            std::cout << std::endl << (prev = e.first) << ": ";
        std::cout << e.second << ", ";
    }
    std::cout << std::endl;
}
