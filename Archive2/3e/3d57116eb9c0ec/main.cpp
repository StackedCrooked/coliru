#include <iostream>

struct Foo
{
    Foo()                       { std::cout << "DEFAULT CTOR\n"; }
    Foo(Foo &&)                 { std::cout << "FOO MOVE CTOR\n"; }
    Foo(Foo const &)            { std::cout << "FOO CONST COPY CTOR\n"; }
    Foo& operator=(Foo &&)      { std::cout << "FOO MOVE ASSIGN\n"; return *this;}
    Foo& operator=(Foo const &) { std::cout << "FOO CONST COPY ASSIGN\n"; return *this;}
    
    int x = 0; // nsdmi
};


namespace
{
    Foo f{};
}


Foo const & getFoo()
{ return f; }




int main(void)
{
    auto & ff = getFoo();
    printf("%p\n%p\n", &ff, &f); 
}