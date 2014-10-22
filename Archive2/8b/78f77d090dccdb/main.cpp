#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>

struct VertexProperties {
    int attribute1; 
}; 
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties, boost::no_property> Graph; 

int main()
{

    Graph g(5);
    
    for (int i = 0; i < num_vertices(g); i++)
    {
        g[i].attribute1 = i; 
    } 

    boost::graph_traits<Graph>::vertex_iterator vert_i, vert_end;
    for (tie(vert_i, vert_end) = vertices(g); vert_i != vert_end; ++vert_i)
    {
        std::cout << g[*vert_i].attribute1 << std::endl;
    }
    
    BGL_FORALL_VERTICES(v,g,Graph)
    {
        std::cout << g[v].attribute1 << std::endl;
    }

}
