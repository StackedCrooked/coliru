template<typename> struct foo {};

template<typename>
struct bar {
    template<typename> void foo() const {}
};

template<typename T>
void qux(bar<T> b)
{ b.template foo<void>(); }

int main()
{
    bar<void> b;
    qux(b);
}