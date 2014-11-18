template <typename T>
class Delegate;

template <typename T>
struct Base;

template <typename R, typename... Args>
struct Base<Delegate<R(Args...)>>
{
    R operator()(Args...)
    {
        Delegate<R(Args...)>* that = static_cast<Delegate<R(Args...)>*>(this);
        return {};
    }
};

template <typename R>
struct Base<Delegate<R()>>
{
    R operator()()
    {
        Delegate<R()>* that = static_cast<Delegate<R()>*>(this);
        return {};
    }
};

template <typename R, typename... Args>
class Delegate<R(Args...)> : public Base<Delegate<R(Args...)>>
{
    friend struct Base<Delegate<R(Args...)>>;
};

int main()
{
    Delegate<int(int)> a;
    Delegate<int()> b;
    a(1);
    b();
}
