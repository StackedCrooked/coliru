#include <iostream>
#include <memory>
 
struct Foo {
    Foo() { std::cout << "Foo\n"; }
    ~Foo() { std::cout << "~Foo\n"; }
};
 
int main() 
{
    std::unique_ptr<Foo> p1;
 
    {
        std::cout << "Creating new Foo...\n";
        std::unique_ptr<Foo> p2(new Foo);
        // p1 = p2; // Error ! can't copy unique_ptr
       // p1 = std::move(p2);
        const p1& = &p2;
        std::cout << "About to leave inner block...\n";
 
        // Foo instance will continue to live, 
        // despite p2 going out of scope
    }
 
    std::cout << "About to leave program...\n";
}