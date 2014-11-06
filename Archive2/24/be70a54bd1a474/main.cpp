#include <iostream>
#include <type_traits>

template <typename Ret, typename Arg>
struct get_arg
{
    using value = Arg;
    get_arg(Ret (*func)(Arg))
    {
    }
};

template <class B>
class A
{
public:
   void Foo(B& b)
   {
       float value = 0.f;
       static_assert(std::is_same<get_arg(std::declval<B>.Bar(value))::value, decltype(value)>::value, "");
       b.Bar(0);
   }
};

class B
{
public:
    void Bar(float) {std::cout<<__PRETTY_FUNCTION__;}
    void Bar(int) {std::cout<<__PRETTY_FUNCTION__;}
    void Bar(double) {std::cout<<__PRETTY_FUNCTION__;}
};

int main()
{
    B b;
    A<B> a;
    a.Foo(b);
}