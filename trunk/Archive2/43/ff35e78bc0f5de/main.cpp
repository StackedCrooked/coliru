#include <boost/type_traits.hpp>

typedef char yes[1];
typedef char no[2];

template<class F>
struct SFINAE
{
    typedef typename boost::decay<F>::type F_decayed;
    
    struct Any
    {
        template<class T>
        Any(T&);
    };
    
    template<class T>
    static yes& test(boost::integral_constant<int, sizeof(Any(T()(5)))>*);
    template<class T>
    static no&  test(...);
    
    static bool const result = sizeof(test<F_decayed>(0)) == sizeof(yes);
};

struct foo
{
    int& operator()(int);
};

struct bar
{
    int operator()(int);
};

struct overloaded
{
    overloaded* operator&() const;
};

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::boolalpha << SFINAE<foo>::result << "\n";
    std::cout << std::boolalpha << SFINAE<bar>::result << "\n";
    std::cout << std::boolalpha << SFINAE<int&(*)(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<int(*)(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<int&(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<int(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<int&(&)(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<int(&)(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<overloaded(int)>::result << "\n";
}