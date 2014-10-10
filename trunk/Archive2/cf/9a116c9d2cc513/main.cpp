#include <type_traits>
#include <iostream>

template <typename T>
struct Foo
{
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type store;

    template <typename... Args>
    Foo(Args&&... args)
    {
        new (&store) T { std::forward<Args>(args)... };
    }

    void Release()
    {
        reinterpret_cast<T*>(&store)->~T();
    }
};

int main()
{
    Foo<int> a(2); // ok
    Foo<int[3]> b(1, 2, 3);
}
