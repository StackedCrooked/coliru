#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/random.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/filtered_graph.hpp>


using namespace boost;

boost::mt19937 rnd;
boost::uniform_int<uint64_t> dist(0,100);

struct Guid     { uint64_t part1, part2, part3; Guid() : part1(dist(rnd)), part2(dist(rnd)), part3(dist(rnd)) {} };
struct MyVertex { Guid guid; };

typedef adjacency_list<listS, vecS, directedS, MyVertex> Graph;

typedef Graph::vertex_iterator vertex_iterator;
typedef Graph::vertex_descriptor vertex_descriptor;

// A hash function for vertices.
struct vertex_hash:std::unary_function<vertex_descriptor, std::size_t> 
{
    vertex_hash(Graph const& g):g(g){}

    std::size_t operator()(vertex_descriptor const& v) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, g[v].guid.part1);
    boost::hash_combine(seed, g[v].guid.part2);
    boost::hash_combine(seed, g[v].guid.part3);
    return seed;
  }

  Graph const& g;
};


typedef boost::unordered_set<vertex_descriptor, vertex_hash> vertex_set;
typedef boost::filtered_graph<Graph,boost::keep_all,boost::is_not_in_subset<vertex_set> > FilteredGraph;

template <typename GraphType>
std::size_t filtered_num_vertices(const GraphType& g)
{
    std::size_t total=0;
    BGL_FORALL_VERTICES_T(v,g,GraphType)
    {
        ++total;
    }
    return total;
}

template <typename GraphType>
std::size_t filtered_num_edges(const GraphType& g)
{
    std::size_t total=0;
    BGL_FORALL_EDGES_T(e,g,GraphType)
    {
        ++total;
    }
    return total;
}


template <typename GraphType>
bool has_cycle(GraphType const& g);

#include <boost/chrono.hpp>
typedef chrono::high_resolution_clock hrclock;

int main() {
    rnd.seed(42);
    vertex_iterator vi,vi_end;
    Graph m_graph;

    hrclock::time_point start = hrclock::now();
    generate_random_graph(m_graph, 10000/*00*/, 5000/*00*/, rnd); // REDUCED FOR COLIRU

    std::cout << "Generated " << num_vertices(m_graph) << " vertices and " << num_edges(m_graph) << " edges in "
        << chrono::duration_cast<chrono::milliseconds>(hrclock::now() - start).count() << "ms\n"
        << "The graph has a cycle? " << std::boolalpha << has_cycle(m_graph) << "\n"
        << "starting selective removal...\n";

    vertex_hash hasher(m_graph);
    vertex_set removed(0,hasher);
    FilteredGraph fg(m_graph,boost::keep_all(),removed);
    

    start = hrclock::now();

    BGL_FORALL_VERTICES(v,m_graph,Graph)
    {
        if (m_graph[v].guid.part1%2 == 0) {
            removed.insert(v);
        } 
    }

    std::cout << "Done in " << chrono::duration_cast<chrono::milliseconds>(
            hrclock::now() - start).count() << "ms\n";

    std::cout << "After: " << filtered_num_vertices(fg) << " vertices and " << filtered_num_edges(fg) << " edges\n"; //num_vertices and num_edges don't work for filtered_graphs
    
    start = hrclock::now();
    has_cycle(fg);
    std::cout << "Done in " << chrono::duration_cast<chrono::milliseconds>(
            hrclock::now() - start).count() << "ms\n";
    
}

#include <boost/graph/depth_first_search.hpp>

struct cycle_detector : public dfs_visitor<> {
    cycle_detector(bool &has_cycle) : _has_cycle(has_cycle) {}

    template <class Edge, class Graph> void back_edge(Edge, Graph &) { _has_cycle = true; }
  protected:
    bool &_has_cycle;
};


template <typename GraphType>
bool has_cycle(GraphType const &g) {
    bool has_cycle = false;
    cycle_detector vis(has_cycle);

    boost::depth_first_search(g, 
             visitor(vis)
            );
    return has_cycle;
}
