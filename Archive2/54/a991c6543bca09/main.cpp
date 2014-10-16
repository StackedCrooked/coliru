#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace boost;

int main()
{
    std::string text = "foo   bar";
    boost::iterator_range<std::string::iterator> r(text.begin(), text.end());

    std::vector<iterator_range<std::string::const_iterator> > result;
    algorithm::split(result, r, is_any_of(" \n\t"), algorithm::token_compress_on);

    for (auto i : result)
        std::cout << "distance: " << distance(text.cbegin(), i.begin()) << ", "
                  << "length: " << i.size() << ", "
                  << "value: '" << i << "'\n";
}