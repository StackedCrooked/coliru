#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_DEBUG
// #include "core/spirit/position.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace qi = boost::spirit::qi;

struct my_handler_f
{
    template <typename...> struct result { typedef void type; };

    template <typename... T>
    void operator()(T&&...) const {
        std::cout << "\nmy_handler_f() invoked with " << sizeof...(T) << " arguments\n";
    }
};

struct append_utf8_f
{
    template <typename, typename>
    struct result { typedef void type; };

    template <typename INT>
    void operator()(INT in, std::string& to) const
    {
        auto out = std::back_inserter(to);
        boost::utf8_output_iterator<decltype(out)> convert(out);
        *convert++ = in;
    }
};


struct get_line_f
{
    template <typename> struct result { typedef size_t type; };
    template <typename It> size_t operator()(It const& pos_iter) const
    {
        return get_line(pos_iter);
    }
};

struct RangePosition { size_t beginLine, endLine; };

struct String : public RangePosition
{
    String()
        : RangePosition()
        , value()
        , source()
    {
    }

    std::string value;
    std::string source;
};

BOOST_FUSION_ADAPT_STRUCT(String,
                            (std::string, value)
                            (std::string, source)
                            (size_t,      beginLine)
                            (size_t,      endLine)
                          )

template <typename Iterator>
struct source_string : qi::grammar<Iterator, String(), qi::space_type>
{
    struct escape_symbols : qi::symbols<char, char>
    {
        escape_symbols()
        {
            add
                ("\'"    , '\'')
                ("\""    , '\"')
                ("\?"    , '\?')
                ("\\"    , '\\')
                ("0"     , '\0')
                ("a"     , '\a')
                ("b"     , '\b')
                ("f"     , '\f')
                ("n"     , '\n')
                ("r"     , '\r')
                ("t"     , '\t')
                ("v"     , '\v')
            ;
        }

    } escape_symbol;

    source_string() : source_string::base_type(start)
    {
        using qi::raw;
        using qi::_val;
        using qi::_1;
        using qi::_2;
        using qi::_3;
        using qi::_4;
        using qi::space;
        using qi::omit;
        using qi::no_case;
        using qi::print;
        using qi::eps;
        using qi::on_error;
        using qi::fail;
        using qi::lit;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;
        using phx::ref;
        using phx::val;

        escape %= escape_symbol;

        character %=   (no_case["\\x"] > hex12)
                        | ("\\"  > (oct123 | escape))
                        | (print - (lit('"') | '\\'));

        unicode =   ("\\u" > hex4[append_utf8(_1, _val)])
                    | ("\\U" > hex8[append_utf8(_1, _val)]);

        string_section %= '"' > *(unicode | character) > '"';

        string %= string_section % omit[*space];

        main = raw [
                       string[at_c<0>(_val) = _1]
                   ]
                   [
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1)),
                       at_c<3>(_val) = get_line_(end(_1))
                   ];

        start %= eps > main;

        on_error<fail>(start, my_handler);
    }

    boost::phoenix::function<my_handler_f> my_handler;

    qi::rule<Iterator, std::string()> escape;
    qi::uint_parser<char, 16, 1, 2> hex12;  
    qi::uint_parser<char,  8, 1, 3> oct123;
    qi::rule<Iterator, std::string()> character;

    qi::uint_parser<uint16_t, 16, 4, 4> hex4;
    qi::uint_parser<uint32_t, 16, 8, 8> hex8;
    boost::phoenix::function<append_utf8_f> append_utf8;
    qi::rule<Iterator, std::string()> unicode;

    qi::rule<Iterator, std::string()> string_section;
    qi::rule<Iterator, std::string()> string;

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, String(), qi::space_type> main;
    qi::rule<Iterator, String(), qi::space_type> start;
};

int main()
{
    std::string str[] =
    {
        "\"\\u1234\\U0002345\"",  
        //"\"te\"\"st\"",
        //"\"te\"  \"st\"",
        //"\"te\" \n \"st\"",
        //"\"\"",
        //"\"\\\"\"",
        //"\"test\"",
        //"\"test\" something",
        //"\"\\\'\\\"\\\?\\\\\\a\\b\\f\\n\\r\\t\\v\"",
        //"\"\\x61cd\\X3012\\x7z\"",
        //"\"\\141cd\\06012\\78\\778\"",
        "\"te",
        //"\"te\nst\"",
        //"\"test\\\"",
        //"\"te\\st\"",
        //
    };

    typedef boost::spirit::line_pos_iterator<std::string::const_iterator> Iterator;

    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
    {
        source_string<Iterator> g;
        Iterator iter(str[i].begin());
        Iterator end(str[i].end());

        String string;
        bool r = phrase_parse(iter, end, g, qi::space, string);
        if (r)
            std::cout << string.beginLine << "-" << string.endLine << ": " << string.value << " === " << string.source << "\n";
        else
            std::cout << "Parsing failed\n";
    }
}

