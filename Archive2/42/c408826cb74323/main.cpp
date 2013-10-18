#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <map>
#include <cassert>
#include <stdexcept>

typedef unsigned Vertex;
typedef std::pair<Vertex, Vertex> Edge;
typedef double Cost;

typedef std::map<Edge, Cost> Graph;
typedef Graph::value_type Entry;

Graph readGraph(std::istream& is)
{
    size_t vertices, edges;

    if (is >> vertices >> edges)
    {
        is.ignore(1024, '\n'); // assume not overly long lines

        Graph graph;
        while (edges--)
        {
            std::string line;
            if (is && std::getline(is, line))
            {
                Vertex from, to;
                Cost cost;

                std::istringstream line_stream(line);

                if (line_stream >> from >> to >> cost)
                {
                    if (!(graph.insert({ { from, to }, cost }).second))
                        throw std::runtime_error("Duplicate edge");
                } else
                {
                    is.setstate(is.rdstate() | std::ios::badbit);
                }
            }
        }

        if (!is.bad())
            return graph;
    }

    throw std::runtime_error("Invalid input");
}

static inline Vertex      get_source     (Edge  const& e) { return e.first;  }
static inline Vertex      get_destination(Edge  const& e) { return e.second; }
static inline Edge const& get_edge       (Entry const& e) { return e.first;  }
static inline double      get_cost       (Entry const& e) { return e.second; }

static inline Vertex&     get_source     (Edge       & e) { return e.first;  }
static inline Vertex&     get_destination(Edge       & e) { return e.second; }
static inline double&     get_cost       (Entry      & e) { return e.second; }

int main()
{
    Graph const graph = readGraph(std::cin);

    for (auto& entry: graph)
    {
        Edge const& edge = ::get_edge(entry);
        Cost        cost = ::get_cost(entry);
        
        std::cout << "Edge(" << get_source(edge) << ", " << get_destination(edge) << "): cost " << cost << "\n";
    }
}
