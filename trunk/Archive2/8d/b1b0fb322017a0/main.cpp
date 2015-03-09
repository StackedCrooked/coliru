#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <map>

namespace qi = boost::spirit::qi;

std::string const sample = R"({"ts":1827908701,"updates":[[4,30623409,17,81282347579,1425823449632," ... ","tfs"],[80,1,0],[7,81282347579,30652308]]})";

namespace qd_json { // quick and dirty JSON handling
    struct null {};
    using text   = std::string;
    using value  = boost::make_recursive_variant<
            null,
            text,                                      // "string" (roughly!)
            double,                                    // number
            std::map<text, boost::recursive_variant_>, // object
            std::vector<boost::recursive_variant_>,    // array
            bool
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
            null_   = "null" >> attr(null{});
            bool_   = "true" >> attr(true) | "false" >> attr(false);
            value_  = null_ | bool_ | text_ | double_ | object_ | array_;
            member_ = text_ >> ':' >> value_;
            object_ = '{' >> -(member_ % ',') >> '}';
            array_  = '[' >> -(value_  % ',') >> ']';

            ////////////////////////////////////////
            // Bonus: properly decoding the string:
            text_   = lexeme [ '"' >> *ch_ >> '"' ];

            ch_ = +(
                    ~char_("\"\\")) [ _val += _1 ] |
                       qi::lit("\x5C") >> (               // \ (reverse solidus)
                       qi::lit("\x22") [ _val += '"'  ] | // "    quotation mark  U+0022
                       qi::lit("\x5C") [ _val += '\\' ] | // \    reverse solidus U+005C
                       qi::lit("\x2F") [ _val += '/'  ] | // /    solidus         U+002F
                       qi::lit("\x62") [ _val += '\b' ] | // b    backspace       U+0008
                       qi::lit("\x66") [ _val += '\f' ] | // f    form feed       U+000C
                       qi::lit("\x6E") [ _val += '\n' ] | // n    line feed       U+000A
                       qi::lit("\x72") [ _val += '\r' ] | // r    carriage return U+000D
                       qi::lit("\x74") [ _val += '\t' ] | // t    tab             U+0009
                       qi::lit("\x75")                    // uXXXX                U+XXXX
                            >> _4HEXDIG [ append_utf8(qi::_val, qi::_1) ]
                    );

            BOOST_SPIRIT_DEBUG_NODES((text_)(value_)(member_)(object_)(array_)(null_)(bool_))
        }
    private:
        qi::rule<It, text()>            text_, ch_;
        qi::rule<It, null()>            null_;
        qi::rule<It, bool()>            bool_;
        qi::rule<It, value(),  Skipper> value_;
        qi::rule<It, member(), Skipper> member_;
        qi::rule<It, object(), Skipper> object_;
        qi::rule<It, array(),  Skipper> array_;

        struct append_utf8_f {
            template <typename...> struct result { typedef void type; };
            template <typename String, typename Codepoint>
            void operator()(String& to, Codepoint codepoint) const {
                auto out = std::back_inserter(to);
                boost::utf8_output_iterator<decltype(out)> convert(out);
                *convert++ = codepoint;
            }
        };
        boost::phoenix::function<append_utf8_f> append_utf8;
        qi::uint_parser<uint32_t, 16, 4, 4> _4HEXDIG;
    };

    template <typename Range, typename It = typename boost::range_iterator<Range const>::type>
    value parse(Range const& input) {
        grammar<It> g;

        It first(boost::begin(input)), last(boost::end(input));
        value parsed;
        bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);

        if (ok && (first == last))
            return parsed;

        throw std::runtime_error("Remaining unparsed: '" + std::string(first, last) + "'");
    }

    namespace accessors {
        static double          dbl_(qd_json::value const&v) { return boost::get<double>(v); }
        static int             int_(qd_json::value const&v) { return boost::get<double>(v); }
        static std::string     txt_(qd_json::value const&v) { return boost::get<qd_json::text>(v); }
        static qd_json::array  arr_(qd_json::value const&v) { return boost::get<qd_json::array>(v); }
        static qd_json::object obj_(qd_json::value const&v) { return boost::get<qd_json::object>(v); }
    }
}

using It = std::string::const_iterator;

int main()
{
    using namespace qd_json::accessors;

    auto root = obj_(qd_json::parse(sample));

    for(auto& updates : arr_(root["updates"]))
        for(auto& first : arr_(updates))
        {
            std::cout << int_(first) << "\n";
            return 0;
        }
}
