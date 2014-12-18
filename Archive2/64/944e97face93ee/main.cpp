#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

namespace fusion  = boost::fusion;
namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;
namespace karma   = boost::spirit::karma;
namespace phoenix = boost::phoenix;

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
    qi::grammar<Iterator, mini_xml(), qi::space_type>
{
    mini_xml_parser() : mini_xml_parser::base_type(start)
    {
        using qi::lit;
        using qi::lexeme;
        using ascii::char_;
        using ascii::string;
        using namespace qi::labels;

        text %= lexeme[+(char_ - '<')];
        node %= xml | text;

        start_tag %=
                '<'
            >>  !lit('/')
            >>  lexeme[+(char_ - '>')]
            >>  '>'
        ;

        end_tag =
                "</"
            >>  string(_r1)
            >>  '>'
        ;

        qi::_a_type element_name_;
        xml %=
                start_tag[element_name_ = _1]
            >>  *node
            >>  end_tag(element_name_)
        ;

        start = xml;
    }

    qi::rule<Iterator, mini_xml(), qi::space_type> start;
    qi::rule<Iterator, mini_xml(), qi::space_type, qi::locals<std::string> > xml;
    qi::rule<Iterator, mini_xml_node(), qi::space_type> node;
    qi::rule<Iterator, std::string(), qi::space_type> text;
    qi::rule<Iterator, std::string(), qi::space_type> start_tag;
    qi::rule<Iterator, void(std::string), qi::space_type> end_tag;
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

        xml   %= 
            '<'  << karma::string[element_name_ = karma::_1] << '>'
            <<  *node
            <<  "</" << karma::string(element_name_) << '>'
            ;

        node  %= karma::string | xml;
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
    bool r = qi::phrase_parse(iter, end, xmlin, qi::space, ast);

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


