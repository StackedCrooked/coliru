#include <type_traits>
#include <new>

template<typename T>
typename std::enable_if<std::is_nothrow_move_constructible<T>::value, T&>::type
recycle(T& obj, T&& other)  noexcept
{ obj.~T(); new (&obj) T(other);  return obj; }

template<typename T, typename... A>
typename std::enable_if<std::is_nothrow_constructible<T>::value && std::is_nothrow_move_constructible<T>::value, T&>::type
recycle(T& obj, A&&... arg) noexcept
{ obj.~T(); new (&obj) T{arg...}; return obj; }


int main()
{
    struct foo
    {
        foo() noexcept {}
        explicit foo(float) noexcept {}
    };

    foo b;
    recycle(b, foo());     // OK, calls #1, move-constructing from default temporary
    recycle(b, foo(1.0f)); // OK, as above, but non-default temporary
    recycle(b, 5.0f);      // OK, calls #2, forwarding and move-constructing
    recycle(b, 5.0);       // succeeds calling #2 (undesired implicit double --> float conversion)
    recycle(b, 5);         // succeeds calling #2 (undesired implicit int ---> float conversion)
    recycle(b, b);         // succeeds, but should probably fail a runtime check (undefined behavior)

    return 0;
}