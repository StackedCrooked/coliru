#include <iostream>
#include <cstddef>

template <typename T, std::size_t... Sizes>
class Foo {
public:
     const std::size_t    rank = sizeof...(Sizes);
     const std::size_t    dimensions[sizeof...(Sizes)] = { Sizes... };
};

int main()
{
    Foo<int, 1, 2, 3> foo;

    std::cout << "Rank: " << foo.rank << std::endl;

    return 0;
}
