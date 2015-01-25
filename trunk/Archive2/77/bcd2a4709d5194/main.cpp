#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

    template<typename Container, typename ElementParser = qi::auto_type>
    void MyParse(std::string const& line, Container& container, ElementParser const& elementParser = ElementParser())
    {
        auto f(line.begin()), l(line.end());
        bool ok = qi::phrase_parse(
                f, l,
                elementParser % ",", qi::blank, container);

        if (!ok || (f!=l))
            throw "parser error: '" + std::string(f,l) + "'"; // FIXME
    } 

#include <set>

int main()
{
    std::vector<int> i;
    std::set<std::string> s;

    MyParse("1,22,33,44,15", i);
    MyParse("1,22,33,44,15", s, *~qi::char_(","));

    for(auto e:i) std::cout << "i: " << e << "\n";
    for(auto e:s) std::cout << "s: " << e << "\n";
}
