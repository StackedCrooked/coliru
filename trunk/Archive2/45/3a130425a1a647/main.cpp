#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace {
    using double_vec = std::vector<double>;
    using It         = std::string::const_iterator;

    static const qi::rule<It, double_vec(bool percent), qi::blank_type> doubles_
        = (qi::double_ >> (qi::eps(qi::_r1) >> '%' | !qi::lit('%'))) % '|';
}

int main() {
    std::string str;
    while (std::getline(std::cin, str)) {
        It f = str.begin(), l = str.end();

        double_vec v, w;

        bool ok = qi::phrase_parse(f, l, 
                  (doubles_(false) >> -('|' >> doubles_(true))) 
                | qi::attr(double_vec{}) >> doubles_(true),
                qi::blank, v, w);

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
