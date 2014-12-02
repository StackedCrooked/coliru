#include <iostream>
#include <memory>

struct Foo
{
    int x;
    int y;
};

int main()
{
    std::shared_ptr<Foo> p = std::make_shared<Foo>();
    std::cout << p.get() << std::endl;
    p.reset();
    std::cout << p.get() << std::endl;
    
    return 0;
}