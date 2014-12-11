#include <iostream>
#include <type_traits>

template<typename T>
struct Foo
{
    template<typename U = T>
    operator typename std::enable_if<!std::is_class<U>::value, U >::type () const
    {
        return _val;
    }

    template<typename U = T>
    operator typename std::enable_if< std::is_class<U>::value, const U&>::type () const
    {
        return _val;
    }

    T _val;
};

int main()
{
    Foo<double> f1;
    f1._val = 0.3;

    double d = f1;
    std::cout << d << std::endl;
    return 0;
}
