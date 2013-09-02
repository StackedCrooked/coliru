template < typename T >
struct S
{
    template < typename U >
    void foo() {}
};

template < typename T > template<>
void S<T>::foo<int>()
{
}

int main()
{
    S<double> s;
    s.foo<int>();
}
