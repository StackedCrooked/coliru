#include <boost/fusion/adapted/struct.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
//#include <boost/graph/graph_traits.hpp>
//#include <boost/graph/prim_minimum_spanning_tree.hpp>
//#include <boost/graph/properties.hpp>
//#include <boost/property_map/property_map.hpp>
//#include <boost/tokenizer.hpp>

typedef int Weight;
typedef boost::property<boost::edge_weight_t, Weight>      WeightProperty;
typedef boost::property<boost::vertex_name_t, std::string> NameProperty;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, NameProperty, WeightProperty> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
typedef boost::property_map<Graph, boost::vertex_name_t>::type NameMap;

typedef boost::iterator_property_map<Vertex*, IndexMap, Vertex, Vertex&> PredecessorMap;
typedef boost::iterator_property_map<int*, IndexMap, int, int&> DistanceMap;

typedef std::map<std::string, Vertex> VertexMap;

#include <iostream>
#include <fstream>

BOOST_FUSION_DEFINE_STRUCT((parsing), edgedef, (std::string,s)(std::string,t)(Weight,weight))

int main() {
    Graph g;
    VertexMap Vmap;
    {
        //Prompts the user for the file name
        std::string filename = "";
        std::cout << "Please enter the name of the text file: ";
        std::cin >> filename;

        //Opens the file and adds vertices and edges to graph g
        using namespace boost::spirit::qi;
        std::fstream f(filename);
        f >> std::noskipws;

        std::vector<std::string> names;
        std::vector<parsing::edgedef> defs;
        if (f >> phrase_match(
                    "Vertices:" >> eol >> +alnum % ',' >> eol >> 
                    "Edges:" >> eol >>
                    ('(' >> +alnum >> ',' >> +alnum >> ',' >> int_ >> ')') % eol,
                    blank, names, defs))
        {
            for(auto& c : names)
                Vmap[c] = add_vertex(c, g);         // For each token, add the value as a vertex in Graph g

            for(auto& def : defs)
            {
                std::cout << def.s << " -> " << def.t << " (" << def.weight << ")\n";
                add_edge(Vmap[def.s], Vmap[def.t], def.weight, g);                          // Adds weighted edge from Location 1 to Location 2 to Graph g
            }
        }
    }

    //Prompts user for starting and ending node
    std::string v1 = "";
    std::string v2 = "";

    std::cout << "Please enter the starting node: ";
    std::cin >> v1;
    std::cout << "Please enter the ending node: ";
    std::cin >> v2;

    std::cout << "From " << v1 << " to " << v2 << "; num_vertices: " << num_vertices(g) << "\n";

    auto const srce_vertex = Vmap[v1];
    auto dest_vertex = Vmap[v2];

    // Create things for Dijkstra
    std::vector<Vertex> predecessors(num_vertices(g)); // To store parents
    std::vector<Weight> distances(num_vertices(g));    // To store distances

    IndexMap indexMap = boost::get(boost::vertex_index, g);
    PredecessorMap predecessorMap(&predecessors[0], indexMap);
    DistanceMap distanceMap(&distances[0], indexMap);

    // Compute shortest paths from v0 to all vertices, and store the output in predecessors and distances
    // boost::dijkstra_shortest_paths(g, v0, boost::predecessor_map(predecessorMap).distance_map(distanceMap));
    // This is exactly the same as the above line - it is the idea of "named parameters" - you can pass the
    // prdecessor map and the distance map in any order.
    boost::dijkstra_shortest_paths(g, srce_vertex, boost::distance_map(distanceMap).predecessor_map(predecessorMap));

    std::cout << "distances and parents:" << std::endl;
    NameMap nameMap = boost::get(boost::vertex_name, g);

    BGL_FORALL_VERTICES(curr_vertex, g, Graph)
    {
        std::cout << "distance("    << nameMap[srce_vertex] << ", "   << nameMap[curr_vertex]                 << ") = " << distanceMap[curr_vertex] << ", ";
        std::cout << "predecessor(" << nameMap[curr_vertex] << ") = " << nameMap[predecessorMap[curr_vertex]] << std::endl;
    }

    // Extract a shortest path
    std::cout << std::endl;

    typedef std::vector<Graph::edge_descriptor> PathType;

    PathType path;

                                                                                  // We want to start at the destination and work our way back to the source
    for (Vertex curr_vertex = predecessorMap[dest_vertex];                        // Start by setting 'srce_vertex' to the destination node's predecessor
            curr_vertex != srce_vertex;                                           // Keep tracking the path until we get to the source
            dest_vertex = curr_vertex, curr_vertex = predecessorMap[dest_vertex]) // Set the current vertex to the current predecessor, and the predecessor to one level up
    {
        std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(curr_vertex, dest_vertex, g);
        Graph::edge_descriptor edge = edgePair.first;

        path.push_back(edge);
    }

    // Write shortest path
    std::cout << "Shortest path from " << v1 << " to " << v2 << std::endl;
    float totalDistance = 0;
    for (PathType::reverse_iterator pathIterator = path.rbegin(); pathIterator != path.rend(); ++pathIterator)
    {
        std::cout << nameMap[boost::source(*pathIterator, g)] << " -> " << nameMap[boost::target(*pathIterator, g)]
                  << " = " << boost::get(boost::edge_weight, g, *pathIterator) << std::endl;

    }

    std::cout << std::endl;

    std::cout << "Distance: " << distanceMap[Vmap[v2]] << std::endl;
}
