template <typename T>
struct Delegate;

template <typename R, typename... Args> // partial specialization for non-empty Args
struct Delegate<R(Args...)>
{   
    R operator()(Args...) { return {}; }
};

template <typename R> // partial specialization for empty Args
struct Delegate<R()>
{
    R operator()() { return {}; }
};

int main()
{
    Delegate<int(int)> a;
    Delegate<int()> b;
    a(1);
    b();
}
