#include <iostream>

/** Exposition **/

template <typename...Ts>
class Self;

template <typename X, typename...Ts>
class Self<X,Ts...> : public Ts...
{
public:
    typedef X self;
};

#define WITH_SELF(X) X : public Self<X>
#define WITH_SELF_DERIVED(X,...) X : public Self<X,__VA_ARGS__>

/****************/



struct WITH_SELF(Foo)
{
    void foo(self& other)
    {
        other.bar();
    }
    
    virtual void bar()
    {
        std::cout << ":)\n";
    }
};

struct WITH_SELF_DERIVED(Bar, Foo)
{
    void bar()
    {
        std::cout << ":D\n";
    }
};

int main()
{
    Foo::self foo;
    foo.foo(foo);
    
    Bar::self bar;
    bar.foo(foo);
    bar.foo(bar);
}
