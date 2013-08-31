#include <cstdio>

#define show(s) printf("%s : %s\n", s, __PRETTY_FUNCTION__)

namespace op
{
    template<class A, class B> auto foo(A a, B b) -> decltype(a+b) { show("good"); return a+b; }
    int foo(...) { show("fail"); return 0; }
}

template<class A, class B> struct Eval
{
    void foo(A a, B b) const { op::foo(a,b); }
};

int main()
{
    Eval<int,void*> eiv; eiv.foo(0,0);
    Eval<int,char*> eic; eic.foo(0,0);
    Eval<char*,char*> ecc; ecc.foo(0,0);
}
