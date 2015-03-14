#include <iostream>
#include <vector>

struct Foo
{
    int x, y;
};

int main()
{
    Foo f = {1,2};
    std::cout << f.x << ',' << f.y << '\n';
    
    std::vector<Foo> v;
    v.emplace_back(f);
    std::cout << f.x << ',' << f.y << '\n';
}