#include <map>
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;

struct Demo
{
    int i;
    std::string truth;

    using Vars = std::map<std::string, double>;
    Vars vars;
};

BOOST_FUSION_ADAPT_STRUCT(Demo, (int,i)(std::string,truth)(Demo::Vars, vars))

static std::string serialize(Demo const& data)
{
    std::ostringstream oss;
    oss << karma::format(
            "Demo{" << karma::int_ << ';' << karma::string << ';' 
                << '{' 
                        << ('{' << karma::string << ": " << karma::double_ << '}') % ", " 
                << '}'
            << '}', data);

    return oss.str();
}

static Demo deserialize(std::string const& text)
{
    auto f(text.begin()), l(text.end());
    Demo parsed;
    if (qi::parse(f, l,
            "Demo{" >> qi::int_ >> ';' >> +~qi::char_(';') >> ';' 
            >> '{' 
                >> ('{' >> +~qi::char_(':') >> ": " >> qi::double_ >> '}') % ", " >> '}'
            >> '}', parsed))
    {
        return parsed;
    }
    throw std::runtime_error("Parse failed at '" + std::string(f,l) + "'");
}

int main()
{
    Demo a { 42, "LtUaE", { { "PI", 3.1415926 }, { "e", std::exp(1.0) } } };
    std::cout << "Quick serialization: " << karma::format_delimited(karma::auto_, ';', a) << "\n";

    std::string const serialized = serialize(a);
    std::cout << "Serious serialization: " << serialized << "\n";

    // to parse back:
    Demo roundtrip = deserialize(serialized);
    std::cout << "Parsed back: " << karma::format_delimited(karma::auto_, ';', roundtrip) << "\n";
}
