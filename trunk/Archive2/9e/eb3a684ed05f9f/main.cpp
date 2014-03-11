#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Base{};
struct Derived : public Base{};

template<typename T>
struct Foo {};

using namespace std;


int main()
{
    shared_ptr<Foo<Base>> p (new Foo<Derived>());
    
    return 0;
}
