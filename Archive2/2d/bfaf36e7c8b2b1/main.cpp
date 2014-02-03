#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct A {
    void foo() {
        std::cout << "foo()" << std::endl;
    }
};

int main()
{
    std::vector<std::unique_ptr<A>> v;
    auto a = std::unique_ptr<A>(new A());
    
    v.push_back(std::move(a));
    a->foo();
    
    return 0;
}
