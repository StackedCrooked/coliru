#include <iostream>
#include <memory>
#include <functional>
 
struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n\n"; }
};
 
int main()
{
    Foo* foo = new Foo();
    std::unique_ptr<Foo> up(foo);
 
    std::cout << "hash(up):  " << std::hash<std::unique_ptr<Foo>>()(up) << '\n';
    std::cout << "hash(foo): " << std::hash<Foo*>()(foo) << '\n';
}