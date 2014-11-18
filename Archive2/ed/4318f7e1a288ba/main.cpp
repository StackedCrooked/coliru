#include <type_traits>

template <typename T>
struct Delegate;

template <typename R, typename... Args>
struct Delegate<R(Args...)>
{
    template <typename T = R>
    typename std::enable_if<sizeof...(Args) != 0 && std::is_same<T,R>{}, R>::type
    operator()(Args...) { return {}; }

    template <typename T = R>
    typename std::enable_if<sizeof...(Args) == 0 && std::is_same<T,R>{}, R>::type
    operator()() { return {}; }
};

int main()
{
    Delegate<int(int)> a;
    Delegate<int()> b;
    a(1);
    b();
}
