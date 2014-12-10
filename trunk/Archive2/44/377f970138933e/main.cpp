



struct Foo
{ 
    Foo() {}
    void foo() && {}
    void foo() volatile && {}
    void foo() const && {}
    void foo() const volatile && {}
    
    void foo() & {}
    void foo() volatile & {}
    void foo() const &  {}
    void foo() const volatile & {}
};


int main()
{
    const volatile Foo foo;
    foo.foo();
    foo.foo();
}