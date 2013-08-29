#include <cstdio>

#define show(s) printf("%s : %s\n", s, __PRETTY_FUNCTION__)

template<class A, class B>
struct Eval
{
    void foo(A a, B b) { bar<A,B>(a,b, 0); }
    
    template<typename T, typename U>
    auto bar(T a, U b, decltype(a+b)*) -> decltype(a+b)
    {
        show("good"); return a+b;
    }
    template<typename T, typename U>
    int  bar(T a, U b, ...)
    {
        show("bad");
        return 0;
    }
};

int main()
{
    Eval<int,void*> eiv;
    eiv.foo(0,0);
}