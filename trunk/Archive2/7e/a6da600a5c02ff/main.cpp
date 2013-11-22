#include <boost/type_traits.hpp>

typedef char yes[1];
typedef char no[2];

template<class F>
struct SFINAE
{
    template<class T>
    static yes& test(boost::integral_constant<int, sizeof(&(T()(5)))>*);
    template<class T>
    static no&  test(...);
    
    static bool const result = sizeof(test<F>(0)) == sizeof(yes);
};

struct foo
{
    int& operator()(int);
};

struct bar
{
    int operator()(int);
};

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::boolalpha << SFINAE<foo>::result << "\n";
    std::cout << std::boolalpha << SFINAE<bar>::result << "\n";
}