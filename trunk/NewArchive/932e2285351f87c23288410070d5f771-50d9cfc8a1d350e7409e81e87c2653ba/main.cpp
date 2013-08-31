#include <string>

struct derived_string : std::string
{
    template<typename ...Args>
    derived_string(Args && ...args) : std::string(std::forward<Args>(args)...) {}
};

int main()
{    
    derived_string d1(std::string()); // ok    
    derived_string d2(std::string{}); // ok
    derived_string d3{std::string()}; // ok
    derived_string d4{std::string{}}; // ok
    
    std::string str;
    derived_string d5(str); // ok
    derived_string d6{str}; // ok
}