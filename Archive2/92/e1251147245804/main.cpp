#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <sstream>

using namespace boost;
typedef adjacency_list<setS/*vecS*/, vecS, directedS> Graph;

std::vector<std::string> generate_file_data();
void merge_into(std::istream&& is, Graph& into);

int main() {
    Graph merged;

    for(auto& input: generate_file_data())         
        merge_into(std::istringstream(input), merged);

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
namespace {
    struct edge_merge_f {
        template <typename...> struct result { typedef void type; }; // for BOOST_RESULT_OF_USE_TR1:

        template<typename V, typename Edges, typename G>
            void operator()(V const& v, Edges const& edges, G& into) const {
                for (auto e : edges)
                    if (!add_edge(v, e, into).second)
                        std::cout << "Duplicate edge: (" << v << "," << e << ")\n";
            }
    };
}

#include <boost/spirit/include/qi.hpp>

void merge_into(std::istream&& is, Graph& into) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    phx::function<edge_merge_f> merge_edges;
    boost::spirit::istream_iterator f(is >> std::noskipws), l;

    bool ok = qi::phrase_parse(f, l, 
            (qi::int_ >> *qi::int_) [ merge_edges(qi::_1, qi::_2, phx::ref(into)) ] % qi::eol,
            qi::blank);

    assert(ok);
}
