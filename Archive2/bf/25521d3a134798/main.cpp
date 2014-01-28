#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <string>

using strong_byte = unsigned int; // change to int in order to get proper debug output (chars are printed as chars)

struct Hdr {
    unsigned int samples;
    unsigned int lines;
    unsigned int bands;
    strong_byte  data_type;
    strong_byte  byte_order;
    std::string  interleave;
};

BOOST_FUSION_ADAPT_STRUCT(
    Hdr,
    (unsigned int, samples)
    (unsigned int, lines)
    (unsigned int, bands)
    (strong_byte,  data_type)
    (strong_byte,  byte_order)
    (std::string,  interleave)
)

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct Hdr_parser : qi::grammar<Iterator, qi::blank_type, Hdr()>
{
    Hdr_parser() : Hdr_parser::base_type(start)
    {
    sep = qi::eol | qi::lit(';') | qi::eoi;

        kv_uint = qi::lexeme[ qi::lit(qi::_r1) ] >> '=' >> qi::uint_ >> sep;

        data_type_  = qi::lexeme["data type"]  >> '=' >> data_type_p  >> sep;
        byte_order_ = qi::lexeme["byte order"] >> '=' >> byte_order_p >> sep;
        interleave_ = qi::lexeme["interleave"] >> '=' >> (qi::string("bsq") | qi::string("bil") | qi::string("bip")) >> sep;

        start =
            kv_uint(+"samples") >>
            kv_uint(+"lines")   >>
            kv_uint(+"bands")   >>
            data_type_          >>
            byte_order_         >>
            interleave_;

        BOOST_SPIRIT_DEBUG_NODES((kv_uint)(start)(sep)(data_type_)(byte_order_)(interleave_));
    }

    qi::rule<Iterator, qi::blank_type, Hdr()> start;
    qi::rule<Iterator, qi::blank_type, unsigned int(char const* const)> kv_uint;
    qi::rule<Iterator, qi::blank_type> sep;
    qi::rule<Iterator, qi::blank_type, strong_byte()> data_type_, byte_order_;
    qi::rule<Iterator, qi::blank_type, std::string()> interleave_;

    qi::uint_parser<strong_byte,  2, 1, 1> byte_order_p; // 0 or 1
    qi::uint_parser<strong_byte, 10, 1, 2> data_type_p;  // base 10, 2 digits
};

int main()
{
    namespace qi = boost::spirit::qi;

    std::string input("samples = 1; lines = 2; bands = 3; data type = 4; byte order = 0; interleave = bsq");
    std::string::iterator begin = input.begin();
    std::string::iterator end = input.end();

    Hdr_parser<std::string::iterator> p;
    Hdr h;

    if (!qi::phrase_parse(begin, end, p, qi::blank, h))
    {
        std::cout << "-------------------------------- \n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------------- \n";
    }
}
