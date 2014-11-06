#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/make_shared.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <boost/function.hpp>

using namespace boost;

// Create a typedef for the Graph type
typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int>, property<edge_index_t, int>> Graph;

// typedef subgraph < Graph > SubGraph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph> GraphTraits;

// Iterators
typedef graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<Graph>::edge_iterator edge_iter;
typedef property_map<Graph, vertex_index_t>::type VertexIndexMap;
typedef property_map<Graph, edge_index_t>::type EdgeIndexMap;

typedef boost::shared_ptr<std::vector<unsigned long>> vertex_component_map;

typedef filtered_graph<Graph, function<bool(Graph::edge_descriptor)>, function<bool(Graph::vertex_descriptor)> > ComponentGraph;

std::vector<ComponentGraph> connected_components_subgraphs(Graph const&g)
{
    vertex_component_map mapping = boost::make_shared<std::vector<unsigned long>>(num_vertices(g));
    size_t num = boost::connected_components(g, mapping->data());

    std::vector<ComponentGraph> component_graphs;

    for (size_t i = 0; i < num; i++)
        component_graphs.push_back(ComponentGraph(g,
            [mapping,i,&g](Graph::edge_descriptor e) {
                return mapping->at(source(e,g))==i
                    || mapping->at(target(e,g))==i;
            }, 
            [mapping,i](Graph::vertex_descriptor v) {
                return mapping->at(v)==i;
            }));

    return component_graphs;
}

int main()
{
    Graph g;

    add_edge(0, 1, g);
    add_edge(1, 4, g);
    add_edge(4, 0, g);
    add_edge(2, 5, g);

    for (auto const& component : connected_components_subgraphs(g))
    {
        std::cout << "component [ ";
        for (auto e :  make_iterator_range(edges(component)))
            std::cout << source(e, component) << " -> " << target(e, component) << "; ";
        std::cout << "]\n";
    }
}
