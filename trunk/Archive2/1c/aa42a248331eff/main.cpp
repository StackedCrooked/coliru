#include <iostream>
#include <memory>
 
struct Foo {
    Foo() { std::cout << "Foo::Foo\n"; }
    ~Foo() { std::cout << "Foo::~Foo\n"; }
    void bar() { std::cout << "Foo::bar\n"; }
};
 
void f(const Foo &foo)
{
    std::cout << "f(const Foo&)\n";
}
 
int main()
{
    std::unique_ptr<Foo> p1(new Foo);  // p1 владеет Foo
    if (p1) p1->bar();
 
    {
        std::unique_ptr<Foo> p2(std::move(p1));  // теперь p2 владеет Foo
        f(*p2);
 
        p1 = std::move(p2);  // владение возвращено p1
        std::cout << "destroying p2...\n";
    }
 
    if (p1) p1->bar();
 
    // экземпляр Foo уничтожен, когда p1 покидает область видимости
}