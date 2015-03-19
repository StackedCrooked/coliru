static const struct Aux
{
    template<typename F>
    struct Guard
    {
        const F& f;

        Guard(const Guard&) = delete;
    
        Guard(const F& f) : f(f) {}
        ~Guard() noexcept(noexcept(f()))
        {
            f();
        }
    };

    template<typename F>
    Guard<F> operator*(const F& f) const
    {
        return {f};
    }
} aux{};

#include <iostream>

int main()
{
    int x;
    auto&& guard1 = aux * [] { std::cout << "guard 1\n"; };
    auto&& guard2 = aux * [&] { std::cout << x << ": guard 2\n"; };
    x = 42;
    std::cout << "begin of scope\n";
}