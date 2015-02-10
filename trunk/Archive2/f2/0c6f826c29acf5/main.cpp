#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/io.hpp>
//#include <boost/spirit/include/classic.hpp>
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

namespace qi = boost::spirit::qi;

// From here original file continues
namespace StateMachine {
namespace Private {

    template<typename Iterator>
    struct LuaParameterDataParser : qi::grammar<Iterator, LuaParameterData(), qi::ascii::space_type>
    {
        LuaParameterDataParser() : LuaParameterDataParser::base_type(start)
        {
            quotedString = qi::lexeme['"' >> +(qi::ascii::char_ - '"') >> '"'];

            start =
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
    using It = std::string::const_iterator;

    std::string const input = R"(
        "parameter" : {
            "name"        : "name"       , 
            "type"        : "type"       , 
            "unit"        : "unit"       , 
            "cardinality" : "cardinality", 
            "value"       : "value"       
        }
    )";
    It f = input.begin(), 
       l = input.end();

    StateMachine::Private::LuaParameterDataParser<It> p;
    StateMachine::Private::LuaParameterData data;
    bool ok = qi::phrase_parse(f, l, p, qi::ascii::space, data);

    if (ok) {
        std::wcout << L"Parsed: \n";
        std::wcout << L"\tname: " << data.name << L'\n';
        std::wcout << L"\ttype: " << data.type << L'\n';
        std::wcout << L"\tunit: " << data.unit << L'\n';
        std::wcout << L"\tcardinality: " << data.cardinality << L'\n';
        std::wcout << L"\tvalue: " << data.value << L'\n';
    } else {
        std::wcout << L"Parse failure\n";
    }

    if (f!=l)
        std::wcout << L"Remaining unparsed: '" << std::wstring(f,l) << L"'\n";
}
