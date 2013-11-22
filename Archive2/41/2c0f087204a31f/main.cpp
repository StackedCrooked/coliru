template<typename T>
struct Foo
{
    template<typename> struct impl;
    T x;
};

template<typename T>
template<typename U>
struct Foo<T>::impl
{
    impl();
    U x;
    T y;
};

template<typename> void type_is();

template<typename T>
template<typename U>
Foo<T>::impl<U>::impl()
{
    type_is<T>();
    type_is<U>();
    type_is<decltype(x)>();
    type_is<decltype(y)>();
}

int main()
{
    Foo<int>::impl<double>{};
}