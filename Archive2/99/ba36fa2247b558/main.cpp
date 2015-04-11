#include <iostream>
#include <vector>

struct only_movable
{
    only_movable() = default;
    only_movable(only_movable const&) = delete;
    only_movable(only_movable     &&) = default;
    only_movable & operator = (only_movable const&) = delete;
    only_movable & operator = (only_movable     &&) = default;
};

struct foo : only_movable {};

int main()
{
    std::vector<foo> bar;
    for(int n = 0; n < 10000; ++n)
        bar.emplace_back();
    std::cout << bar.size() << '\n';
}
