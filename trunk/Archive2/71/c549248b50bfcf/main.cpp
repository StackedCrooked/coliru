#include <iostream>
 
struct w0
{
    int bar;
};

struct w1
{
    template<class T>
    struct bar
    {
        explicit bar(int) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    };
};

struct foo
{
    template<class U>
    friend bool operator<(U, foo) { std::cout << __PRETTY_FUNCTION__ << "\n"; return true; }
};
 
template<class B>
struct gadget : B
{
    void a() { auto x = B::bar<foo()>(5); (void)x; }
    void b() { auto x = typename B::template bar<foo()>(5); (void)x; }
};
 
int main()
{
    gadget<w0>().a();
    gadget<w1>().b();
}