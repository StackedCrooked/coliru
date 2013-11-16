#include <boost/type_traits.hpp>
#include <boost/utility.hpp>
#include <cstddef>

typedef char yes[1];
typedef char no[2];

template<class F, class P>
struct SFINAE
{
    typedef typename boost::decay<F>::type F_decayed;
    
    struct Any
    {
        template<class T>
        Any(T&);
    };
    
    template<class T>
    static yes& test(boost::integral_constant<std::size_t,
                         sizeof(Any( boost::declval<T>()(boost::declval<P>()) ))>*);
    template<class T>
    static no&  test(...);
    
    static bool const result = sizeof(test<F_decayed>(0)) == sizeof(yes);
};

struct foo
{
    bool& operator()(int);
    bool operator()(double);
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
    std::cout << std::boolalpha << SFINAE<foo, int>::result << "\n";
    std::cout << std::boolalpha << SFINAE<foo, double>::result << "\n";
    std::cout << std::boolalpha << SFINAE<bar, int>::result << "\n";
    std::cout << std::boolalpha << SFINAE<foo&(*)(long), int>::result << "\n";
    std::cout << std::boolalpha << SFINAE<void(*)(int), short>::result << "\n";
    std::cout << std::boolalpha << SFINAE<bool&(short), long>::result << "\n";
    std::cout << std::boolalpha << SFINAE<void(float), int>::result << "\n";
    std::cout << std::boolalpha << SFINAE<char&(&)(bool), long>::result << "\n";
    std::cout << std::boolalpha << SFINAE<foo(&)(int), short>::result << "\n";
    std::cout << std::boolalpha << SFINAE<overloaded(int), bool>::result << "\n";
}