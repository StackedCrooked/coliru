#include <iostream>
#include <vector>

struct foo { int i; };

std::vector<foo*> search(foo* arr, std::size_t num)
{
    std::vector<foo*> result;
    for(foo* cur = arr; cur != arr + num; ++ cur)
        if(cur->i % 2 == 0)
            result.push_back(cur);
    return result;
}

int main()
{
    foo val[] = { {1}, {2}, {3}, {4}, {5}, {6}, {7}, };
    std::size_t num = sizeof val / sizeof *val;
    auto res = search(val, num);
    std::cout << res.size() << '\n';
    for(const auto& i: res)
        std::cout << i->i << ' ';
}