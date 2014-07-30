template <class T>
struct Base {
    int foo;
};

template <class T>
struct Derived : Base<T> {
    void bar() { foo = 0; }
};

int main()
{
    Derived<int> d;
    d.bar();
}