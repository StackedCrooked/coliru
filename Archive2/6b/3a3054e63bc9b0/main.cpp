#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

// This is pasted and copied from another header file

namespace StateMachine {
namespace Private {

struct LuaParameterData {
  std::wstring name;
  std::wstring type;
  std::wstring unit;
  std::wstring cardinality;
  std::wstring value;
};

} // namespace Private
} // namespace StateMachine

BOOST_FUSION_ADAPT_STRUCT(
  StateMachine::Private::LuaParameterData,
  (std::wstring, name)
  (std::wstring, type)
  (std::wstring, unit)
  (std::wstring, cardinality)
  (std::wstring, value)
)

// From here original file continues
namespace StateMachine {
namespace Private {

namespace qi = boost::spirit::qi;

    template<typename Iterator>
    struct LuaParameterDataParser : qi::grammar<Iterator, LuaParameterData(), qi::ascii::space_type>
    {
        LuaParameterDataParser() : LuaParameterDataParser::base_type(start)
        {
            quotedString %= qi::lexeme['"' >> +(qi::ascii::char_ - '"') >> '"'];

            start %=
                qi::lit("\"parameter\"")
                >> ':'
                >> '{'
                >> qi::lit("\"name\""       ) >> ':' >> quotedString >> ','
                >> qi::lit("\"type\""       ) >> ':' >> quotedString >> ','
                >> qi::lit("\"unit\""       ) >> ':' >> quotedString >> ','
                >> qi::lit("\"cardinality\"") >> ':' >> quotedString >> ','
                >> qi::lit("\"value\""      ) >> ':' >> quotedString
                >> '}'
                ;
            BOOST_SPIRIT_DEBUG_NODES((start)(quotedString));
        }

        qi::rule<Iterator, std::string(), qi::ascii::space_type> quotedString;
        qi::rule<Iterator, LuaParameterData(), qi::ascii::space_type> start;
    };

} // namespace Private
} // namespace StateMachine

int main() {
    StateMachine::Private::LuaParameterDataParser<char const*> p;
}
