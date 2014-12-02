#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
// #include <Eigen/Core>

// use bundled properties for vertices and edges
struct VertexProperty
{
    double error;
    // Eigen::Matrix<real,dim,1> location;
};

typedef boost::adjacency_list< boost::setS, boost::setS, boost::undirectedS, VertexProperty> Graph;

typedef typename boost::graph_traits<Graph>::edge_descriptor edge_descriptor;
typedef typename boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;

namespace detail {
    template <typename Map>
        struct readable_only_pmap : Map {
            readable_only_pmap(Map map) : Map(map) { }

            // overrule the category tag
            typedef boost::readable_property_map_tag category;
        };
}

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    typedef std::map<vertex_descriptor, std::size_t> IndexMap;
    IndexMap index_map;
    boost::associative_property_map<IndexMap> index_properties(index_map);
    
    std::size_t i = 0;
    for (const vertex_descriptor& v : boost::make_iterator_range(boost::vertices(graph)))
        index_properties[v] = i++;

    using pmap_t = typename boost::property_map<Graph, double VertexProperty::*>::const_type;
    detail::readable_only_pmap<pmap_t> error_map = get(&VertexProperty::error, graph);

    boost::dynamic_properties dp;
    dp.property("error", error_map);
    boost::write_graphml(os, graph, index_properties, dp);

    return os;
}

int main()
{
  Graph g;
  auto v1 = boost::add_vertex(VertexProperty{0.1}, g);
  auto v2 = boost::add_vertex(VertexProperty{0.2}, g);
  auto v3 = boost::add_vertex(VertexProperty{0.3}, g);
  auto v4 = boost::add_vertex(VertexProperty{0.4}, g);
  auto v5 = boost::add_vertex(VertexProperty{0.5}, g);

  add_edge(v1,v2,g);
  add_edge(v5,v2,g);
  add_edge(v4,v2,g);
  add_edge(v2,v3,g);
  add_edge(v3,v4,g);
  add_edge(v4,v1,g);

  std::cout << g <<std::endl;
}
