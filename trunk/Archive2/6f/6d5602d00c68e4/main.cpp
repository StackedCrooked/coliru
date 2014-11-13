#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;

int main()
{
    std::ifstream ifs("one.txt");
    ifs >> std::noskipws;

    std::vector< std::string > people;
    boost::spirit::istream_iterator first(ifs), last;

    using namespace qi;

    if (parse(first, last, - as_string[+(char_ - eol)] % eol, people))
    {
        std::cout << "Size = " << people.size() << std::endl;

        for (auto person : people)
        {
            std::cout << person << std::endl;
        }
    }
}
