#include <iostream>
#include <string>
#include <vector>

struct Base
{
    int x, y;
};

struct Derived : public Base
{
};

template <typename A, typename B,
    typename = typename std::enable_if<std::is_base_of<Base, A>::value && std::is_base_of<Base, B>::value>::type>
A operator-(const A& a, const B& b)
{
    return {b.x - a.x, b.y - a.y};
}

int main()
{

}
