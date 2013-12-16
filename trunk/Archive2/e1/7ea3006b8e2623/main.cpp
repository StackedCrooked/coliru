#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/property_maps/constant_property_map.hpp>


struct Node
{
    int level;
};

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::bidirectionalS,Node> NodeGraph;
typedef NodeGraph::vertex_descriptor VertexDesc;
typedef NodeGraph::edge_descriptor EdgeDesc;


int main()
{
    NodeGraph nodes;
    
    //Building and initializing the graph
    VertexDesc n118=add_vertex(nodes);
    VertexDesc n122=add_vertex(nodes);
    VertexDesc n120=add_vertex(nodes);
    VertexDesc n121=add_vertex(nodes);
    VertexDesc n123=add_vertex(nodes);
    VertexDesc n125=add_vertex(nodes);
    VertexDesc n124=add_vertex(nodes);
    
    add_edge(n118,n122,nodes);
    add_edge(n118,n120,nodes);
    add_edge(n122,n120,nodes);
    add_edge(n122,n121,nodes);
    add_edge(n121,n125,nodes);
    add_edge(n121,n123,nodes);
    add_edge(n123,n125,nodes);
    add_edge(n125,n124,nodes);
    
    BGL_FORALL_VERTICES(v,nodes,NodeGraph)
    {
        nodes[v].level=0;
    }
    //graph built

    dijkstra_shortest_paths(nodes,n118,boost::weight_map(boost::make_constant_property<EdgeDesc>(1)).distance_map(get(&Node::level,nodes)));    
    
    BGL_FORALL_VERTICES(v,nodes,NodeGraph)
    {
        int max_p_lvl = nodes[v].level - 1;
        NodeGraph::inv_adjacency_iterator neighbourIt, neighbourEnd;
        boost::tie(neighbourIt, neighbourEnd) = inv_adjacent_vertices( v, nodes );
        for(NodeGraph::inv_adjacency_iterator adj_iter = neighbourIt; adj_iter != neighbourEnd; ++adj_iter) {
            max_p_lvl = std::max(max_p_lvl, nodes[*adj_iter].level);
        }
        nodes[v].level = max_p_lvl + 1;
    }
    
    BGL_FORALL_VERTICES(v,nodes,NodeGraph)
    {
        std::cout << nodes[v].level << std::endl;
    }
    
}
