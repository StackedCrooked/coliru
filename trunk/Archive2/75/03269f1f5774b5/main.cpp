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
    auto f1 = std::make_shared<Foo>();
    Foo f2{f1};
    
    // should print 1?
    std::cout << f1->children.size() << std::endl;
}
