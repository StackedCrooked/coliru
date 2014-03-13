#include <iostream>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <type_traits>

template <class Enum>
auto foo(Enum& v) -> typename std::enable_if<std::is_enum<Enum>::value>::type
{
    printf("foo(enum)\n");
}

template <class Digit>
auto foo(Digit& v) -> typename std::enable_if<std::is_integral<Digit>::value>::type
{
    printf("foo(int)\n");
}

/* вот эти оба метода не скомпилируются:
template <class Enum>
void goo(Enum& v)
{
    static_assert(std::is_enum<Enum>::value, "");
    printf("goo(enum)\n");
}

template <class Digit>
void goo(Digit& v)
{
    static_assert(std::is_integral<Digit>::value, "");
    printf("goo(int)\n");
}
*/

enum class En {
    val
};    

int main()
{
    En v = En::val;
    foo(v);
    
    int i = 1;
    foo(i);
    
    //goo(v);
    
    return 0;
}
