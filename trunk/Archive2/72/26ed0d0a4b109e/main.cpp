#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main() {
    std::string str;
    while (std::getline(std::cin, str)) {
        auto f = str.begin(), l = str.end();

        std::vector<double> v, w;

        bool ok = qi::phrase_parse(
                f, l, *(qi::double_>>!qi::lit('%')) >> *(qi::double_>>'%'),
                qi::blank | '|', v, w);

        if (ok && f == l) {
            std::cout << "Parsed " << v.size() << "/" << w.size() << " elements\n";
        } else {
            std::istringstream iss(str);
            if (iss >> str && (str == "q" || str == "Q"))
                break;
            std::cout << "Invalid input. Remaining '" << std::string(f,l) << "'\n";
        }
    }
}
