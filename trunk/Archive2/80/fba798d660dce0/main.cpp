#include <memory>
#include <iostream>
 
struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
 
struct D { 
    void operator()(Foo* p) const {
        std::cout << "Call delete for Foo object...\n";
        delete p;
    }
};
 
int main()
{
    {
        std::cout << "constructor with no managed object\n";
        std::shared_ptr<Foo> sh1;
    }
 
    {
        std::cout << "constructor with object\n";
        Foo *f =new Foo;
        std::shared_ptr<Foo> sh2(f);
        std::shared_ptr<Foo> sh3(f);
        std::cout << sh2.use_count() << '\n';
        std::cout << sh3.use_count() << '\n';
    }
 
    {
        std::cout << "constructor with object and deleter\n";
        std::shared_ptr<Foo> sh4(new Foo, D());
    }
}