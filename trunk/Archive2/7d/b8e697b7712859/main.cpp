    struct Foo {
         enum { bar };
         explicit Foo(int){}
    };

    struct Baz { explicit Baz(Foo){} };

    Baz b(Foo(Foo::bar)); // #1
    
    int main(){}