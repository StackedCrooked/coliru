    #include <iostream>
    
    #include <boost/graph/grid_graph.hpp>
    #include <boost/graph/boykov_kolmogorov_max_flow.hpp>
    #include <boost/graph/iteration_macros.hpp>
    #include <boost/version.hpp>
    
    int main()
    {
    
        const unsigned int D = 2;
        typedef boost::grid_graph<D> Graph;
        typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
        typedef boost::graph_traits<Graph>::edge_descriptor EdgeDescriptor;//ADDED
        typedef boost::graph_traits<Graph>::vertices_size_type VertexIndex;
        typedef boost::graph_traits<Graph>::edges_size_type EdgeIndex;
        
    
        boost::array<std::size_t, D> lengths = { { 3, 3 } };
        Graph graph(lengths, false);
    
        float pixel_intensity[]={10.0f,15.0f,25.0f,
                                5.0f,220.0f,240.0f,
                                12.0f,15.0,230.0f};
        std::vector<int> groups(num_vertices(graph));
        std::vector<float> residual_capacity(num_edges(graph)); //this needs to be initialized to 0
        std::vector<float> capacity(num_edges(graph)); //this is initialized below, I believe the capacities of an edge and its reverse should be equal, but I'm not sure
    	std::vector<EdgeDescriptor> reverse_edges(num_edges(graph));//ADDED
    
        BGL_FORALL_EDGES(e,graph,Graph)
        {
            VertexDescriptor src = source(e,graph);
            VertexDescriptor tgt = target(e,graph);
            VertexIndex source_idx = get(boost::vertex_index,graph,src);
            VertexIndex target_idx = get(boost::vertex_index,graph,tgt);
            EdgeIndex edge_idx = get(boost::edge_index,graph,e);
    
            capacity[edge_idx] = 255.0f - fabs(pixel_intensity[source_idx]-pixel_intensity[target_idx]); //you should change this to your "gradiant or intensity or something"
        
    		reverse_edges[edge_idx]=edge(tgt,src,graph).first;//ADDED
    	}
    
        VertexDescriptor s=vertex(0,graph), t=vertex(8,graph); 
    
        //in the boykov_kolmogorov_max_flow header it says that you should use this overload with an explicit color property map parameter if you are interested in finding the minimum cut
        boykov_kolmogorov_max_flow(graph,
            make_iterator_property_map(&capacity[0], get(boost::edge_index, graph)), 
            make_iterator_property_map(&residual_capacity[0], get(boost::edge_index, graph)),
    		make_iterator_property_map(&reverse_edges[0], get(boost::edge_index, graph)), //CHANGED
    		make_iterator_property_map(&groups[0], get(boost::vertex_index, graph)),
            get(boost::vertex_index, graph),
            s,
            t
        );
    
    
       for(size_t index=0; index < groups.size(); ++index)
       {
            if((index%lengths[0]==0)&&index)
                std::cout << std::endl;
            std::cout << groups[index] << " ";
       }
    
       return 0;
    }