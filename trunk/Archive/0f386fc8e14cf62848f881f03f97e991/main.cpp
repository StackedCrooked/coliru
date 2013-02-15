#include <type_traits>

template<typename Func>
typename std::result_of<Func&()>::type foo(Func f)
{ return f(); }

template<typename Func>
typename std::result_of<Func&(int)>::type foo(Func f)
{ return f(42); }

int main()
{
    foo([](int) {})(42);
}