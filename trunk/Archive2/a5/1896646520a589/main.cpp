#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>

struct Test 
{
    enum { a = true, b = 1 };    
};

static_assert(std::is_same<
    std::underlying_type_t<decltype(Test::a)>, 
    std::underlying_type_t<decltype(Test::b)>>::value, ""
);

int main()
{    
    int status;
    auto const& bi = typeid(std::underlying_type_t<decltype(Test::a)>);
    std::cout << abi::__cxa_demangle(bi.name(), 0, 0, &status); // unsigned int
}
