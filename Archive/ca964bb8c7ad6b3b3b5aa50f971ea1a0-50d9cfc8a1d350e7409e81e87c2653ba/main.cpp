#include <string>

struct derived_string : std::string
{
    using std::string::string;    
};

int main()
{    
    derived_string d1(std::string()); // ok    
    derived_string d2(std::string{}); // not ok    
    derived_string d3{std::string()}; // not ok
    derived_string d4{std::string{}}; // not ok
    
    std::string str;
    derived_string d5(str); // not ok
    derived_string d6{str}; // not ok
}