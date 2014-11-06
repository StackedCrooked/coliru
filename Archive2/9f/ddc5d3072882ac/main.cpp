#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/make_shared.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/property_map/property_map.hpp>
#include <iostream>
#include <boost/function.hpp>

using namespace boost;

// Create a typedef for the Graph type
typedef adjacency_list<vecS, setS, undirectedS, property<vertex_index_t, int>, property<edge_index_t, int>> Graph;

// typedef subgraph < Graph > SubGraph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph> GraphTraits;

// Iterators
typedef graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<Graph>::edge_iterator edge_iter;
typedef property_map<Graph, vertex_index_t>::type VertexIndexMap;
typedef property_map<Graph, edge_index_t>::type EdgeIndexMap;

typedef std::map<Graph::vertex_descriptor, unsigned long> mapping_t;
typedef boost::shared_ptr<mapping_t> vertex_component_map;

typedef filtered_graph<Graph, function<bool(Graph::edge_descriptor)>, function<bool(Graph::vertex_descriptor)> > ComponentGraph;

std::vector<ComponentGraph> connected_components_subgraphs(Graph const&g)
{
    vertex_component_map mapping = boost::make_shared<mapping_t>();
    size_t num = boost::connected_components(g, boost::associative_property_map<mapping_t>(*mapping));

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

    auto v0 = add_vertex(0, g);
    auto v1 = add_vertex(1, g);
    auto v2 = add_vertex(2, g);
    auto v4 = add_vertex(4, g);
    auto v5 = add_vertex(5, g);

    add_edge(v0, v1, g);
    add_edge(v1, v4, g);
    add_edge(v4, v0, g);
    add_edge(v2, v5, g);

    for (auto const& component : connected_components_subgraphs(g))
    {
        std::cout << "component [ ";
        
        auto idx = boost::get(boost::vertex_index, component);

        for (auto e :  make_iterator_range(edges(component)))
            std::cout << idx[source(e, component)] << " -> " << idx[target(e, component)] << "; ";

        std::cout << "] has " << distance(vertices(component)) << " vertices\n";
    }
}
