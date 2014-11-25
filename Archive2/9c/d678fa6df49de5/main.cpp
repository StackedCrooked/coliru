//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

using long32  = int32_t;
using float32 = float;

namespace Geoset {
    template <typename T>
        struct Vertex3d {
            T a,b,c;
        };

    typedef Vertex3d<float32>       VertexData;
    typedef VertexData              VertexReal3d;
    typedef std::vector<VertexData> Vertices;
}

BOOST_FUSION_ADAPT_STRUCT(Geoset::VertexData, (float32, a)(float32, b)(float32, c))

template <typename Iterator, typename Skipper = qi::space_type>
struct grammar : qi::grammar<Iterator, Geoset::Vertices(), Skipper> {

    grammar() : grammar::base_type(start) {
        using namespace qi;

        vertex_real_3d = 
            '{' >> real_literal >> ','
                >> real_literal >> ','
                >> real_literal >> '}'
            ;

        vertices %=
                "Vertices"
                >> omit [ integer_literal[_a = _1] ]
                >> '{' >> repeat(_a)[ vertex_real_3d >> (',' | &lit('}')) ] >> '}'
            ;

        start = vertices;

        BOOST_SPIRIT_DEBUG_NODES((start)(vertices)(vertex_real_3d))
    }
  private:
    qi::int_parser<long32> integer_literal;
    qi::real_parser<float32> real_literal;
    qi::rule<Iterator, Geoset::VertexReal3d(), Skipper> vertex_real_3d;
    qi::rule<Iterator, Geoset::Vertices(), Skipper, qi::locals<long32> > vertices;
    qi::rule<Iterator, Geoset::Vertices(), Skipper> start;
};

int main() {
    std::string const input = "Vertices 4 { \n"
        " { 1,  2,  3  }, \n"
        " { 4,  5,  6  }, \n"
        " { 7,  8,  9  }, \n"
        " { 10, 11, 12 } \n"
    "}";

    auto f(begin(input)), l(end(input));
    grammar<std::string::const_iterator> g;

    Geoset::Vertices vertices;
    bool ok = qi::phrase_parse(f,l,g,qi::space,vertices);

    if (ok) {
        std::cout << "Parsed: " << vertices.size() << "\n";
        for (auto& v : vertices)
            std::cout << boost::fusion::as_vector(v) << "\n";
    } else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}