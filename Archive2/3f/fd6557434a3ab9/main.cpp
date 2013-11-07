#include <utility>

template<class T>
struct foo_argument
{
    template<class Ret, class C, class Arg>
    static Arg test(Ret (C::*)(Arg));

    using type = decltype(test(&T::template foo<>));
};

template<class T, class D>
struct dependent { typedef T type; };

template<class T, class D>
using Dependent = typename dependent<T, D>::type;

template<class T>
struct base
{
    friend struct foo_argument<T>;

    template<class Ignore = void>
    auto foo(int i) -> decltype(std::declval<Dependent<T&, Ignore>>().foo_impl(i))
    {
        return static_cast<T&>(*this).foo_impl(i);
    }
};

struct derived : base<derived>
{
    friend struct base<derived>;
    //friend struct foo_argument<derived>;
  private:
    int foo_impl(int i)
    {
        return 123 + i;
    }
};

int main()
{
    using foo_arg_type = foo_argument<derived>::type;
}