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

template <typename It, typename TSkipper = boost::spirit::ascii::space_type>
struct MyGrammar : qi::grammar<It, std::list<MyField>(), TSkipper>
{
    MyGrammar() : MyGrammar::base_type(start) {
        valid_symbols = qi::lexeme[+qi::alpha];
        field         = qi::matches[qi::string("const")] >> valid_symbols >> valid_symbols;
        start         = +(field > ";");

        BOOST_SPIRIT_DEBUG_NODES((valid_symbols)(field)(start))
    }
  private:
    qi::rule<std::string::const_iterator, std::string(),        TSkipper> valid_symbols;
    qi::rule<std::string::const_iterator, MyField(),            TSkipper> field;
    qi::rule<std::string::const_iterator, std::list<MyField>(), TSkipper> start;
};

int main()
{
    std::string const data = "aaa aaaa; const bbb bbbb;";

    //-----------------------------------------------------------------
    std::string::const_iterator first = data.begin(), last = data.end();
    std::list<MyField> parsed_vals;

    bool is_parsed = false;

    try
    {
        MyGrammar<std::string::const_iterator> grammar;

        is_parsed = qi::phrase_parse(   first, last,  
                                        grammar, 
                                        boost::spirit::ascii::space, 
                                        parsed_vals);
    }
    catch(const qi::expectation_failure<std::string::const_iterator>& e)
    {
        std::string frag(e.first, e.last);
        std::cout << "Expectation failure: " << e.what() << " at '" << frag << "'" << std::endl;
    }

    BOOST_ASSERT(is_parsed && "the example not parsed");
}
