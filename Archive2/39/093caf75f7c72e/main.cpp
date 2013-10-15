#define BOOST_SPIRIT_UNICODE
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // unicode, please

using u32_string = std::basic_string<uint32_t>;

struct Value 
{
    std::string value;
};

namespace boost { namespace spirit { namespace traits {
    template <> // <typename Attrib, typename T, typename Enable>
        struct assign_to_attribute_from_value<Value, u32_string, void>
        {
            static void call(u32_string const& val, Value& attr)
            {
                u32_to_u8_iterator<u32_string::const_iterator> f(val.begin()), l(val.end());
                attr.value.assign(f, l);
            }
        };
}}}

///////////////////////////////////////////////////////////////
// Parser
///////////////////////////////////////////////////////////////

namespace qi         = boost::spirit::qi;
namespace encoding   = qi::standard_wide;
//namespace encoding = qi::unicode;

template <typename It, typename Skipper = encoding::space_type>
    struct parser : qi::grammar<It, Value(), Skipper>
{
    parser() : parser::base_type(start)
    {
        string = qi::lexeme [ L'"' >> *char_ >> L'"' ];

        static qi::uint_parser<uint32_t, 16, 4, 4> _4HEXDIG;

        char_ = +(
                ~encoding::char_(L"\"\\")) [ qi::_val += qi::_1 ] |
                    qi::lit(L"\x5C") >> (                    // \ (reverse solidus)
                    qi::lit(L"\x22") [ qi::_val += L'"'  ] | // "    quotation mark  U+0022
                    qi::lit(L"\x5C") [ qi::_val += L'\\' ] | // \    reverse solidus U+005C
                    qi::lit(L"\x2F") [ qi::_val += L'/'  ] | // /    solidus         U+002F
                    qi::lit(L"\x62") [ qi::_val += L'\b' ] | // b    backspace       U+0008
                    qi::lit(L"\x66") [ qi::_val += L'\f' ] | // f    form feed       U+000C
                    qi::lit(L"\x6E") [ qi::_val += L'\n' ] | // n    line feed       U+000A
                    qi::lit(L"\x72") [ qi::_val += L'\r' ] | // r    carriage return U+000D
                    qi::lit(L"\x74") [ qi::_val += L'\t' ] | // t    tab             U+0009
                    qi::lit(L"\x75")                         // uXXXX                U+XXXX
                        >> _4HEXDIG [ qi::_val += qi::_1 ]
                );

        // entry point
        start = string;
    }

    private:
    qi::rule<It, Value(),  Skipper> start;
    qi::rule<It, u32_string()> string;
    qi::rule<It, u32_string()> char_;
};

// input assumed to be utf8
Value parse(std::string const& input) {
    auto first(begin(input)), last(end(input));

    typedef boost::u8_to_u32_iterator<decltype(first)> Conv2Utf32;
    Conv2Utf32 f(first), saved = f, l(last);

    static const parser<Conv2Utf32, encoding::space_type> p;

    Value parsed;
    if (!qi::phrase_parse(f, l, p, encoding::space, parsed))
    {
        std::cerr << "whoops at position #" << std::distance(saved, f) << "\n";
    }

    return parsed;
}

#include <iostream>

int main()
{
    Value parsed = parse("\"Footnote: ¹ serious busineş\\u1e61\"");
    std::cout << parsed.value;
}
