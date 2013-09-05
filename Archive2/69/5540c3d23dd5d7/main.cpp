
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
    std::vector<float> m_v;
};

class Derived : public Base
{
public:
    Derived(std::vector<float> v) : m_v(v)
    {

    }
};
int main() {}