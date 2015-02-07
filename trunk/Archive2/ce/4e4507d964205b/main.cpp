#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/random.hpp>
#include <boost/container/stable_vector.hpp>

#define STABLE_IT

using namespace boost;

boost::mt19937 rnd;
boost::uniform_int<uint64_t> dist(0,100);

struct Guid     { uint64_t part1 = dist(rnd), part2 = dist(rnd), part3 = dist(rnd); };
struct MyVertex { Guid guid; };

namespace boost {
    struct stableVecS;

    template <typename V>
        struct container_gen<stableVecS, V> {
            typedef boost::container::stable_vector<V> type;
        };
}

#ifdef STABLE_IT
    using Graph = adjacency_list<listS, listS, directedS, MyVertex>;
#else
    using Graph = adjacency_list<listS, vecS, directedS, MyVertex>;
#endif

using vertex_iterator = Graph::vertex_iterator;

bool has_cycle(Graph const& g);

#include <boost/chrono.hpp>

int main() {
    rnd.seed(42);
    vertex_iterator vi,vi_end;
    Graph m_graph;

    auto start = chrono::high_resolution_clock::now();
    generate_random_graph(m_graph, 1000/*00*/, 50/*00*/, rnd); // reduced for Coliru

    std::cout << "Generated " << num_vertices(m_graph) << " vertices and " << num_edges(m_graph) << " edges in "
        << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << "ms\n"
        << "The graph has a cycle? " << std::boolalpha << has_cycle(m_graph) << "\n"
        << "starting selective removal...\n";

    for (boost::tie(vi, vi_end) = boost::vertices(m_graph); vi!=vi_end; ++vi)
        if (m_graph[*vi].guid.part1 == 0)
            clear_vertex(*vi, m_graph);

    start = chrono::high_resolution_clock::now();

    for (boost::tie(vi, vi_end) = boost::vertices(m_graph); vi!=vi_end;)
    {
        if (m_graph[*vi].guid.part1 == 0) {
            //std::cout << "." << std::flush;
#if defined(STABLE_IT)
            auto toremove = vi++;
            boost::remove_vertex(*toremove,m_graph);
#else
            boost::remove_vertex(*vi,m_graph);
            boost::tie(vi, vi_end) = boost::vertices(m_graph);
#endif
        } else 
            ++vi;
    }

    std::cout << "Done in " << chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start).count() << "ms\n";

    std::cout << "After: " << num_vertices(m_graph) << " vertices and " << num_edges(m_graph) << " edges\n";
}

#include <boost/graph/depth_first_search.hpp>

struct cycle_detector : public dfs_visitor<> {
    cycle_detector(bool &has_cycle) : _has_cycle(has_cycle) {}

    template <class Edge, class Graph> void back_edge(Edge, Graph &) { _has_cycle = true; }
  protected:
    bool &_has_cycle;
};

bool has_cycle(Graph const &g) {
    bool has_cycle = false;
    cycle_detector vis(has_cycle);


    std::map<Graph::vertex_descriptor, size_t> index;
    size_t gen = 0;
    for(auto vd : make_iterator_range(vertices(g)))
        index.emplace(vd, gen++);

    boost::depth_first_search(g, 
             visitor(vis)
            .vertex_index_map(make_assoc_property_map(index))
            );
    return has_cycle;
}
