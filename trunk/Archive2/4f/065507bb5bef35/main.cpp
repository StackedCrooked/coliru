#include <vector>
#include <stack>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

int main()
{
    // [from_node,to_node,distance] 
    std::vector<std::vector<double>> from_to_and_distance_matrix =
        {{0,1,0.13}, {1,2,0.1}, {1,3,0.2},
         {2,3,0.1}, {1,3,0.3}, {2,4,0.1}};

    using namespace boost;
    typedef adjacency_list<listS, vecS, directedS, no_property,
                           property<edge_weight_t, double>> graph_t;
    graph_t g;
    for(auto& v: from_to_and_distance_matrix)
        get(edge_weight, g)[add_edge(v[0], v[1], g).first] = v[2];

    std::cout << "Loaded graph with " << num_vertices(g) << " nodes\n";

    // call Dijkstra
    typedef graph_traits<graph_t>::vertex_descriptor vertex_descriptor;
    std::vector<vertex_descriptor> p(num_vertices(g)); // predecessors
    std::vector<double> d(num_vertices(g)); // distances
    vertex_descriptor start = vertex(0, g); // starting point
    vertex_descriptor goal = vertex(4, g); // end point

    dijkstra_shortest_paths(g, start, predecessor_map(&p[0]).distance_map(&d[0]));

    // print the results
    std::stack<vertex_descriptor> path;
    for(vertex_descriptor v = goal; v != start; v = p[v])
        path.push(v);
    path.push(start);

    std::cout << "Total length of the shortest path: " << d[4] << '\n'
              << "The number of steps: " << path.size() << '\n';
    while(!path.empty()) {
        int pos = path.top();
        std::cout << '[' << pos << "] ";
        path.pop();
    }
    std::cout << '\n';
}