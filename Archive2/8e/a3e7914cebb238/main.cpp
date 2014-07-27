#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <fstream>
#include <iostream>

#include <chrono>

using Clock = std::chrono::high_resolution_clock;

int main()
{
    using namespace boost;
    typedef adjacency_list<listS, vecS, undirectedS, no_property, no_property, no_property, vecS> Graph;
    Graph G;

    // read edges
    auto start = Clock::now();
    std::ifstream infile("pairs.txt", std::ios::binary);

    std::vector<std::pair<int, int> > as_read;

    int node1, node2;
    while (infile >> node1 >> node2)
        as_read.emplace_back(node1, node2);

    std::cout << "Reading " << as_read.size() << " done in " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count() << "ms\n";
    start = Clock::now();

    // build graph
    G.m_edges.reserve(as_read.size());
    for(auto& pair : as_read)
        add_edge(pair.first,pair.second,G);

    std::cout << "Building graph done in " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count() << "ms\n";
    start = Clock::now();

    // find connected components
    std::vector<int> component(num_vertices(G));
    int num = connected_components(G, &component[0]);

    std::cout << "Algorithm done in " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count() << "ms\n";
    start = Clock::now();

    // write output
    std::cout <<"writing file"<<std::endl;

    std::ofstream out;
    out.open("connected_component.txt");
    for (size_t i = 0; i != component.size(); ++i) {
        out << i << "\t "<< component[i] << std::endl; 
    }

    out.close();
    std::cout << "Writing done in " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count() << "ms\n";
}
