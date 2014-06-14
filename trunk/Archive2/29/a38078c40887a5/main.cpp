template <template <int> class T>
struct B {
};

template <int N>
struct A {
    B<A> b;
};

int main()
{
    A<10> c;
    (void) c;
}