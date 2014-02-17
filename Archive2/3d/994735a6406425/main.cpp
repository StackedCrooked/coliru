#include <memory>
#include <iostream>
 
struct Foo {
    Foo() { std::cout << "Foo\n"; }
    ~Foo() { std::cout << "~Foo\n"; }
};
 
int main()
{
    std::cout << "Creating new Foo...\n";
    std::unique_ptr<Foo> up(new Foo());
 
    std::cout << "About to release Foo...\n";
    Foo* fp = up.release();
 
    if (up.get() == nullptr)
        std::cout << "Foo is no longer owned by unique_ptr...\n";
 
    delete fp;
}