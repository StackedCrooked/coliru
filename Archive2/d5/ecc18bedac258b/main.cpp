#include <iostream>

struct Foo
{
    Foo()                       { std::cout << "DEFAULT\n"; }
    Foo(Foo &&)                 { std::cout << "FOO MOVE CTOR\n"; }
    Foo(Foo const &)            { std::cout << "FOO CONST COPY CTOR\n"; }
    Foo& operator=(Foo &&)      { std::cout << "FOO MOVE ASSIGN\n"; return *this;}
    Foo& operator=(Foo &)       { std::cout << "FOO COPY ASSIGN\n"; return *this;}
    Foo& operator=(Foo const &) { std::cout << "FOO CONST COPY ASSIGN\n"; return *this;}
};


void func(Foo f)
{
    (void)f;   
}



int main(void) 
{ 
    Foo f{};
    // ^ should be DEFAULT
    func(f);
    
}