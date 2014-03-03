template <class A, class B>
class Foo
{
public:
    template <class T>
    Foo(T* self, void (T::*mem)(A,B))
    {}
};

class Bar
{
public:
    void foo(int a, int b);
};

template <class T, class A, class B>
Foo<A,B> make(T* self, void (T::*mem)(A,B))
{
    return Foo<A,B>(self, mem);
}

int main(void)
{
    Bar b;
    auto blah = make(&b, &Bar::foo);
    return 0;
}
