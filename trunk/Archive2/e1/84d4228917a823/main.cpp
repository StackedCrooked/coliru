

template <typename T>
struct Foo
{
    static void foo()
    {
        T::foo<int>();
    }
};


struct Bar
{
    template<typename T>
    static void foo()
    {
    }
};


int main()
{
    Foo<Bar>::foo();
}
