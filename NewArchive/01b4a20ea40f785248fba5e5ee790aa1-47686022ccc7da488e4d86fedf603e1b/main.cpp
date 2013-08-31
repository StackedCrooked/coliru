#include <vector>
#include <iostream>
#include <fstream>

#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

struct my_visitor : boost::default_bfs_visitor 
{
    template <typename Vertex, typename Graph>
        void discover_vertex(Vertex const& u, const Graph & g) const
        {
            std::cout << "discover_vertex: " << u << "\n";
        }
};

std::vector<std::pair<int, int>> parse_input(int& min_vertex, int& max_vertex)
{
    std::vector<std::pair<int, int>> data;

    min_vertex = std::numeric_limits<int>::max();
    max_vertex = std::numeric_limits<int>::min();

    std::string line;
    while (std::getline(std::cin, line))
    {
        int a, b;
        if (std::istringstream(line) >> a >> b)
        {
            data.emplace_back(a, b);

            if (a>b) std::swap(a,b);
            min_vertex = std::min(min_vertex, a);
            max_vertex = std::max(max_vertex, b);
        }
        else throw "oops";
    }
    return data;
}

int main() 
{
    typedef boost::adjacency_list<> Graph;

    int min_vertex, max_vertex;
    auto const lines = parse_input(min_vertex, max_vertex);

    const Graph G(begin(lines), end(lines), max_vertex+1);
    print_graph(G);

    const auto source = vertex(min_vertex, G);

    breadth_first_search // visit ... needs explicit ColorMap
        (G, source, boost::visitor(my_visitor()));
}
