#include <iostream>
#include <type_traits>
#include <vector>

struct A
{
    void boo() const { std::cout << "boo." << std::endl; }
};

struct B {};

template<bool> struct booable;

template<>
struct booable<true> {

    template<typename Type>
    static void booIt(Type const & t)
    {
        t.boo();
    }
};

template<>
struct booable<false> {

    template<typename Type>
    static void booIt(Type const & t)
    {
        std::cout << "booing a non-booable type" << std::endl;
    }
};


template<typename T>
constexpr auto is_booable(int) -> decltype(std::declval<T>().boo(), bool())
{
    return true;
}

template<typename T>
constexpr bool is_booable(...)
{
    return false;
}


template<typename Type>
void alg(Type const& t)
{
    booable< is_booable<Type>(0) >::booIt(t);
}

int main(int argc, const char *argv[])
{
    A a;
    B b;

    alg(a);
    alg(b);

    return 0;
}