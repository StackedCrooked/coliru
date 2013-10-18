#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

typedef unsigned Vertex;
typedef std::pair<Vertex, Vertex> Edge;
typedef double Cost;

typedef std::map<Edge, Cost> Graph;
typedef Graph::value_type Entry;

Graph readGraph(std::istream& is)
{
    typedef boost::spirit::istream_iterator It;
    is.unsetf(std::ios::skipws);
    It f(is), l;

    size_t vertices = 0, edges = 0;
    Graph graph;

    using namespace boost::spirit::qi;
    static const rule<It, Edge(), blank_type> edge_rule = uint_ >> uint_;

    bool ok = phrase_parse(f, l, 
            uint_ >> uint_ >> eol >>
            (edge_rule >> double_) % eol >> *eol > eoi,
            blank,
            vertices, edges, graph);

    assert(ok && f==l && graph.size() == edges);
    
    return graph;
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
