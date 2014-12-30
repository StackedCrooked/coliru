#include <string>
#include <type_traits>

template<class T, class = void>
struct A;

template<class T>
struct A<T, typename std::enable_if< std::is_trivial<T>::value >::type>
{
    using Type = T;
};

template<class T>
struct A<T, typename std::enable_if< ! std::is_trivial<T>::value >::type>
{
    int Type;
};

template<class T>
void f(T)
{
    struct C
    {
        typename std::conditional< std::is_trivial<T>::value, int, std::string >::type x;
    };
    typedef typename A<C>::Type Type; // typename required
}

int main()
{
    f(0); // well-formed
    f(std::string{}); // ill-formed
}