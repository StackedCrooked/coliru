template<class T>
struct decompose;

template<class Func, class... Args>
struct decompose<Func(Args...)>
{
    constexpr static int n = sizeof...(Args);
};

template<class T>
int deduce(T&& t)
{
    return decompose<T()>::n;
}

int main()
{
    deduce([](){});
}
