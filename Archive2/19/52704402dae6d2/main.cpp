//#define BOOST_SPIRIT_DEBUG
#include <boost/optional/optional_io.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

struct Data
{
    boost::posix_time::ptime timestamp;
    std::string id;
    struct Fields {
        boost::optional<int> data1;
        boost::optional<std::string> data2;
    } fields;
};

BOOST_FUSION_ADAPT_STRUCT(Data::Fields,
        (boost::optional<int>, data1)
        (boost::optional<std::string>, data2)
    )

BOOST_FUSION_ADAPT_STRUCT(Data,
        (boost::posix_time::ptime, timestamp)
        (std::string, id)
        (Data::Fields, fields)
    )

template <typename It, typename Skipper = qi::space_type>
struct grammar : qi::grammar<It, Data(), Skipper> {
    grammar() : grammar::base_type(start) {
        using namespace qi;
        timestamp = stream;

        real_parser<double, strict_real_policies<double> > real_;

        text   = lexeme [ 
                    '"' >> *('\\' >> char_ | ~char_('"')) >> '"'
                  | "'" >> *('\\' >> char_ | ~char_("'")) >> "'"
                  | *graph 
               ];

        id     = lexeme [ *~char_(';') ];

        auto data1 = bind(&Data::Fields::data1, _val);
        auto data2 = bind(&Data::Fields::data2, _val);

        other  = lexeme [ +(graph-'=') ] >> '=' >> (real_|int_|text|lexeme[*graph]);

        fields = *(
                    ("key1" >> lit('=') >> int_) [ data1 = _1 ]
                  | ("key2" >> lit('=') >> text) [ data2 = _1 ]
                  | other
                  );

        start  = timestamp >> ';' >> id >> -(';' >> fields);

        BOOST_SPIRIT_DEBUG_NODES((timestamp)(id)(start)(text)(other)(fields))
    }
  private:
    qi::rule<It,                                 Skipper> other;
    qi::rule<It, std::string(),                  Skipper> text, id;
    qi::rule<It, boost::posix_time::ptime(),     Skipper> timestamp;
    qi::rule<It, Data::Fields(),                 Skipper> fields;
    qi::rule<It, Data(),                         Skipper> start;
};

int main() {
    using It = std::string::const_iterator;
    for (std::string const input : {
            "2015-Jan-26 00:00:00;id",
            "2015-Jan-26 14:59:24;id;key2=\"value\"",
            "2015-Jan-26 14:59:24;id;key2=\"value\" key1=42",
            "2015-Jan-26 14:59:24;id;key2=\"value\" key1=42 something=awful __=4.74e-10 blarg;{blo;bloop='whatever \\'ignor\\'ed' key2=\"new} \\\"value\\\"\"",
            "2015-Jan-26 14:59:24.123;id;key1=42 key2=\"value\" ",
            })
    {
        std::cout << "----------------------------------------\nParsing '" << input << "'\n";
        It f(input.begin()), l(input.end());
        Data parsed;
        bool ok = qi::phrase_parse(f,l,grammar<It>(),qi::space,parsed);

        if (ok) {
            std::cout << "Parsing success\n";
            std::cout << parsed.timestamp << "\t" << parsed.id << "\n";
            std::cout << "data1: " << parsed.fields.data1 << "\n";
            std::cout << "data2: " << parsed.fields.data2 << "\n";
        } else {
            std::cout << "Parsing failed\n";
        }

        if (f!=l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
