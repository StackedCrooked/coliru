#include <functional>
#include <iostream>
#include <type_traits>

void hook()
{
    std::cout << "Called\n";
}

template <typename Fun>
struct hooked {
public:
    explicit hooked(Fun const& fun) : fun(fun) {}
    explicit hooked(Fun&& fun) : fun(std::move(fun)) {}

    template <typename... Args>
    std::result_of<Fun const&(Args...)> operator()(Args&&... args) const {
        hook();
        return fun(std::forward<Args>(args)...);
    }
    template <typename... Args>
    typename std::result_of<Fun&(Args...)>::type operator()(Args&&... args) {
        hook();
        return fun(std::forward<Args>(args)...);
    }

private:
    Fun fun;
};

template <typename Fun>
hooked<typename std::decay<Fun>::type> wrap(Fun&& fun) {
    return hooked<typename std::decay<Fun>::type>(std::forward<Fun>(fun));
}

int main()
{
    auto cb = [](int a, int b){ std::cout << a << " " << b << "\n"; };
    auto wrap_cb = wrap(cb);
    wrap_cb(1, 2);
}