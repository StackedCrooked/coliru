#include <iostream>
#include <array>
#include <utility>

struct Bar
{
    int data;
};

struct Foo
{
    std::size_t index;
    Bar bar;
};

template <std::size_t... indices>
constexpr std::array<Foo, sizeof...(indices)>
CreateArrayOfFoo(const Bar& bar, std::index_sequence<indices...>)
{
    return {{{indices, bar}...}};
}

template <std::size_t N>
constexpr std::array<Foo, N> CreateArrayOfFoo(const Bar& bar)
{
    return CreateArrayOfFoo(bar, std::make_index_sequence<N>());
}

int main()
{
    constexpr Bar bar{1};
    constexpr std::size_t n_foos = 8;
    constexpr auto foos = CreateArrayOfFoo<n_foos>(bar);
    
    for (const Foo& foo : foos)
    {
        std::cout << foo.index << " " << foo.bar.data << std::endl;
    }
}