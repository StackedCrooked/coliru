#include <memory>
#include <iostream>
 
class Foo {
    public:
    std::string name;
    Foo(std::string name) { std::cout << "Foo() " + name + "\n"; }
    ~Foo() { std::cout << "~Foo()" + name + "\n"; }
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
        std::shared_ptr<Foo> sh2(new Foo("sh2"));
        std::cout << "Use count of sh2 = " << sh2.use_count() << '\n';

        std::shared_ptr<Foo> sh3(sh2);
        std::cout << "Use count of sh3 = " << sh3.use_count() << '\n';
    }
 
    {
        std::cout << "constructor with object and deleter\n";
        std::shared_ptr<Foo> sh4(new Foo("sh4"), D());
    }
}