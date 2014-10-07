#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
    std::string s = "this is a test";
    auto input_rng = boost::make_iterator_range(s.begin(), s.end());
    
    std::cout << input_rng.size() << '\n';
    
    return 0;
}