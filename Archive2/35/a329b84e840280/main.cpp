#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/function.hpp>
#include <sstream>

using namespace boost;
typedef adjacency_list<setS/*vecS*/, vecS, directedS> Graph;
typedef std::vector<int> VertexList;
typedef function<bool(int, VertexList const&)> EdgeCallback;

std::vector<std::string> generate_file_data();
void merge_adjacencies(std::istream&& is, EdgeCallback callback);

int main() {
    Graph merged;

    for(auto& input: generate_file_data())         
    {
        merge_adjacencies(std::istringstream(input), [&](int s, VertexList const& ts) {
                for (auto t : ts)
                    if (!add_edge(s, t, merged).second)
                        std::cout << "Duplicate edge: (" << s << "," << t << ")\n";
                return true;
            });
    }

    print_graph(merged);
}

////////////////////////////////
// Generating random test data
#include <boost/graph/random.hpp>
#include <boost/random.hpp>

std::vector<std::string> generate_file_data() {
    std::vector<std::string> data;

    mt19937 prng(42);
    for (int i=0; i<5; ++i) {
        std::ostringstream oss;

        Graph g;
        generate_random_graph(g, 10, 4, prng);

        for (auto v : make_iterator_range(vertices(g))) {
            oss << v << " ";
            for (auto const& e : make_iterator_range(out_edges(v, g))) oss << target(e, g) << " ";
            oss << "\n";
        }

        data.push_back(oss.str());
    }

    return data;
}

////////////////////////////////
// Merging edges
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

void merge_adjacencies(std::istream&& is, EdgeCallback callback) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    boost::spirit::istream_iterator f(is >> std::noskipws), l;

    bool ok = qi::phrase_parse(f, l, 
            (qi::int_ >> *qi::int_) [ phx::bind(callback, qi::_1, qi::_2) ] % qi::eol,
            qi::blank);

    assert(ok);
}
