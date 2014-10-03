#include <iostream>
#include <memory>
 
struct Foo {
    Foo(const std::string& name) { this->name = name; std::cout << "Foo: "<<name<<"\n"; }
    ~Foo() { std::cout << "~Foo "<<name<<"\n"; }
    std::string name;
};
 
int main() 
{
    std::unique_ptr<Foo> p1(new Foo("1"));
 
    {
        std::cout << "Creating new Foo...\n";
        p1 = std::unique_ptr<Foo>(new Foo("2"));
        //std::unique_ptr<Foo> p2(new Foo("2"));
         //p1 = p2; // Error ! can't copy unique_ptr
        //p1 = std::move(p2);
        std::cout << "About to leave inner block...\n";
 
        // Foo instance will continue to live, 
        // despite p2 going out of scope
    }
 
    std::cout << "About to leave program...\n";
}