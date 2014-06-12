
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <string>

class Base
{
public:
    std::vector<float> protectedElement;
};

class Derived : public Base
{
public:
    Derived(std::vector<float> v) : protectedElement(v)
    {

    }
};
int main() {}