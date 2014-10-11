#include <type_traits>
#include <iostream>
#include <new>

template <typename T>
void destroy(T& t) { t.~T(); }

template <typename T, std::size_t N>
void destroy(T (&t)[N]) {
    for (auto i = N; i-- > 0;) {
        destroy(t[i]);
    }
}

template <typename T>
class Foo
{
public:
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type store;

    template <typename... Args>
    Foo(Args&&... args)
    {
        new (&store) T { std::forward<Args>(args)... };
    }

    void Release()
    {
        destroy(reinterpret_cast<T&>(store));
    }
};

int main() {
    struct A { ~A() { std::cout << this << "->~A()\n"; } };
    Foo<A[2][3]> c;
    c.Release();
}
