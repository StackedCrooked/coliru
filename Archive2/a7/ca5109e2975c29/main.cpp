template<class F>
struct return_type_t;

template<class R, class C, class... Args>
struct return_type_t<R (C::*)(Args...)>
{
    using type = R;
};

template<class F>
using return_type = typename return_type_t<F>::type;

class A
{
public:
    int foo() {return 1;}
    void goo( return_type<decltype(&A::foo)> i) {}
};

int main()
{
    A a;
    a.goo( a.foo() );
}