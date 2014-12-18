#include <iostream>

template<class Class,typename Type,Type Class::*PtrToMember>
struct multi_index
{
    multi_index(Class& c)
    {
        (c.*PtrToMember) = 42;
    }
};

struct Foo {
  struct Bar {
    int qux = 0;
  } bar1, bar2;
};

#include <iostream>

int main()
{
    Foo f;
    multi_index<Foo::Bar, int, &Foo::Bar::qux> m(f.bar1);
    
    std::cout << f.bar1.qux << '\n';
    std::cout << f.bar2.qux << '\n';
}
