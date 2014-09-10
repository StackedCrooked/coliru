#include <string>
#include <iostream>
#include <type_traits>

template <typename T>
class foo
{
    public:
    template <typename U>
    typename std::enable_if<std::is_same<T, U>::value>::type
    bar(const U& t)
    {
        std::cout << t << "\n";
    }
};

template <typename X, typename... Args>
class baz : public foo<X>, public baz<Args...>
{
    public:
       using foo<X>::bar;
       using baz<Args...>::bar;
};

template <typename X>
class baz<X> : public foo<X>
{
};

int main()
{
    baz<double, std::string> b;
    b.bar(1.0);
    b.bar(std::string("Demo"));
}