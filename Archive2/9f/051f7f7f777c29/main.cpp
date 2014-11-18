template <typename T>
struct Impl;

template <typename R, typename... Args>
struct Impl<R(Args...)>
{
    static R call(Args...) { return {}; }
};

template <typename R>
struct Impl<R()>
{
    static R call() { return {}; }
};

template <typename T>
struct Delegate;

template <typename R, typename... Args>
struct Delegate<R(Args...)>
{
    R operator()(Args... args)
    {
        return Impl<R(Args...)>::call(args...);
    }
};

int main()
{
    Delegate<int(int)> a;
    Delegate<int()> b;
    a(1);
    b();
}
