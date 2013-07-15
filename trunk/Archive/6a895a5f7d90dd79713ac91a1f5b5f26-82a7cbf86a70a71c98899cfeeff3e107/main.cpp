#include <iostream>
#include <sstream>
#include <fstream>

#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/phoenix.hpp"
#include "boost/spirit/include/support_iso8859_1.hpp"
#include "boost/fusion/include/adapt_struct.hpp"

struct ElemParseData
{
    std::vector<float> verts;
    std::vector<unsigned int>  idx;
};

namespace boost { namespace spirit { namespace traits {

    template<> 
        struct is_container<ElemParseData, void> : mpl::true_ { };
    template<> 
        struct container_value<ElemParseData, void> { 
             typedef boost::variant<std::vector<float>, std::vector<unsigned int>> type;
        };
    template <>
        struct push_back_container<ElemParseData, std::vector<float>, void> {
            static bool call(ElemParseData& c, std::vector<float> const& val) {
                c.verts.insert(c.verts.end(), val.begin(), val.end());
                return true;
            }
        };
    template <>
        struct push_back_container<ElemParseData, std::vector<unsigned int>, void> {
            static bool call(ElemParseData& c, std::vector<unsigned int> const& val) {
                c.idx.insert(c.idx.end(), val.begin(), val.end());
                return true;
            }
        };
}}}

bool doParse( ElemParseData &parseData, const std::string &data )
{
    namespace phx     = boost::phoenix;
    namespace qi      = boost::spirit::qi;
    namespace iso8859 = boost::spirit::iso8859_1;

    struct objGram : qi::grammar<std::string::const_iterator, ElemParseData(), iso8859::space_type>
    {
        objGram() : objGram::base_type(start)
        {
            using namespace qi;

            vertex   = +('v' >> double_ >> double_ >> double_);
            elements = +('f' >> int_    >> int_    >> int_);
            start    = *(vertex | elements);
        }

        qi::rule<std::string::const_iterator, ElemParseData(), iso8859::space_type> start;
        qi::rule<std::string::const_iterator, std::vector<float>(), iso8859::space_type> vertex;
        qi::rule<std::string::const_iterator, std::vector<unsigned>(), iso8859::space_type> elements;
    } objGrammar;

    std::string::const_iterator f = data.cbegin(), l = data.cend();
    bool res = qi::phrase_parse( f, l, objGrammar, iso8859::space, parseData );

    // print everything that hasn't been processed by the parser
    if (f!=l)
    {
        std::cout << "#### Trail ####" << std::endl;
        std::cout << std::string(f, l) << std::endl;
    }

    return res;
}


int main( int argc, char* argv[] )
{
#if 0
    std::filebuf fb;
    if (fb.open("parsetest.txt", std::ios::in))
    {
        ss << &fb;
        fb.close();
    }

    const std::string s = ss.str();
#else
    std::stringstream ss;
    ss << std::cin.rdbuf();
    const std::string s = ss.str();
#endif

    ElemParseData parseData;
    bool res = doParse( parseData, s );


    // print results
    std::cout << std::endl << "Parsing result: " << res << std::endl;
    std::cout << "---######### ResultData #########---" << std::endl;
    std::cout << "---- Begin vertex data ----" << std::endl;
    std::vector<float>::iterator it;
    for ( it = parseData.verts.begin(); it != parseData.verts.end(); ++it )
        std::cout << *it << std::endl;
    std::cout << "---- End vertex data ----" << std::endl;

    std::cout << std::endl;

    std::cout << "---- Begin index data ----" << std::endl;
    std::vector<unsigned int>::iterator idxIt;
    for ( idxIt = parseData.idx.begin(); idxIt != parseData.idx.end(); ++idxIt )
            std::cout << *idxIt << std::endl;
    std::cout << "---- End index data ----" << std::endl;
}
