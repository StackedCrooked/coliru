#include <utility>

template<class Type, class First>
bool any_equal(Type&& f, First&& first)
{
    return f==first;
};
template<class Type, class First, typename... NUMBERS>
bool any_equal(Type&& f, First&& first, NUMBERS&&... numbers )
{
    return f==first || any_equal(std::forward<Type>(f), std::forward<NUMBERS>(numbers)...);
};

#include <string>
#include <iostream>
int main()
{
    std::string a = "HI";
    std::cout <<  any_equal(a, "Hello", std::string("nope"), "HI");    
}