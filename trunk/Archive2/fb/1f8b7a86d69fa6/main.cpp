#include <iostream>
#include <map>

struct Node
{
    explicit Node(int i) : _i(i) {}
    int _i;
    
    bool operator<(const Node& rhs) const 
    {
        return _i < rhs._i;
    }
};

std::ostream& operator<<(std::ostream& os, const Node& n)
{
    os << n._i;
    return os;
}

typedef std::multimap<Node,Node> Graph;

int main()
{
    Graph g;
    Node node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node8(8), node9(9);
    
    g.insert (Graph::value_type(node1, node3));
    g.insert (Graph::value_type(node1, node4));
    g.insert (Graph::value_type(node1, node5));
    g.insert (Graph::value_type(node2, node6));
    g.insert (Graph::value_type(node3, node6));
    g.insert (Graph::value_type(node5, node7));
    g.insert (Graph::value_type(node5, node8));
    g.insert (Graph::value_type(node5, node9));
    g.insert (Graph::value_type(node9, node5));
    
    Graph::const_iterator it = g.begin();
    while (it != g.end())
    {
        std::pair<Graph::const_iterator, Graph::const_iterator> range = g.equal_range(it->first);
        
        std::cout << it->first << ": ";        
        for (; range.first != range.second; ++range.first)
        {
            std::cout << range.first->second << ", ";
        }
        std::cout << std::endl;
        
        it = range.second;
    }
}
