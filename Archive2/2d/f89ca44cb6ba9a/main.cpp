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
    U x;
    T y;
};

template<typename> void type_is();

int main()
{
    type_is<decltype( Foo<int>{}.x )>();
    type_is<decltype( Foo<int>::impl<double>{}.x )>();
    type_is<decltype( Foo<int>::impl<double>{}.y )>();
}