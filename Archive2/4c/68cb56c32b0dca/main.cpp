#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

enum class YNO { NO, Y };

struct YNoToken : qi::symbols<char, YNO> {
    YNoToken() { add("Y", YNO::Y)("NO", YNO::NO); }
} static YNo;

int main() {
    std::string const str = "Y-10,NO-3,NO-4,Y-100";
    auto f = str.begin(), l = str.end();

    std::vector<std::pair<YNO, int> > v;

    bool ok = qi::parse(f, l, (YNo >> '-' >> qi::int_) % ',', v);
    if (ok) {
        std::cout << "Parse success: \n";
        for (auto pair : v)
            std::cout << (pair.first==YNO::Y? "Y":"NO") << "\t" << pair.second << "\n";
    }
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
