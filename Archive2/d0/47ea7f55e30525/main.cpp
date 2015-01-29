#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>

using namespace boost;

template <typename Graph>
size_t index_of(Graph const& g, typename Graph::vertex_descriptor const& vd)
{
    auto vs = vertices(g);
    auto lookup = std::find(vs.first, vs.second, vd);
    assert(lookup != vs.second);

    return std::distance(vs.first, lookup);
}

static mt19937 rnd(time(0));

template <typename Graph, size_t num_vertices = 200, size_t num_edges = 300>
void test_index_of()
{
    Graph g;
    generate_random_graph(g, 100, 300, rnd);

    for(auto const& v : make_iterator_range(vertices(g))) {
        assert(v == boost::vertex(index_of(g, v), g));
    }
}

int main()
{
    test_index_of<adjacency_list<vecS,  vecS,  undirectedS> >();
    test_index_of<adjacency_list<vecS,  setS,  undirectedS> >();
    test_index_of<adjacency_list<vecS,  listS, undirectedS> >();
    test_index_of<adjacency_list<setS,  vecS,  undirectedS> >();
    test_index_of<adjacency_list<setS,  setS,  undirectedS> >();
    test_index_of<adjacency_list<setS,  listS, undirectedS> >();
    test_index_of<adjacency_list<listS, vecS,  undirectedS> >();
    test_index_of<adjacency_list<listS, setS,  undirectedS> >();
    test_index_of<adjacency_list<listS, listS, undirectedS> >();
    test_index_of<adjacency_list<vecS,  vecS,  directedS>   >();
    test_index_of<adjacency_list<vecS,  setS,  directedS>   >();
    test_index_of<adjacency_list<vecS,  listS, directedS>   >();
    test_index_of<adjacency_list<setS,  vecS,  directedS>   >();
    test_index_of<adjacency_list<setS,  setS,  directedS>   >();
    test_index_of<adjacency_list<setS,  listS, directedS>   >();
    test_index_of<adjacency_list<listS, vecS,  directedS>   >();
    test_index_of<adjacency_list<listS, setS,  directedS>   >();
    test_index_of<adjacency_list<listS, listS, directedS>   >();
}
