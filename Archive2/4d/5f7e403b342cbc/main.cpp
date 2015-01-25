#include <iostream>
#include <tuple>

class T
{
    public:
        using Names = std::tuple<char const*, char const*>;
        static constexpr Names names {"First", "Second"};
};

constexpr T::Names T::names;

int main()
{
    std::cout << std::get<0>(T::names);
}