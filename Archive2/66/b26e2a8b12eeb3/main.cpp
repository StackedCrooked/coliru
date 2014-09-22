// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct MyField
{
    bool        isConst = false;
    std::string mtype   = "";
    std::string name    = "";

    friend std::ostream& operator<<(std::ostream& os, MyField const& mf)
    {
        return os << "MyField[" 
                        << "isConst:" << std::boolalpha << mf.isConst 
                        << "\nmtype:" << mf.mtype
                        << "\nname: " << mf.name << "]";
    }
};

BOOST_FUSION_ADAPT_STRUCT
    (
     MyField,
     (bool, isConst)
     (std::string, mtype)
     (std::string, name)
    )

template<typename Iterator, typename TSkipper = boost::spirit::ascii::space_type>
struct field_grammar : qi::grammar <Iterator, MyField(), TSkipper>
{
    field_grammar() : field_grammar::base_type(field, "field_grammar")
    {
        // must parse values such as: int, list, i, j9_
        valid_symbols = qi::char_("a-zA-Z") >> *(qi::char_("a-zA-Z0-9_"));
        field         = qi::matches["const"] >> valid_symbols >> valid_symbols;

        BOOST_SPIRIT_DEBUG_NODES((valid_symbols)(field));
    }

    boost::spirit::qi::rule<Iterator, std::string()> valid_symbols;
    boost::spirit::qi::rule<Iterator, MyField(), TSkipper> field;
};

void SpiritTestSimple()
{
    std::string const mdata = "int destroyWindow";

    std::string::const_iterator first = mdata.begin(), last = mdata.end();
    field_grammar<std::string::const_iterator> test_grammar;

    try
    {
        MyField parsed;
        if (qi::phrase_parse(first, last, test_grammar, 
                                     boost::spirit::ascii::space, parsed))
        {
            std::cout << "Parsed: " << parsed << "\n";
        } else
        {
            std::cout << "Failed to parse '" << std::string(first, last) << "'\n";
        }
    }
    catch (const qi::expectation_failure<std::string::const_iterator>& e)
    {
        std::string frag(e.first, e.last);
        std::cout << e.what() << "'" << frag << "'" << std::endl;
    }

}

int main()
{
    SpiritTestSimple();
}
