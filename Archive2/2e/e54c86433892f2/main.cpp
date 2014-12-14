#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace boost;
using namespace std;

int main(){
typedef int Weight;
typedef boost::property<boost::edge_weight_t, Weight> WeightProperty;
typedef boost::property<boost::vertex_name_t, std::string> NameProperty;
typedef boost::property<boost::vertex_index_t, int> IndexProperty;

typedef boost::adjacency_list < boost::listS, boost::vecS, boost::undirectedS,
    NameProperty, WeightProperty > Graph;

typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;

typedef boost::property_map < Graph, boost::vertex_index_t >::type IndexMap;
typedef boost::property_map < Graph, boost::vertex_name_t >::type NameMap;

typedef boost::iterator_property_map < Vertex*, IndexMap, Vertex, Vertex& > PredecessorMap;
typedef boost::iterator_property_map < Weight*, IndexMap, Weight, Weight& > DistanceMap;

Graph g;

typedef boost::tokenizer < boost::char_separator<char> >
    tokenizer;

std::map<std::string, Vertex> Vmap;

//Initializes a graph and variables
Vertex u;
Vertex v;
char_separator<char> sep(",");
string filename = "";
string line = "";
string v1 = "";
string v2 = "";
fstream f;
Weight weight = 0;

//Prompts the user for the file name
std::cout << "Please enter the name of the text file: ";
std::cin >> filename;

//Opens the file and adds vertices and edges to graph g
f.open(filename);
getline(f, line);                                                                   //Ignores first line "Vertices:"
getline(f, line);
tokenizer tokens(line, sep);                                                        //Tokenizes the second line "Location1, Location2 ..." 
for (tokenizer::iterator tok_iter = tokens.begin();
    tok_iter != tokens.end(); ++tok_iter) {
    Vmap[*tok_iter] = add_vertex(*tok_iter, g);                                     //For each token, add the value as a vertex in Graph g                                      
}

getline(f, line);                                                                   //Skip next line "Edges: "
while (!f.eof()){
    getline(f, line);
    line = line.substr(1, line.size() - 2);                                         //Removes parentheses by creating a substring without the first and last char
    tokenizer tokens(line, sep);                                                    //Tokenizes the string
    for (tokenizer::iterator tok_iter = tokens.begin();
        tok_iter != tokens.end(); ++tok_iter)
    {
        if (distance(tokens.begin(), tok_iter) == 0)                                //Sets first token "Location 1" to u
        {
            v1 = *tok_iter;
        }
        if (distance(tokens.begin(), tok_iter) == 1)                                //Sets second token "Location 2" to v
        {
            v2 = *tok_iter;
        }
        if (distance(tokens.begin(), tok_iter) == 2)                                //Sets third token "IntegerWeightValue" to weight
        {
            weight = stoi(*tok_iter);
        }
    }
    add_edge(Vmap[v1], Vmap[v2], weight, g);                                        //Adds weighted edge from Location 1 to Location 2 to Graph g
}

cout << "Please enter the starting node: ";
cin >> v1;
cout << "Please enter the ending node: ";
cin >> v2;
u = Vmap[v1];
v = Vmap[v2];

// Create things for Dijkstra
std::vector<Vertex> predecessors(num_vertices(g)); // To store parents
std::vector<Weight> distances(num_vertices(g)); // To store distances

IndexMap indexMap = boost::get(boost::vertex_index, g);
PredecessorMap predecessorMap(&predecessors[0], indexMap);
DistanceMap distanceMap(&distances[0], indexMap);

// Compute shortest paths from v0 to all vertices, and store the output in predecessors and distances
// boost::dijkstra_shortest_paths(g, v0, boost::predecessor_map(predecessorMap).distance_map(distanceMap));
// This is exactly the same as the above line - it is the idea of "named parameters" - you can pass the
// prdecessor map and the distance map in any order.
boost::dijkstra_shortest_paths(g, u, boost::distance_map(distanceMap).predecessor_map(predecessorMap));

std::cout << "distances and parents:" << std::endl;
NameMap nameMap = boost::get(boost::vertex_name, g);

BGL_FORALL_VERTICES(s, g, Graph)
{
    std::cout << "distance(" << nameMap[u] << ", " << nameMap[s] << ") = " << distanceMap[s] << ", ";
    std::cout << "predecessor(" << nameMap[s] << ") = " << nameMap[predecessorMap[s]] << std::endl;
}

// Extract a shortest path
std::cout << std::endl;

typedef std::vector<Graph::edge_descriptor> PathType;

PathType path;

// We want to start at the destination and work our way back to the source
for (Vertex p = predecessorMap[v]; // Start by setting 'u' to the destintaion node's predecessor
    p != u; // Keep tracking the path until we get to the source
    v = p, p = predecessorMap[v]) // Set the current vertex to the current predecessor, and the predecessor to one level up
{
    std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(p, v, g);
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

system("pause");
return 0;