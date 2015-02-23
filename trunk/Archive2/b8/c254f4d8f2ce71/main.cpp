template<typename... Fs> 
struct overloaded;

template<typename F, typename... Fs>
struct overloaded<F, Fs...> : public F, public overloaded<Fs...>::type {
public:
    using type = overloaded;
public:
    overloaded(F head, Fs... tail) 
        : F{head}
        , overloaded<Fs...>::type{tail...} { 
    }
    using F::operator ();
    using overloaded<Fs...>::type::operator ();
};

template<typename F>
struct overloaded<F> : F {
public:
    using type = F;
public:
    overloaded(F head) 
        : F{head} { 
    }
    using F::operator ();
};

template<typename... Fs>
typename overloaded<Fs...>::type make_overload_set(Fs... fs) { 
    return overloaded<Fs...>(fs...); 
}

#include <iostream>

int main() {
    auto f = make_overload_set([](int i) { return i; }, 
                               [](const char* p) { return p; });
    std::cout << f(42);    
}