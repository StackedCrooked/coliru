#include <boost/range/adaptors.hpp>
#include <vector>

#include <iostream>

using boost::adaptors::transformed;

int main()
{
    const std::vector</* const */ std::string> v { "test", "goodbye" };
    auto convert = std::mem_fn(&std::string::c_str);

    const auto vc = boost::copy_range<std::vector<const char*> >(v | transformed(convert));
    
    for (auto cc : vc)
        std::cout << cc << "\n";
}
