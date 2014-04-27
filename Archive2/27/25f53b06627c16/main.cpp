#include <memory>
#include <vector>

class Foo { };

class MyClass
{
    MyClass(std::vector<std::unique_ptr<Foo>> foos = std::vector<std::unique_ptr<Foo>>()) :
        foos_(std::move(foos))
    {};
    
    std::vector<std::unique_ptr<Foo>> foos_;
};

int main()
{
    
}