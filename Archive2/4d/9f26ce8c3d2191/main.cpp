

///////////////////////////////    internal Properties ////////////////////////////////////

struct NodeInfo {  int a , b , c; };   //actual bundled property  // we can chain it as well (not shown here)

struct NodeInfoPropertyTag {               
      typedef boost::vertex_property_tag kind;
      static  std::size_t const num;
 };

 std::size_t const NodeInfoPropertyTag::num = (std::size_t) &NodeInfoPropertyTag::num;

 //typedef the Vertex Property and in same way for edge property
 typedef boost::property <NodeInfoPropertyTag, NodeInfo>  NodeProperty;
 typedef boost::property <EdgeInfoPropertyTag, EdgeInfo>  EdgeProperty;
 
 //define graph 
 typedef boost::adjacency_list <vecS, vecS, undirectedS, NodeProperty, EdgeProperty, no_property, listS>   Graph_t;
 
 //initialize the graph and add vertices and properties 
 Graph_t  G;
  typedef graph_traits<Graph_t>::vertex_descriptor   vd_t;
  
  NodeInfo   ninfo1, ninfo2;   //put some values in ninfo  --> such as state, infectivity etc.
  EdgeInfo   einfo;   //initialize edgeinfo  for edge property -->such as timestamp
  
  //add vertex 
  vd_t  v = add_vertex (ninfo1, G)   //add a vertex in G with property ninfo1 
  vd_t  u = add_vertex (ninfo2, G)   //add a vertex in G with property ninfo2
  //add edge
  add_edge (u, v, einfo, G )   edge (u, v) with property einfo is added in G 
  
  
  
  //////////////////// how to access the properties ////////////////////////////
  
  
 //method 1: direct method: using Tags  (get and put)
 NodInfo   info  =  boost::get (NodeInfoPropertyTag(), G, v)   //get v's property
 put (NodeInfoPropertyTag(), G, v, info)    // (put in G, key = v, value = info )



 //method 2 : using property maps.Edge Map and Node Map  
 typedef typename boost::property_map <Graph_t, EdgeInfoPropertyTag>::type  EdgeMap;
 typedef typename boost::property_map <Graph_t, NodeInfoPropertyTag>::type  NodeMap;

 EdgeInfo  einfo = boost::get (EdgeMap, e)
 put (EdgeMap, e, einfo)   //put in the EdgeMap  key = e, value = einfo
  
  
  
  
  
  
  
  
  
  