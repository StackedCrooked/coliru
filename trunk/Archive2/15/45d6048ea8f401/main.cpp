#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <memory>

int s_uid = 0;

struct Foo
{
    int m_uid = s_uid++;
    int m_data = rand() % 127 + 1;
    
    Foo() { printf("default %i(%i)\n", m_uid, m_data); }
    Foo(Foo const & rhs) : m_data(rhs.m_data) { printf("copy %i -> %i(%i)\n", rhs.m_uid, m_uid, m_data); }
    Foo(Foo&& rhs) : m_data(rhs.m_data) { rhs.m_data = 0; printf("move %i -> %i(%i)\n", rhs.m_uid, m_uid, m_data); }
    ~Foo() { printf("destructor %i(%i)\n", m_uid, m_data); }
};

void func(Foo a)
{
    Foo b = std::move(a);
}

int main()
{
    Foo foo;
    
    puts("\nfunc(foo);");
    func(foo);
    
    puts("\nfunc(std::move(foo));");
    func(std::move(foo));
    
    puts("\nfunc(Foo());");
    func(Foo());
    
    puts("\nlambda copy");
    {
        Foo foo2;
        ([foo2]() { func(std::move(foo2)); })();
    }
    
    puts("\nlambda move");
    {
        Foo foo2;
        ([f = std::move(foo2)]() { func(std::move(f)); })();
    }
    
    puts("\nmutable lambda move");
    {
        Foo foo2;
        ([f = std::move(foo2)]() mutable { func(std::move(f)); })();
    }
    
    
    return 0;
}
