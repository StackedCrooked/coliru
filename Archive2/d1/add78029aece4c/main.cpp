#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

template<typename Graph>
void print_adjacent_vertex(Graph const &g)
{
    for (auto vertex = vertices(g); vertex.first != vertex.second; 
         ++vertex.first){
        std::cout << *vertex.first << " is connected with ";
        for (auto neighbour = adjacent_vertices(*vertex.first, g);
             neighbour.first != neighbour.second; ++neighbour.first){
            std::cout << *neighbour.first << " ";
        }
        std::cout<<std::endl;
    }
}

int main()
{
    using MinCutG = boost::adjacency_list<
        boost::setS, boost::vecS, boost::undirectedS>;
    
    MinCutG graph;
    std::vector<std::vector<int> > input
    {
        {1,2,3,4,7},
        {2,1,3,4},
        {3,1,2,4},
        {4,1,2,3,5},
        {5,4,6,7,8},
        {6,5,7,8},
        {7,1,5,6,8},
        {8,5,6,7}
    };
    
    for(auto const &data : input){
        auto begin = std::begin(data);
        auto end = std::end(data);
        if(begin != end){
            auto const Vertex = *begin;
            ++begin;
            while(begin != end){
                boost::add_edge(Vertex, *begin, graph);        
                ++begin;
            }
        }
    }
    print_adjacent_vertex(graph);
}
