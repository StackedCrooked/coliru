template <class C, class U, class U2 /* assignable from U*/, 
    class T = typename C::value_type>
   void set_parameter(C& container, U&& val, U2 (T::* pmember), typename C::value_type* sfinae=nullptr)
{
    for (auto& instance : container)
        (instance.*(pmember)) = std::forward<U>(val);
}

#include <iostream>
#include <string>
#include <vector>

struct X
{
    double foo;
    std::string splurgle;
};

int main()
{
    std::vector<X> xs(10);

    set_parameter(xs, 42, &X::foo);
    set_parameter(xs, "hello world", &X::splurgle);

    for (auto const& x : xs)
        std::cout << x.foo << ", " << x.splurgle << "\n";
}
