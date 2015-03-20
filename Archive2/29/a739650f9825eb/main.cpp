#include <iostream>
#include <vector>

struct Foo 
{ 
    std::vector<void *> v;
    
    // send init list to vect
    Foo(std::initializer_list<void *> init) :
        v(init)
    { }
};

struct Bar
{
    Foo * f;

    // forward args to create f
    template<typename... Ts>
        Bar(Ts &&... ts)
        { 
            f = new Foo{std::forward<Ts>(ts)...};
        }
};

int main(void)
{
    int x=0 , y=1 , z=2 , a=3;

    Foo{{&x, &y}};
    Bar{{&z, &a}};
}
