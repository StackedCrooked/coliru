#include <utility>


template<typename T>
struct Foo
{
    template<typename ...Args>
    Foo(Args&& ...args) : inner_object_(std::forward<Args>(args)...) {}
    
    T inner_object_;
};


struct Bar
{
    Bar(int n, float f) : n_(n), f_(f) {}
    
    int n_;
    float f_;
};


int main()
{
    Foo<Bar> f(1, 2.3);
}

