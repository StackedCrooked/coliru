#include<functional>
#include<iostream>
#include<type_traits>

template <class H, class... Tail> struct callable : callable<H>, callable<Tail...>
{
    callable(H h, Tail... tail) : callable<H>(h), callable<Tail...>(tail...) {}
    using callable<H>::operator();
    using callable<Tail...>::operator();
};

template <class H> struct callable<H> : H
{
    callable(H h) : H(h) {}
    using H::operator();
};


template <class... Fs> struct overload_set : callable<Fs...>
{
    overload_set(Fs... fs) : callable<Fs...>(fs...) {}
    
    using callable<Fs...>::operator();
};

template<class... Fs>
auto make_overload_set(Fs&&... fs) { return overload_set<std::remove_reference_t<Fs>...>(std::forward<Fs>(fs)...); }

int main() {
    
    auto o = make_overload_set([](int i) { std::cout << "int" << std::endl; },
                               [](long i) { std::cout << "bool" << std::endl; });
    
    o(3);
    o(2l);
return 0;
}