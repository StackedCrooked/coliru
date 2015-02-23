#include <utility>

template<typename... Bases>
struct overload: Bases... {
    overload(Bases... bases): Bases { std::move(bases) }... {}
};

template<typename... Fs>
overload<Fs...> make_overload(Fs... fs) { return { std::move(fs)... }; }

int main()
{
    auto f = make_overload([](int i) { return i; }, [](long l) { return l; });
    f(1);
}
