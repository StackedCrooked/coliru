//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

namespace qi = boost::spirit::qi;

static std::string const sample = R"(
    {
        "folders" :
        [{
                "id" : 109,
                "parent_id" : 110,
                "path" : "\/1\/105\/110\/"
            },
            {
                "id" : 110,
                "parent_id" : 105,
                "path" : "\/1\/105\/"
            }
        ],

        "files" :
        [{
                "id" : 26,
                "parent_id" : 105,
                "name" : "picture.png",
                "hash" : "md5_hash",
                "path" : "\/1\/105\/"
            },
            {
                "id" : 25,
                "parent_id" : 110,
                "name" : "another_picture.jpg",
                "hash" : "md5_hash",
                "path" : "\/1\/105\/110\/"
            }
        ]
    })";

namespace qd_json { // quick and dirty JSON handling
    using text   = std::string;
    using value  = boost::make_recursive_variant<
            text,                                      // "string" (roughly!)
            double,                                    // number
            std::map<text, boost::recursive_variant_>, // object
            std::vector<boost::recursive_variant_>     // array
        >::type;
    using member = std::pair<text, value>;
    using object = std::map<text, value>;
    using array  = std::vector<value>;

    template <typename It, typename Skipper = qi::space_type>
    struct grammar : qi::grammar<It, value(), Skipper>
    {
        grammar() : grammar::base_type(value_) {
            using namespace qi;

            text_   = '"' >> raw [*('\\' >> char_ | ~char_('"'))] >> '"';
            value_  = text_ | double_ | object_ | array_;
            member_ = text_ >> ':' >> value_;
            object_ = '{' >> member_ % ',' >> '}';
            array_  = '[' >> value_  % ',' >> ']';

            BOOST_SPIRIT_DEBUG_NODES((text_)(value_)(member_)(object_)(array_))
        }
    private:
        qi::rule<It, text()>            text_;
        qi::rule<It, value(),  Skipper> value_;
        qi::rule<It, member(), Skipper> member_;
        qi::rule<It, object(), Skipper> object_;
        qi::rule<It, array(),  Skipper> array_;
    };

}

using It = std::string::const_iterator;

int main()
{
    qd_json::grammar<It> g;

    It first(sample.begin()), last(sample.end());
    qd_json::value parsed;
    bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);

    if (ok)
    {
        std::cout << "Parsed sucessfully\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (first!=last)
        std::cout << "Remaining unparsed: '" << std::string(first, last) << "'\n";

    qd_json::value clone = parsed;
    assert(parsed == clone);
}
