#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iterator>

struct Edge{
    typedef std::map<char, std::string> edge_map;
    edge_map edge;
    int weight;

    Edge() : edge(), weight(0) {};
    Edge(char v, std::string e, int w) : edge(), weight(w)
    {
        edge.insert(std::pair<char,std::string>(v,e));
        weight = w;
    }

    friend std::ostream& operator<<(std::ostream& os, Edge const& edge)
    {
        os << "Edge { weight:" << edge.weight << " {\n";
        for(edge_map::const_iterator it=edge.edge.begin(); it!=edge.edge.end(); ++it)
        {
            os << "{ '" << it->first << "', \"" << it->second << "\" } ";
        }
        return os << "\n}";
    }
};

int main()
{
    Edge e;
    std::cout << e;

}