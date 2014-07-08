#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

using namespace std;
using namespace boost::spirit;

struct VariableInitialization
{
    std::string m_type;
    bool m_is_static;
    std::string m_name;
    std::string m_value;
};

BOOST_FUSION_ADAPT_STRUCT(
        VariableInitialization,
        (std::string, m_type)
        (bool, m_is_static)
        (std::string, m_name)
        (std::string, m_value)
        )

template <typename Iterator>
struct VariableInitializationParser : qi::grammar<Iterator, VariableInitialization(), ascii::space_type> {
    /*!
     * IsStatic is a mapping betwen a char and a boolean
     */
    struct IsStatic_ : qi::symbols<char, bool> {
        IsStatic_()
        {
            add("@", false)("#", true);
        }
    } IsStatic;

    VariableInitializationParser() :
        VariableInitializationParser::base_type(start) {
            using qi::lit;
            using ascii::char_;

            var_type   = qi::raw[lit("Position")|"String"|"Numeric"|"Integer"|"Trajectory"];

            identifier = (ascii::alpha|'_') >> *(ascii::alnum|'_');

            var_value  = qi::lexeme[*(char_)];
            start      = var_type >> IsStatic >> identifier >> '=' >> var_value;
        }

    qi::rule<Iterator, std::string(), ascii::space_type> var_type;
    qi::rule<Iterator, std::string(), ascii::space_type> identifier;
    qi::rule<Iterator, std::string(), ascii::space_type> var_value;
    qi::rule<Iterator, VariableInitialization(), ascii::space_type> start;
};

int main()
{
    VariableInitialization variable;

    std::string input = "Position #toto=1;2;2";
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator end = input.end();

    VariableInitializationParser<std::string::const_iterator> m_parser;

    bool ok = phrase_parse(iter, end, m_parser, boost::spirit::ascii::space, variable);
    if(!ok) return false;

    std::cout << "Boost version : " << BOOST_VERSION        << "\n";
    std::cout << "Type : "          << variable.m_type      << "\n"
              << "Is Static : "     << variable.m_is_static << "\n"
              << "Name :"           << variable.m_name      << "\n"
              << "Value :"          << variable.m_value     << "\n";
}
