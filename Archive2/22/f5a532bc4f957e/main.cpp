#include <vector>
#include <iostream>

struct Foo {};

int main(int, char *[])
{
    std::vector<Foo*> v;
    v.reserve(100000);
    std::cout << v.capacity() << '\n';
    
    std::vector<Foo*>{v.begin(), v.end()}.swap(v);
    std::cout << v.capacity() << '\n';
}