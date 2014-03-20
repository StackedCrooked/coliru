#include <vector>
#include <iostream>

struct Point {int x; int y;};

struct Foo
{
    static std::vector<Point> vec[3];
};

std::vector<Point> Foo::vec[3] = {
    {{1,2}, {3,4}},
    {{0,0}},
    {}
};

int main()
{
    for(auto const& f : Foo::vec) {
        std::cout << f.size() << ' ';
    }
    std::cout << '\n';
}
