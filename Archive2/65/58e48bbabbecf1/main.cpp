#include <iostream>
#include <string>
#include <vector>

struct A
{
    const std::vector<std::string>& names() const& { return names_ ; }
    
    #ifdef WITH_RVALUE_OVERLOAD
        std::vector<std::string> names() const&& { return std::move(names_) ; }
    #endif // WITH_RVALUE_OVERLOAD
    
    #ifdef DISABLE_ON_RVALUES
        std::vector<std::string> names() const&& = delete ;
    #endif // DISABLE_ON_RVALUES
    
    std::vector<std::string> names_ ;
};

A foo() { return { { "one", "two", "three", "four", "five", "six" } } ; }

int main()
{
    for( const auto& s : foo().names() ) std::cout << s << ' ' ; // UB
    std::cout << "\n\n\n" ;
}
