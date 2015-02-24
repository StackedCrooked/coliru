#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/config/warning_disable.hpp>

#include <boost/spirit/include/qi.hpp>
//[mini_xml_karma_sr_includes
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
//]
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

//[mini_xml_karma_sr_using
using namespace boost::spirit;
using namespace boost::spirit::ascii;
//]

namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;

using phoenix::at_c;

///////////////////////////////////////////////////////////////////////////////
//  Our mini XML tree representation
///////////////////////////////////////////////////////////////////////////////
struct mini_xml;

typedef
    boost::variant<
        boost::recursive_wrapper<mini_xml>
      , std::string
    >
mini_xml_node;

typedef std::list<mini_xml_node> mini_xml_nodes;

struct mini_xml
{
    std::string name;               // tag name
    mini_xml_nodes children;        // children
};

// We need to tell fusion about our mini_xml struct
// to make it a first-class fusion citizen
BOOST_FUSION_ADAPT_STRUCT(
    mini_xml,
    (std::string, name)
    (mini_xml_nodes, children)
)

///////////////////////////////////////////////////////////////////////////////
//  Our mini XML grammar definition
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct mini_xml_parser :
    qi::grammar<Iterator, mini_xml(), space_type>
{
    mini_xml_parser() : mini_xml_parser::base_type(xml)
    {
        text = lexeme[+(char_ - '<')        [_val += _1]];
        node = (xml | text)                 [_val = _1];

        start_tag =
                '<'
            >>  !lit('/')
            >>  lexeme[+(char_ - '>')       [_val += _1]]
            >>  '>'
        ;

        end_tag =
                "</"
            >>  lit(_r1)
            >>  '>'
        ;

        xml =
                start_tag                   [at_c<0>(_val) = _1]
            >>  *node                       [phoenix::insert(at_c<1>(_val), phoenix::end(at_c<1>(_val)), _1)]
            >>  end_tag(at_c<0>(_val))
        ;
    }

    qi::rule<Iterator, mini_xml(), space_type> xml;
    qi::rule<Iterator, mini_xml_node(), space_type> node;
    qi::rule<Iterator, std::string(), space_type> text;
    qi::rule<Iterator, std::string(), space_type> start_tag;
    qi::rule<Iterator, void(std::string), space_type> end_tag;
};

///////////////////////////////////////////////////////////////////////////////
//  A couple of phoenix functions helping to access the elements of the 
//  generated AST
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct get_element
{
    template <typename T1>
    struct result { typedef T const& type; };

    T const& operator()(mini_xml_node const& node) const
    {
        return boost::get<T>(node);
    }
};

phoenix::function<get_element<std::string> > _string;
phoenix::function<get_element<mini_xml> > _xml;

///////////////////////////////////////////////////////////////////////////////
//  The output grammar defining the format of the generated data
///////////////////////////////////////////////////////////////////////////////
//[mini_xml_karma_sr_grammar
template <typename OutputIterator>
struct mini_xml_generator
  : karma::grammar<OutputIterator, mini_xml()>
{
    mini_xml_generator() : mini_xml_generator::base_type(entry)
    {
        karma::_a_type element_name_;

        xml %= 
            '<'  << string[element_name_ = _1] << '>'
            <<  *node
            <<  "</" << string(element_name_) << '>'
            ;

        node %= string | xml;
        entry %= node;
    }

    karma::rule<OutputIterator, mini_xml()> entry;

    karma::rule<OutputIterator, mini_xml(), qi::locals<std::string> > xml;
    karma::rule<OutputIterator, mini_xml_node()> node;
};
//]

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    char const* filename;
    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    std::ifstream in(filename, std::ios_base::in);

    if (!in)
    {
        std::cerr << "Error: Could not open input file: "
            << filename << std::endl;
        return 1;
    }

    std::string storage; // We will read the contents here.
    in.unsetf(std::ios::skipws); // No white space skipping!
    std::copy(
        std::istream_iterator<char>(in),
        std::istream_iterator<char>(),
        std::back_inserter(storage));

    typedef mini_xml_parser<std::string::const_iterator> mini_xml_parser;
    mini_xml_parser xmlin;  //  Our grammar definition
    mini_xml ast; // our tree

    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();
    bool r = qi::phrase_parse(iter, end, xmlin, space, ast);

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";

        typedef std::back_insert_iterator<std::string> outiter_type;
        typedef mini_xml_generator<outiter_type> mini_xml_generator;

        mini_xml_generator xmlout;                 //  Our grammar definition

        std::string generated;
        outiter_type outit(generated);
        bool r = karma::generate(outit, xmlout, ast);

        if (r)
            std::cout << generated << std::endl;
        return 0;
    }
    else
    {
        std::string::const_iterator begin = storage.begin();
        std::size_t dist = std::distance(begin, iter);
        std::string::const_iterator some = 
            iter + (std::min)(storage.size()-dist, std::size_t(30));
        std::string context(iter, some);
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "stopped at: \": " << context << "...\"\n";
        std::cout << "-------------------------\n";
        return 1;
    }
}