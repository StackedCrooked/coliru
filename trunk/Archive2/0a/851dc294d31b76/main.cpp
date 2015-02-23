#include <utility>

template<typename... Bases>
struct overload: Bases... {
    overload(Bases... bases): Bases { std::move(bases) }... {}
    
    template<typename... Args>
    auto operator()(Args&&... args)
    -> decltype( this->operator()(std::forward<Args>(args)...) )
    { return this->operator()(std::forward<Args>(args)...); }
};

template<typename... Fs>
overload<Fs...> make_overload(Fs... fs) { return { std::move(fs)... }; }

int main()
{
    auto f = make_overload([](int i) { return i; }, [](const char* p) { return p; });
    f(1);
}
