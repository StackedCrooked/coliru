#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
typedef boost::spirit::ascii::space_type TSkipper;

struct MyField
{
    bool isConst;
    std::string mtype;
    std::string name;
};

BOOST_FUSION_ADAPT_STRUCT
    (
    MyField,
    (bool, isConst)
    (std::string, mtype)
    (std::string, name)
    )

struct MyFunc
{
    MyField header;
    std::list<MyField> params;
};

BOOST_FUSION_ADAPT_STRUCT
    (
    MyFunc,
    (MyField, header)
    (std::list<MyField>, params)
    )

int main()
{
    qi::rule<std::string::const_iterator, std::string(), TSkipper> valid_symbols;
    qi::rule<std::string::const_iterator, MyField(), TSkipper> field;
    qi::rule<std::string::const_iterator, MyFunc(), TSkipper> func;
    qi::rule<std::string::const_iterator, std::list<MyFunc>(), TSkipper> services;

    valid_symbols %= qi::lexeme[+qi::char_("a-zA-Z")];
    field %= qi::matches["const"] >> valid_symbols >> valid_symbols;

    func %= field
        >   '('
        >   (field % ',')
        >   ')';

    services %= qi::lit("service")
                > '{'
                > +(func > ';')
                > '}';
                
    //BOOST_SPIRIT_DEBUG_NODES((valid_symbols)(field)(func)(services));

    std::string data = "service { bool destroyWindow(int aaa, double bbb); }";

    //------------------------------------------------------------------------------------------------
    std::string::const_iterator first = data.begin(), last = data.end();
    std::list<MyFunc> parsed;
    bool is_parsed;
    try
    {
        is_parsed = qi::phrase_parse(   first, last, 
                                        services,
                                        boost::spirit::ascii::space, parsed);
    }
    catch(const qi::expectation_failure<std::string::const_iterator>& e)
    {
        std::string frag(e.first, e.last);
        std::cout << e.what() << "'" << frag << "'" << std::endl;
    }

    BOOST_ASSERT(is_parsed && "the example not parsed");
}
