#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

namespace {
    typedef std::string::const_iterator It;

    // 2.2 Basic Rules (rfc1945)
    static const qi::rule<It, std::string()> rfc1945_token = +~qi::char_( " \t><@,;:\\\"/][?=}{:"); // FIXME? should filter CTLs
}

#include <iostream>

int main()
{
    std::string const strRequestLine("Host: 192.168.0.1:12345");
    std::string::const_iterator f(strRequestLine.begin()), l(strRequestLine.end());
    
    std::string key, value;
    if (qi::phrase_parse(f, l, rfc1945_token >> ':' >> qi::lexeme[*(qi::char_ - qi::eol)], qi::space, key, value))
        std::cout << "'" << key << "' -> '" << value << "'\n";
}
