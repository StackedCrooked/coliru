template<class T>
class MyClass;

template<class T0, class T1> auto
operator+(MyClass<T0> const& a, MyClass<T1> const& b);

template<class T>
class MyClass {
    public:
        MyClass(T const& a) : impl(a) {}

        template<class T0, class T1> friend auto
        ::operator+(MyClass<T0> const& a, MyClass<T1> const& b);

        T getImpl() const { return impl; }
    private:
        T impl;
};

template<class T0, class T1> auto
operator+(MyClass<T0> const& a, MyClass<T1> const& b)
{
    return MyClass<decltype(a.impl+b.impl)>{a.impl + b.impl};
}

int main()
{
    auto x = MyClass<int>(42);
    auto y = x;
    auto z = x + y;
}