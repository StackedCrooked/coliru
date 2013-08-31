#include <array>
#include <map>
#include <utility>
#include <memory>
#include <stdexcept>
#include <iostream>

struct MyStruct
{
    std::array<int, 2> a;
    std::array<int, 2> b;
};

template <class T, class U>
std::pair<U, T> get_reversed_pair(const std::pair<T, U>& p)
{
    return std::make_pair(p.second, p.first);
}

int main()
{
    std::map<std::pair<int, int>, std::shared_ptr<MyStruct>> m
    {
        {
            {12, 16},
            std::make_shared<MyStruct>()
        },
        {
            {16, 12},
            std::make_shared<MyStruct>()
        }
    };

    std::size_t count = 1;

    for(const auto& p: m)
    {
        try
        {
            auto f = m.at(get_reversed_pair(p.first));
            f -> a.at(0) = count++;
            f -> b.at(0) = count++;
        }
        catch(std::out_of_range& e)
        {

        }
    }

    for(auto& p: m)
    {
        try
        {
            auto& f = m.at(get_reversed_pair(p.first));
            std::swap(f, p.second);
            break;
        }
        catch(std::out_of_range& e)
        {

        }
    }

    for(const auto& p: m)
    {
        std::cout << p.first.first << ' ' << p.first.second << " - ";
        std::cout << p.second -> a.at(0) << ' ' << p.second -> b.at(0) << std::endl;
    }

    return 0;
}
    