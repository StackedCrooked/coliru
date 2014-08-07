#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <fstream>
#include <iostream>

#include <chrono>

using Clock = std::chrono::high_resolution_clock;

struct EdgeInputHolder : std::pair<int,int> {
    friend std::istream& operator>>(std::istream& is, EdgeInputHolder& data) {
        return is >> data.first >> data.second;
    }
};

int main()
{
    using namespace boost;
    typedef adjacency_list<listS, vecS, undirectedS, no_property, no_property, no_property, vecS> Graph;
    Graph G;

    // read edges
    auto start = Clock::now();
    std::ifstream infile;
    infile.imbue(std::locale("C"));
    infile.open("pairs.txt", std::ios::binary);
    std::istream_iterator<EdgeInputHolder> first(infile), last;

    // build graph
    G.m_edges.reserve(80*1000*1001);
    for(auto& pair : boost::make_iterator_range(first,last))
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
