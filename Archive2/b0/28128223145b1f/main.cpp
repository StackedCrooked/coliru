#include <boost/core/demangle.hpp>
#include <typeinfo>
#include <iostream>

int main()
{
    char const * name = "_Zst24__throw_out_of_range_fmtPKcz";
    boost::core::scoped_demangled_name demangled( name );

    std::cout << name << std::endl;
    std::cout << (demangled.get() ? demangled.get() : "[unknown]") << std::endl;
}