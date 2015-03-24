/*!
 *  \file   event_grammar.hpp
 *  \brief  This class defines the grammar for the Script Language Events.
 *  \note   This class uses features from Boost::Spirit.
 */
#ifndef EVENT_GRAMMAR_HPP
#define EVENT_GRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <string>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;


template <typename Iterator, typename Skipper>
struct Event_Grammar
    : boost::spirit::qi::grammar<Iterator, Skipper>
{
    Event_Grammar() : Event_Grammar::base_type(start)
        {
            using boost::spirit::ascii::char_;
            using boost::spirit::qi::eps;

            start = 
                (
                    char_('@') >> char_('(') >> char_(')')
                )
                ;

        }
    boost::spirit::qi::rule<Iterator, Skipper> start;
};


#endif // EVENT_GRAMMAR_HPP

/*!
 *  \file   event_parser.hpp
 *  \brief  This file defines a parser Script Language Events, this is the root.
 *  \note   This file should be used with Boost::Spirit parsers.
 */
#ifndef EVENT_PARSER_HPP
#define EVENT_PARSER_HPP
//#include "event_grammar.hpp"

#include <string>
#include <boost/spirit/include/qi.hpp>

template <typename Iterator>
bool Event_Parser(Iterator first, Iterator last)
{
    using ascii::space;
    using ascii::char_;

    Event_Grammar<Iterator, ascii::space_type>  parser;
    bool result = qi::phrase_parse(first, last, parser, ascii::space);
    if (first != last)
        return false;
    return result;
}

#endif //ndef EVENT_PARSER_HPP
/*!
 *  \file   main.cpp
 *  \brief  This file contains code to validate the Script Compiler
 *          Event grammar.
 *  \note   This project uses the Boost::Spirit library for parsing.
 */
#include <iostream>
#include <string>
#include <cstdlib>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

//#include "event_parser.hpp"

using qi::double_;
using qi::_1;
using ascii::space;
using ascii::char_;
using phoenix::ref;
using qi::phrase_parse;

int main(void)
{
    const char  program_header[] =
        "\n"
        "Event Grammar Tester:\n"
        "    A program to validate the grammar for\n"
        "    a Script Language Event.\n"
        "\n";

    std::cout.write(program_header, sizeof(program_header) - 1);

    const std::string   parse_test_string = "@ ( )";
    std::string         token_names;
    bool result = Event_Parser(parse_test_string.begin(), parse_test_string.end());

    std::cout << "Parsing ";
    if (result)
    {
        std::cout << "succeeded";
    }
    else
    {
        std::cout << "failed";
    }
    std::cout << " for statement \""
              << parse_test_string
              << "\"\n";

    return EXIT_SUCCESS;
}
