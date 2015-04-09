#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>

namespace qi = boost::spirit::qi;

namespace {
    using double_vec = std::vector<double>;
    using line       = std::pair<double_vec, double_vec>;
    using It         = boost::spirit::istream_iterator;

    static const qi::rule<It, double_vec(bool percent), qi::blank_type> doubles_
        = (qi::double_ >> (qi::eps(qi::_r1) >> '%' | !qi::lit('%'))) % '|'
        ;

    static const qi::rule<It, line(), qi::blank_type> line_
        = (doubles_(false) >> -('|' >> doubles_(true))) 
        | qi::attr(double_vec{}) >> doubles_(true)
        ;
}

int main() {
    std::list<line> data;
    It f(std::cin >> std::noskipws), l;

    if (std::cin >> qi::phrase_match(line_ % +qi::eol >> "q" >> qi::eoi, qi::blank, data)) 
        for (auto& p : data)
            std::cout << "Parsed " << p.first.size() << "/" << p.second.size() << " elements\n";
    else
        std::cout << "Invalid output\n";
}
