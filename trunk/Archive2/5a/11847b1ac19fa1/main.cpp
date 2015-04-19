#include <algorithm>
#include <utility>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <iostream>

using namespace boost;

int main()
{
    typedef adjacency_list <vecS, vecS, undirectedS> Graph;

    Graph G;
    add_edge(0, 1, G);
    add_edge(1, 4, G);
    add_edge(4, 0, G);
    add_edge(2, 5, G);

    std::vector<int> component(num_vertices(G));
    int num = connected_components(G, &component[0]);

    std::vector<int>::size_type i;
    std::cout << "Total number of components: " << num << std::endl;
    for (i = 0; i != component.size(); ++i)
        std::cout << "Vertex " << i <<" is in component " << component[i] << std::endl;
    std::cout << std::endl;
}
