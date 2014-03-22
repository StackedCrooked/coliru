#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/graph/edge_list.hpp>
#include <fstream>

typedef std::pair<int,int> Edge;
typedef std::vector<Edge> EdgeList;
typedef boost::edge_list<EdgeList::iterator> Graph;

namespace qi = boost::spirit::qi;

int main()
{
    std::ifstream ifs("input.txt");
    ifs >> std::noskipws;

    boost::spirit::istream_iterator f(ifs), l;

    std::vector<Edge> edges;
    bool parse_ok = qi::phrase_parse(f, l, (qi::int_ >> qi::int_) % qi::eol, qi::blank, edges);

    Graph g(edges.begin(), edges.end());

    if (parse_ok)
    {
        std::cout << "Graph parsed with " << num_edges(g) << " edges\n";
    } else
        std::cout << "Parse error\n";

    if (f!=l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
