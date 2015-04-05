#include <iostream>
#include <vector>

struct Foo // aggregate
{
    int x, y;
};

int main()
{
    std::vector<Foo> v;
    v.push_back({1,2});
    v.emplace_back(3, 4); // fails
}
