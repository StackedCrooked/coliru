#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

using long32  = int32_t;
using float32 = float;

namespace Geoset {
#if 0
    template <typename T>
        struct Vertex3d : std::array<T, 3> {
        };
#else
    template <typename T, typename std::size_t N> class BasicVertex : public std::array<T, N> {
    public:
        typedef std::array<T, N> Base;

        BasicVertex() : Base() {}

        BasicVertex(const BasicVertex<T, N> &other) : Base(other) {}
    };

    template <typename T = float32> class Vertex3d : public BasicVertex<T, 3> {
    public:
        typedef BasicVertex<T, 3> Base;

        Vertex3d() : Base() {}

        Vertex3d(T x, T y, T z) {
            (*this)[0] = x;
            (*this)[1] = y;
            (*this)[2] = z;
        }

        Vertex3d(const Base &other) : Base(other) {}
    };
#endif

    typedef Vertex3d<float32>       VertexData;
    typedef VertexData              VertexReal3d;
    typedef std::vector<VertexData> Vertices;
}

namespace boost { namespace spirit { namespace traits {
    template <> struct is_container<Geoset::VertexData> : mpl::false_ {};
} } }

BOOST_FUSION_ADAPT_ADT(
    Geoset::VertexData,
    (float32, float32, obj[0], obj[0] = val)
    (float32, float32, obj[1], obj[1] = val)
    (float32, float32, obj[2], obj[2] = val)
)

template <typename Iterator, typename Skipper = qi::space_type>
struct grammar : qi::grammar<Iterator, Geoset::Vertices(), Skipper> {

    grammar() : grammar::base_type(start) {
        using namespace qi;
        using phx::at_c;

        integer_literal %=
                lexeme[
                    qi::int_parser<long32>()
                ]
            ;

        real_literal %=
                lexeme[
                    qi::real_parser<float32>()
                ]
            ;

        vertex_real_3d =
                lit('{')
                >> real_literal[at_c<0>(_val) = _1]
                >> lit(',')
                >> real_literal[at_c<1>(_val) = _1]
                >> lit(',')
                >> real_literal[at_c<2>(_val) = _1]
                >> lit('}')
            ;

        vertices %=
                lit("Vertices")
                >> omit [ integer_literal[_a = _1] ]
                >> lit('{')
                >> repeat(_a)[
                    vertex_real_3d >> lit(',')
                ] [_val = _1]
                >> lit('}')
            ;

        start = vertices;

        BOOST_SPIRIT_DEBUG_NODES((start)(vertices)(vertex_real_3d)(real_literal)(integer_literal))
    }
  private:
    qi::rule<Iterator, long32(),           Skipper> integer_literal;
    qi::rule<Iterator, float32(),          Skipper> real_literal;
    qi::rule<Iterator, Geoset::VertexReal3d(),     Skipper> vertex_real_3d;
    qi::rule<Iterator, Geoset::Vertices(), Skipper, qi::locals<long32> > vertices;
    qi::rule<Iterator, Geoset::Vertices(), Skipper> start;
};

int main() {
    std::string const input = "Vertices 4 { \n"
        " { 1,  2,  3  }, \n"
        " { 4,  5,  6  }, \n"
        " { 7,  8,  9  }, \n"
        " { 10, 11, 12 }, \n"
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
