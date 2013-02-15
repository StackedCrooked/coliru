#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
namespace qi = boost::spirit::qi;

template<typename T> T reversed(T c) {  return T(c.rbegin(), c.rend()); }

int main (int argc, char** argv)
{
    const std::string input("?myvolatileStaticMember@myclass@@2HC");

    auto f = begin(input), l = end(input);

    auto identifier = +~qi::char_("@");
    auto delimit    = qi::lit("@") - "@@";

    std::vector<std::string> qualifiedName;
    std::string typeId;

    if (qi::parse(f,l,
                '?' >> identifier % delimit >> "@@" >> +qi::char_,
                qualifiedName,
                typeId))
    {
        using namespace boost::spirit::karma;
        qualifiedName = reversed(qualifiedName);
        std::cout << "Qualified name: "  << format(auto_ % "::" << "\n", qualifiedName);
        std::cout << "Type indication: '" << typeId << "'\n";
    }
}