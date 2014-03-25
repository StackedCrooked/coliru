#include <iostream>
#include <vector>
#include <string>
#include <sstream>




template<typename T>
std::string to_string1(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

struct A{    
    constexpr static float SM = 3.0;
    const static int F = 5;
    int o;
};
    
int main()
{
    A *a = new A();
    to_string1(a->SM);            // undefined reference here
    to_string1(A::F);           
}
