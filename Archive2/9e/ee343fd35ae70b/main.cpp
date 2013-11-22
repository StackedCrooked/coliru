#include <boost/type_traits.hpp>
#include <boost/utility.hpp>

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
    static yes& test(boost::integral_constant<int, sizeof(Any(boost::declval<T>()(5)))>*);
    template<class T>
    static no&  test(...);
    
    static bool const result = sizeof(test<F_decayed>(0)) == sizeof(yes);
};

struct foo
{
    template<class T>
    bool& operator()(T);
};

struct bar
{
    template<class T>
    double operator()(T);
};

struct overloaded
{
    overloaded& operator&() const;
};

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::boolalpha << SFINAE<foo>::result << "\n";
    std::cout << std::boolalpha << SFINAE<bar>::result << "\n";
    std::cout << std::boolalpha << SFINAE<foo&(*)(long)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<void(*)(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<bool&(short)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<void(float)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<char&(&)(bool)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<foo(&)(int)>::result << "\n";
    std::cout << std::boolalpha << SFINAE<overloaded(int)>::result << "\n";
}