#include <functional>

template <typename... Fs> struct Overload;

template <> struct Overload<> {
    void operator()() const {}
};

template <typename F, typename... Fs>
   struct Overload<F, Fs...> : Overload<Fs...>
{
    using Overload<Fs...>::operator();

    Overload(F&& f, Fs&&... fs) :  
        Overload<Fs...>(std::forward<Fs>(fs)...),
        _f(std::forward<F>(f))
    {
    }

    template <typename... Args>
    auto operator()(Args&&... args) const 
    -> decltype(std::declval<F>()(std::forward<Args>(args)...)) {
        return _f(std::forward<Args>(args)...);
    }

  private:
    F _f;
};

template <typename... Fs>
   Overload<Fs...> make_overload(Fs&&... fs)
{
    return { std::forward<Fs>(fs)... };
}

#include <string>
#include <iostream>

int main()
{
    auto overload = make_overload(
        [](int i)          { return '[' + std::to_string(i) + ']'; },
        [](std::string s)  { return '[' + s + ']'; }
        );

    std::cout << overload(42)              << "\n";
    std::cout << overload("yay for c++11") << "\n";
}
