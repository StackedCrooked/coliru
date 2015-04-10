#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <functional>
#include <typeinfo>
#include <memory>



int main()
{
    static const char* u = "U";
    static const char* v = "V";
    std::cout << (u "." v) << "\n";
}
