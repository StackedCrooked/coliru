/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for arbitrary tuples. This example presents a parser
//  for an employee structure.
//
//  [ JDG May 9, 2007 ]
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    struct relation
    {
        std::string location;
        std::string noun;
        double probability;
        int total;
    };
}

// We need to tell fusion about our relation struct to make it a first-class fusion citizen. This has to be in global scope.

BOOST_FUSION_ADAPT_STRUCT(
    client::relation,
    (std::string, location)
    (std::string, noun)
    (double, probability)
    (int, total)
)

namespace client
{

    template <typename Iterator>
    struct relation_parser : qi::grammar<Iterator, relation(), ascii::space_type>
    {
        relation_parser() : relation_parser::base_type(start)
        {
            using qi::int_;
            using qi::lexeme;
            using qi::lit;
            using qi::double_;
            using ascii::char_;

            start %=
                lexeme[+(char_ - '/')]
                >>  lexeme[+(char_ - '/')] >> double_ - '/' >> int_
                ;
        }

        qi::rule<Iterator, relation(), ascii::space_type> start;
    };
}


int main()
{

    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::relation_parser<iterator_type> relation_parser;

    relation_parser g; // Our grammar
    std::string str = "addition/work/0.2387/6664";

        client::relation rel;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, g, space, rel);

        if (r && iter == end)
        {
            std::cout << boost::fusion::tuple_open('[');
            std::cout << boost::fusion::tuple_close(']');
            std::cout << boost::fusion::tuple_delimiter(", ");

            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "got: " << boost::fusion::as_vector(rel) << std::endl;
            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }

    return 0;
}
