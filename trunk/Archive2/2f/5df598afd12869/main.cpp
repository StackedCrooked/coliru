template<class... Fs> struct overloaded;

template<class F1, class... Fs>
struct overloaded<F1, Fs...> : F1, overloaded<Fs...>::type
{
    using type = overloaded;
    overloaded(F1 head, Fs... tail) : F1(head), overloaded<Fs...>::type(tail...) { }
    using F1::operator ();
    using F1::operator = ;
    using overloaded<Fs...>::type::operator ();
    using overloaded<Fs...>::type::operator =;
};

template<class F>
struct overloaded<F> : F
{
    using type = F;
    using F::operator ();
    using F::operator =;
};

template<class... Fs>
typename overloaded<Fs...>::type overload(Fs... fs)
{ return overloaded<Fs...>(fs...); }

#include <iostream>
#include <string>

int main()
{
    auto f = overload([] (int x) { return x + 1; },
                      [] (char const* y) { return std::string{y} + "!"; },
                      [] (double y) { return y * 2; });

    std::cout << f(0) << std::endl;
    std::cout << f("Hello") << std::endl;
    std::cout << f(3.14) << std::endl;
}
