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

struct utf8_f
{
    template <typename> struct result { typedef std::string type; };

    template <typename INT>
    std::string operator()(INT in) const
    {
        std::string to;
        auto out = std::back_inserter(to);
        boost::utf8_output_iterator<decltype(out)> convert(out);
        *convert++ = in;
        return to;
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
    qi::symbols<char, char> escape_symbol;

    source_string() : source_string::base_type(main)
    {
        escape_symbol.add
                ("\\\'"    , '\'')
                ("\\\""    , '\"')
                ("\\\?"    , '\?')
                ("\\\\"    , '\\')
                ("\\0"     , '\0')
                ("\\a"     , '\a')
                ("\\b"     , '\b')
                ("\\f"     , '\f')
                ("\\n"     , '\n')
                ("\\r"     , '\r')
                ("\\t"     , '\t')
                ("\\v"     , '\v')
            ;

        using namespace qi;
        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;
        using phx::ref;
        using phx::val;

        escape %= escape_symbol;

        character %=   (no_case["\\x"] >> hex12)
                     | ("\\"  >> oct123)
                     | escape
                     | (print - (qi::lit('"') | '\\'));

        unicode =   ("\\u" >> hex4[_val += utf8(_1)])
                  | ("\\U" >> hex8[_val += utf8(_1)]);

        string_section %= '"' >> *(unicode | character) >> '"';

        string %= string_section % omit[*space];

        main = eps(true) > raw[
                        string[at_c<0>(_val) = _1]
                   ]
                   [
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1)),
                       at_c<3>(_val) = get_line_(end(_1))
                   ]
        ;

        qi::on_error<qi::fail>(this->main, handler_);

        BOOST_SPIRIT_DEBUG_NODES((escape)(character)(unicode)(string_section)(string)(main))
    }

    qi::rule<Iterator, std::string()> escape;
    qi::uint_parser<char, 16, 1, 2> hex12;
    qi::uint_parser<char,  8, 1, 3> oct123;
    qi::rule<Iterator, std::string()> character;

    qi::uint_parser<uint16_t, 16, 4, 4> hex4;
    qi::uint_parser<uint32_t, 16, 8, 8> hex8;
    boost::phoenix::function<utf8_f> utf8;
    qi::rule<Iterator, std::string()> unicode;

    qi::rule<Iterator, std::string()> string_section;
    qi::rule<Iterator, std::string()> string;

    boost::phoenix::function<get_line_f> get_line_;
    boost::phoenix::function<my_handler_f> handler_;
    qi::rule<Iterator, String(), qi::space_type> main;
};

int main()
{
    std::string str[] =
    {
        //"\"\\u1234\\U00012345\"",
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

