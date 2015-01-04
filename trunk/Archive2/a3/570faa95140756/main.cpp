#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


class GraphNode
{
public:
    GraphNode(){}
private:
    std::vector< std::pair<int, GraphNode*> > m_brothers;
};
class Graph
{
public:
    Graph() {}
private:
    std::vector<GraphNode*> m_nodes;
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
