#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/qi.hpp>
namespace qi = boost::spirit::qi;

namespace boost { namespace spirit { namespace traits {   
    #define PARSER_DEF(a) using type = decltype(boost::proto::deep_copy(a)); static type call() { return boost::proto::deep_copy(a); }

    template<typename T1, typename T2> 
        struct create_parser<std::pair<T1, T2> > 
        {
            PARSER_DEF('(' >> create_parser<T1>::call() >> ',' >> create_parser<T2>::call() >> ')');
        };

    template<template<typename...> class Container, typename TV, typename... TArgs>
        struct create_parser<Container<TV, TArgs...> >
        {
            PARSER_DEF('[' >> qi::omit[qi::uint_] >> ',' >> '(' >> create_parser<TV>::call() % ',' >> ')' >> ']');
        };

    #undef PARSER_DEF
} } }

int main() {
    std::string const input("\t[1, ((0.97,5)\n, (1.75, 10)) ]");

    auto first = input.begin();
    auto last  = input.end();

    std::vector<std::pair<double, int> > parsed;
    /*bool result_ = */qi::phrase_parse(first, last, qi::auto_, qi::space, parsed);
}
