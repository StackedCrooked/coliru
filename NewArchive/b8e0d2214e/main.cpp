#include <memory>
#include <iostream>
#include <utility>

struct foo
{
    std::unique_ptr<int> a;
};

int main()
{
    foo a = { std::unique_ptr<int>(new int(42)) };
    std::cout << *a.a << std::endl;
    
    foo b = std::move(a);
    std::cout << *b.a << std::endl;
    
    std::swap(a, b);
    std::cout << *a.a << std::endl;
}
