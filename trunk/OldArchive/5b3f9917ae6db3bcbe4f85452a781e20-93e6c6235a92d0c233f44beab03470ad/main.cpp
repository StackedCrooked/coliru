#include <utility>
#include <type_traits>

template <class T, class U, class U2 /* assignable from U*/, class T2 = typename std::remove_reference<T>::type>
   void set_parameter(T&& instance, U&& val, U2 (T2::* pmember))
{
    (std::forward<T>(instance).*(pmember)) = std::forward<U>(val);
}

#include <iostream>
#include <string>
struct X
{
    double foo;
    std::string splurgle;
};

int main()
{
    X x;

    set_parameter(x, 3.14         , &X::foo);
    set_parameter(x, "hello world", &X::splurgle);

    std::cout << x.foo << ", " << x.splurgle;
}
