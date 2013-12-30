#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <string>
#include <sstream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/iteration_macros.hpp>

using namespace boost;

struct Vertex
{
    std::string name;
    float height;
    std::string pos;
    float width;
    std::string label;
};
struct Edge
{
    std::string pos;
};


  int main(int,char*[])
  {
    // create a typedef for the Graph type
    typedef adjacency_list<vecS, vecS, bidirectionalS,Vertex,Edge,property<graph_name_t, std::string> > Graph;

     // declare a graph object
    Graph g; //CAUTION: Graph g(); is a function declaration
    dynamic_properties dp;
    
    dp.property("node_id",get(&Vertex::name,g));
    dp.property("height",get(&Vertex::height,g));
    dp.property("pos",get(&Vertex::pos,g));
    dp.property("width",get(&Vertex::width,g));
    dp.property("label",get(&Vertex::label,g));
    
    dp.property("pos",get(&Edge::pos,g));
    
    boost::ref_property_map<Graph*,std::string>
    gname(get_property(g,graph_name));
    dp.property("bb",gname);


    std::stringstream dotfile (R"(digraph G {
    graph [bb="0,0,147,324"];
    node [label="\N"];
    0    [height=0.5,
        pos="82,306",
        width=0.75];
    1    [height=0.5,
        pos="27,234",
        width=0.75];
    0 -> 1   [pos="e,38.911,250.16 70.066,289.81 62.786,280.55 53.337,268.52 45.146,258.09"];
    3    [height=0.5,
        pos="65,162",
        width=0.75];
    0 -> 3   [pos="e,67.058,180.19 79.949,287.87 77.052,263.67 71.729,219.21 68.279,190.39"];
    1 -> 3   [pos="e,56.234,179.15 35.813,216.76 40.418,208.28 46.155,197.71 51.321,188.2"];
    2    [height=0.5,
        pos="120,90",
        width=0.75];
    2 -> 0   [pos="e,85.045,287.85 116.99,107.94 110.42,144.92 94.75,233.2 86.8,277.97"];
    4    [height=0.5,
        pos="92,18",
        width=0.75];
    2 -> 4   [pos="e,98.588,35.47 113.36,72.411 110.09,64.216 106.06,54.14 102.38,44.955"];
    3 -> 2   [pos="e,108.09,106.16 76.934,145.81 84.214,136.55 93.663,124.52 101.85,114.09"];
    3 -> 4   [pos="e,88.732,36.189 68.257,143.87 72.858,119.67 81.312,75.211 86.791,46.393"];
})");

    read_graphviz(dotfile,g, dp);
    
    std::cout << "Every vertex pos:" << std::endl;
    BGL_FORALL_VERTICES(v,g,Graph)
    {
        std::cout << v << ": " << g[v].pos << std::endl;
    }
    
    std::cout << "Every edge pos:" << std::endl;
    BGL_FORALL_EDGES(e,g,Graph)
    {
        std::cout << source(e,g) << " -> " << target(e,g) << ": " << g[e].pos << std::endl;
    }

    return 0;
  }