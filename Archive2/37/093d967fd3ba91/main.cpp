#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>

namespace qi = boost::spirit::qi;
using boost::spirit::repository::confix;

int main()
{
    std::string const input("@anything but &at; followed of the string .PV@");
    std::string parsed;

    auto f(input.begin()), l(input.end());
    bool ok = qi::parse(
            f, l,
            confix('@', ".PV@") [+(qi::char_ - '@' - ".PV@")],
            parsed);

    if (ok)   std::cout << "parse success\ndata: " << parsed           << "\n";
    else      std::cerr << "parse failed: '"       << std::string(f,l) << "'\n";
    if (f!=l) std::cerr << "trailing unparsed: '"  << std::string(f,l) << "'\n";

    return ok? 0 : 255;
}
