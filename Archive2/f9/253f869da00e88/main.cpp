#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <fstream>
using namespace boost::spirit::qi;

int main()
{
    std::string oname;
    std::vector<double> numbers;

    if (std::cin >> std::noskipws 
            >> match(*~char_('$') > '$')
            >> match(*~char_('$') > '$')
            >> match(*~char_('$') > '$', oname)
            >> phrase_match(*double_, blank, numbers))
    {
        std::cout << oname << ": parsed " << numbers.size() << " numbers: ";
        for(auto d : numbers) 
            std::cout << d << " ";
    }
}

