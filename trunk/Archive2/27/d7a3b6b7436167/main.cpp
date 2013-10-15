#include <iostream>
#include <utility>

template<typename F, typename... Fs>
class composition {
private:
    F f;
    composition<Fs...> fs;

public:
    explicit composition(F f_, Fs... fs_) : f(std::move(f_)), fs(std::move(fs_)...) { }

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(f(fs(std::forward<Args>(args)...))) {
        return f(fs(std::forward<Args>(args)...));
    }
};

template<typename F>
class composition<F> {
private:
    F f;

public:
    explicit composition(F f_) : f(std::move(f_)) { }

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(f(std::forward<Args>(args)...)) {
        return f(std::forward<Args>(args)...);
    }
};

template<typename... Fs>
composition<Fs...> compose(Fs... fs) {
    return composition<Fs...>(std::move(fs)...);
}

int main() {
    auto f = compose([] (int x) { return x * 2; }, [] (int x) { return x + 2; });

    std::cout << f(42) << '\n';
    return 0;
}
