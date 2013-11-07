#include <string>
#include <fstream>
#include <algorithm>
#include "sstream"
#include <locale.h>
#include <iomanip>

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/functional/hash.hpp>
#include <boost/variant.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/exception/diagnostic_information.hpp> 
#include <boost/algorithm/string.hpp> 

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

typedef double NumValue;
typedef boost::variant<double, std::wstring> GenericValue;

static NumValue const NumValueDoubleNull = std::numeric_limits<NumValue>::infinity();
static std::wstring const ParserNullChar = L"%null%";

struct IsNull : boost::static_visitor<bool> {
    bool operator()(double num) const { 
        return (num == NumValueDoubleNull || num<10); // TODO FIXME :) for demo only
    }
    bool operator()(std::wstring const& s) const { 
        return boost::iequals(s, ParserNullChar);
    }
};

GenericValue TakeOne(std::vector<GenericValue> const& arglist) {
    assert(!arglist.empty());
    for (auto& v : arglist)
        if (!boost::apply_visitor(IsNull(), v))
            return v;
    return arglist.back(); // last is the default
}
BOOST_PHOENIX_ADAPT_FUNCTION(GenericValue, TakeOne_, TakeOne, 1)

template <typename It, typename Skipper = qi::space_type >
struct MapFunctionParser : qi::grammar<It, GenericValue(), Skipper>
{
    MapFunctionParser() : MapFunctionParser::base_type(expr_)
    {
        using namespace qi;

        function_call_ = 
            no_case[L"TakeOne"] > 
            ('(' > expr_ % ',' > ')') [_val=TakeOne_(_1)];

        string_ =   (L'"' > *~char_('"') > L'"')
            | (L"'" > *~char_("'") > L"'"); 

        factor_ =
            (no_case[ParserNullChar]) [_val = NumValueDoubleNull]
        |   double_                   [ _val = _1]
        |   string_                   [ _val = _1]
        |   function_call_            [ _val = _1]
        ;


        expr_ = factor_;

        on_error<fail> ( expr_, std::cout
            << phx::val("Error! Expecting ") << _4 << phx::val(" here: \"")
            << phx::construct<std::string>(_3, _2) << phx::val("\"\n"));

#ifdef _DEBUG 
        BOOST_SPIRIT_DEBUG_NODE(function_call_);
        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(string_);
        BOOST_SPIRIT_DEBUG_NODE(factor_);
#endif
    }

private:
    qi::rule<It, std::wstring()> string_;
    qi::rule<It, GenericValue(), Skipper> function_call_, expr_, factor_;

};

int main()
{
    std::wstringstream wss;
    typedef std::wstring::const_iterator AttIter;
    MapFunctionParser<AttIter , boost::spirit::qi::space_type> mapFunctionParser;
    bool ret;
    GenericValue result;

    std::wstring functionStr = L"TakeOne(%null%, 5, 7, 8, 42, 'default')";
    std::wstring::const_iterator beginExpression(functionStr.begin());
    std::wstring::const_iterator endExpression(functionStr.end());

    ret = boost::spirit::qi::phrase_parse(beginExpression,endExpression,mapFunctionParser,boost::spirit::qi::space,result);

    std::wcout << std::boolalpha << ret << "\n" 
               << result << std::endl;
    return 0;
}
