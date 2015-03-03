#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Foo
{
    std::vector<Foo *>  children;
    
    Foo (std::shared_ptr<Foo> parent = nullptr)
    {
        children.reserve(10);
        if (parent) parent->children.push_back(this);
    }
    
};


int main()
{
    Foo f1{};
    Foo f2{std::make_shared<Foo>(f1)};
    
    // should print 1?
    std::cout << f1.children.size() << std::endl;
}
