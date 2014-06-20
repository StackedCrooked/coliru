#include <iostream>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>

struct VertexProp
{
    VertexProp(int data_=0):data(data_){}
    int data;
    boost::adjacency_list_traits<boost::listS,boost::listS,boost::directedS>::vertex_descriptor corresponding_vertex;
};

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS,VertexProp> VecGraph;
typedef boost::adjacency_list<boost::listS,boost::listS,boost::directedS,VertexProp> ListGraph;
typedef boost::graph_traits<VecGraph>::vertex_descriptor VecVertexDesc;
typedef boost::graph_traits<ListGraph>::vertex_descriptor ListVertexDesc;


void build_graph(VecGraph& g)
{
    VecVertexDesc v1=add_vertex(VertexProp(1),g);
    VecVertexDesc v2=add_vertex(VertexProp(2),g);
    VecVertexDesc v3=add_vertex(VertexProp(3),g);
    VecVertexDesc v4=add_vertex(VertexProp(4),g);
    VecVertexDesc v5=add_vertex(VertexProp(5),g);
    
    add_edge(v1,v2,g);
    add_edge(v1,v3,g);
    add_edge(v2,v4,g);
    add_edge(v3,v5,g);  
}

int main()
{
    VecGraph g;
    ListGraph g_copy;
    build_graph(g);
    
    copy_graph(g,g_copy, boost::orig_to_copy(get(&VertexProp::corresponding_vertex,g)));
    
    BGL_FORALL_VERTICES(v,g,VecGraph)
    {
        //for every vertex with an odd 'data', multiply the data in the corresponding vertex in the copy by 2
        if(g[v].data%2==1)
            g_copy[g[v].corresponding_vertex].data*=2;
    }
    
    BGL_FORALL_VERTICES(v,g_copy,ListGraph)
        std::cout << g_copy[v].data << std::endl;
    
}
