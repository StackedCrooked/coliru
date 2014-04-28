#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/boykov_kolmogorov_max_flow.hpp>

template <typename Graph>
struct graph_builder
{
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
    typedef typename boost::graph_traits<Graph>::edge_descriptor EdgeDescriptor;
    typedef typename boost::graph_traits<Graph>::edges_size_type EdgeIndex;
    
    graph_builder(Graph& g_, std::vector<float>& capacity_vec_, std::vector<EdgeDescriptor>& reverse_vec_) :
        g(g_),capacity_vec(capacity_vec_),reverse_vec(reverse_vec_),index(0){}
    
    void create_edge(VertexDescriptor src, VertexDescriptor tgt, float capacity)
    {
        bool inserted;
        EdgeDescriptor edge;
        boost::tie(edge,inserted) = add_edge(src,tgt,index++,g);
        if(inserted) // if the edge was inserted set capacity, add the reverse edge, and fill the reverse_vec
        {
            capacity_vec.push_back(capacity);
            EdgeDescriptor reverse_edge=add_edge(tgt,src,index++,g).first;
            reverse_vec.push_back(reverse_edge);
            
            capacity_vec.push_back(capacity);
            reverse_vec.push_back(edge);
            
        }
        //if the edge wasn't inserted you added an edge that is the reverse of one that already exists
        
    }
    
    Graph& g;
    std::vector<float>& capacity_vec; 
    std::vector<EdgeDescriptor>& reverse_vec;
    EdgeIndex index;
};



int main()
{
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
      boost::no_property,
      boost::property<boost::edge_index_t, std::size_t> > GraphType;

  GraphType graph;

  typedef boost::graph_traits<GraphType>::vertex_descriptor VertexDescriptor;
  typedef boost::graph_traits<GraphType>::edge_descriptor EdgeDescriptor;
  typedef boost::graph_traits<GraphType>::vertices_size_type VertexIndex;
  typedef boost::graph_traits<GraphType>::edges_size_type EdgeIndex;

  unsigned int numberOfVertices = 2*2 + 2; // a 2x2 grid
  std::vector<int> groups(numberOfVertices);

  std::vector<EdgeDescriptor> reverse_edges;

  std::vector<float> capacity;
  
  graph_builder<GraphType> builder(graph,capacity,reverse_edges);

  // Add edges between grid vertices
  builder.create_edge(0,1,1.f);

  builder.create_edge(1,2,1.f);

  builder.create_edge(2,3,1.f);

  builder.create_edge(3,0,1.f);

  int sourceId = 4;
  int sinkId = 5;
  // Add edges between all vertices and the source, as well as between all vertices and the sink
  for(size_t i = 0; i < 4; ++i)
  {
      builder.create_edge(i,sourceId,2.f);

      builder.create_edge(i,sinkId,2.f);
  }

  std::vector<float> residual_capacity(num_edges(graph), 0);

  VertexDescriptor sourceVertex = vertex(sourceId,graph);
  VertexDescriptor sinkVertex = vertex(sinkId,graph);

  // There should be 2*2 + 2 = 6 nodes
  std::cout << "Number of vertices " << num_vertices(graph) << std::endl;

  // There should be 4 + 4 + 4 = 12 edges
  std::cout << "Number of edges " << num_edges(graph) << std::endl;
  

  boost::boykov_kolmogorov_max_flow(graph,
      boost::make_iterator_property_map(&capacity[0], get(boost::edge_index, graph)),
      boost::make_iterator_property_map(&residual_capacity[0], get(boost::edge_index, graph)),
      boost::make_iterator_property_map(&reverse_edges[0], get(boost::edge_index, graph)),
      boost::make_iterator_property_map(&groups[0], get(boost::vertex_index, graph)),
      get(boost::vertex_index, graph),
      sourceVertex,
      sinkVertex);

  // Display the segmentation
  for(size_t index=0; index < groups.size(); ++index)
  {
       std::cout << "Vertex " << index << " is in group " << groups[index] << std::endl;
  }

  return EXIT_SUCCESS;
}