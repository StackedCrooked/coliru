#include <array>

template<int I>
struct foo
{
    constexpr foo(int i) : value(i)
    {
    }
    
    int value;
};

template<int I>
struct caller
{
    constexpr caller() {}
    
    constexpr foo<I> operator()(int i)
    {
        return foo<I>(i);
    }
};

template<char...>
constexpr auto operator "" _int()
{
    return caller<0>{};
}

int main()
{
    std::array<int, 123_int(4).value> arr;
}
