template<class T>
struct bar
{
    T m;
};

template<class T, class U>
int foo(bar<T>, bar<U>)
{
    return 42;
}

template<class T, class U>
auto foo(U p0, bar<T> p1)// -> decltype(foo(p1, p0))
{
    return foo(p1, p0);
}

int main()
{
    bar<int> b;
    foo(b, b);
}