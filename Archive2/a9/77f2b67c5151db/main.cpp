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
    A* a = nullptr;
    a->foo();
    
    return 0;
}
