template <typename D, typename T>
struct Base;

template <typename D, typename R, typename... Args>
struct Base<D, R(Args...)>
{
    R operator()(Args...)
    {
        D* that = static_cast<D*>(this);
        return {};
    }
};

template <typename D, typename R>
struct Base<D, R()>
{
    R operator()()
    {
        D* that = static_cast<D*>(this);
        return {};
    }
};

template <typename T>
class Delegate;

template <typename R, typename... Args>
class Delegate<R(Args...)> : public Base<Delegate<R(Args...)>, R(Args...)>
{
    
};

int main()
{
    Delegate<int(int)> a;
    Delegate<int()> b;
    a(1);
    b();
}
