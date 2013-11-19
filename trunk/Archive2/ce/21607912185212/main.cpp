#include <iostream>
#include <string>
#include <cstdlib>

int main ()
{
    std::string str_name="23423.34";
    float a = strtof (str_name.c_str(), NULL);
    std::cout << a << '\n';
}
