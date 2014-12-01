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

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    typedef std::map<vertex_descriptor, std::size_t> IndexMap;
    IndexMap index_map;
    boost::associative_property_map<IndexMap> index_properties(index_map);
    
    std::size_t i = 0;
    for (const vertex_descriptor& v : boost::make_iterator_range(boost::vertices(graph)))
        index_properties[v] = i++;
    
    boost::dynamic_properties dp;
    typename boost::property_map<Graph, double VertexProperty::*>::const_type error_map = get(&VertexProperty::error, graph);
            
    dp.property("error", error_map);
    
    boost::write_graphml(os, graph,index_properties,dp);

    return os;
}

int main()
{
  Graph g;
  std::cout << g <<std::endl;
}
