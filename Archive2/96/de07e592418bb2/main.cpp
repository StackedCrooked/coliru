    struct bar;    
    
    struct foo
    {
    int bar::* p;
    };
     
    struct bar
    {
    foo aFoo;
    int i;
    };
     
    int main()
    {
    int bar::*foo::*ptr = &foo::p;
    return 0;
    }