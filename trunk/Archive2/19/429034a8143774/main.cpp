#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace boost;

int main()
{
    std::ifstream infile("input.txt", std::ios::in);

    long int num_nodes;
    long int num_edges;
    {
        std::string line;
        std::getline(infile, line);
        std::istringstream instream(line);
        instream >> num_nodes >> num_edges;
    }

    std::cout << "READING graph into C++ program from file" << std::endl;
    std::cout << "Found " << num_nodes << " nodes, and " << num_edges << " edges" << std::endl;

    typedef std::pair < int, int > Edge;
    struct Edge_Cost
    {
        double weight;
    };

    struct vertex_data
    {
        boost::graph_traits<
        boost::compressed_sparse_row_graph< boost::directedS > >::vertex_descriptor p;
        double d;
    };

    typedef boost::compressed_sparse_row_graph<
    boost::directedS,
          vertex_data,
          Edge_Cost
          > graph_t;

    typedef boost::graph_traits < graph_t >::vertex_descriptor
    vertex_descriptor;

    std::vector<Edge> edge_list;
    std::vector<Edge_Cost> edge_weight_list;

    for(int i=0; i<num_edges; ++i)
    {
        float wt;
        int n1,n2;

        //get a line from the file, vertex n1 is linked to vertex n2 by weight
        //wt, but first vertex in file is 1 not 0, so -1

        std::string line;
        std::getline(infile, line);
        std::istringstream instream(line);
        instream >> n1 >> n2 >> wt;

        edge_list.emplace_back(n1-1, n2-1);
        edge_weight_list.push_back(Edge_Cost{wt});

        std::cout << "Read: " << n1 << " " << n2 << " " << wt << "\n";
    }

    graph_t Graph(boost::edges_are_unsorted,edge_list.begin(),edge_list.end(),&edge_weight_list[0],edge_list.size());

    vertex_descriptor s = vertex(1,Graph);
    std::vector<vertex_descriptor> p(11);//path
    std::vector<double> d(11);    //distance

    //get one set of distances
    boost::dijkstra_shortest_paths_no_color_map
        (Graph,s,
         boost::predecessor_map(&p[0]).
         distance_map(&d[0]).
         weight_map(boost::get(&Edge_Cost::weight, Graph))
        );
}
