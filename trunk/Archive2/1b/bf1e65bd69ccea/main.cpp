#include <iostream>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi_char_class.hpp>

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
            using qi::_val;
            using qi::_1;
            /*!
             * For now, type is one of the three following litterals :
             */
            var_type = qi::raw[lit("Position")|"String"|"Numeric"|"Integer"|"Trajectory"];

            /*!
             * identifier is how a variable can be named. Name of variable is an alpha (a-zA-Z) or an _,followed
             * by any alpha numeric (a-zA-Z0-9) or a _. The followings are correct :
             * _toto _T5ot_To t1oTo ...
             * The following are incorrect
             * 12toto -tiotp ...
             */
            identifier %= ((ascii::alpha|char_('_')) >> *(ascii::alnum|char_('_')));

            /*!
             * var value can be anything because it's parsed by someone else.
             */
            var_value %= qi::lexeme[*(char_)];
            start = var_type >> IsStatic >> identifier >> '=' >> var_value;
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
    // The phrase_parse call wil fill the structure "variable" with the good values if the syntax is correct.
    // if the syntax is not correct, the method will return false.
    // So if input = "Integer #toto= 6", variable.m_type == "Integer", variable.m_isStatic==true,
    // variable.m_name=="toto" and variable.m_vale="6".
    VariableInitializationParser<std::string::const_iterator> m_parser;
    bool ok = phrase_parse(iter, end, m_parser, boost::spirit::ascii::space, variable);
    if(!ok) return false;
    std::cout << "Boost version : " << BOOST_VERSION << std::endl;
    std::cout << "Type : " << variable.m_type << std::endl
              << "Is Static : " << variable.m_is_static << std::endl
              << "Name :" << variable.m_name << std::endl
              << "Value :" << variable.m_value << std::endl;
    return 0;
}
