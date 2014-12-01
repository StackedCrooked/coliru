#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>

int main() {
    std::vector<std::vector<std::string> > child_hobbies;

    unsigned n, c, f;

    if (std::cin >> n >> c >> f)
    {
        using namespace boost::spirit::qi;

        if (std::cin >> std::noskipws >> phrase_match(eol >>
                repeat(n) [ repeat(c) [ lexeme[+graph] ] >> eol ], blank, child_hobbies)) 
        {
            for(auto s : child_hobbies)
                std::copy(begin(s), end(s), std::ostream_iterator<std::string>(std::cout << "\n", ";"));
        }
        else
        {
            std::cout << "Input error";
        }
    }

}
